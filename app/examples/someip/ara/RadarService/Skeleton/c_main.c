/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2021-2024 Parai Wang <parai@foxmail.com>
 */
/* ================================ [ INCLUDES  ] ============================================== */
#include <string.h>
#include "TcpIp.h"
#include "SoAd.h"
#include "Sd.h"
#include "SomeIp.h"
#include "SomeIpXf.h"
#include "E2E.h"

#include "Sd_Cfg.h"
#include "RadarServiceSkeleton.h"
#include "SomeIp_Cfg.h"
#include "SomeIpXf_Cfg.h"

#include "Std_Timer.h"

#include "Std_Debug.h"
/* ================================ [ MACROS    ] ============================================== */
#define AS_LOG_RADAR 1
/* ================================ [ TYPES     ] ============================================== */
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
static Std_TimerType timer10ms;
static Std_TimerType timer1s;
static boolean lBrakeEventSubscribed = FALSE;
static uint32_t lUpdateRate = 0;
static uint8_t lNum = 1;
/* ================================ [ LOCALS    ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
/* ---- SD / connection callbacks ---- */
boolean Sd_ServerServiceRadarService_CRMC(PduIdType pduID, uint8_t type, uint16_t serviceID,
                                          uint16_t instanceID, uint8_t majorVersion,
                                          uint32_t minorVersion,
                                          const Sd_ConfigOptionStringType *receivedConfigOptionPtrArray,
                                          const Sd_ConfigOptionStringType *configuredConfigOptionPtrArray) {
  return TRUE;
}

void SomeIp_RadarService_OnConnect(uint16_t conId, boolean isConnected) {
}

/* ---- subscription callbacks ---- */
void RadarService_OnBrakeEventSubscribed(boolean isSubscribe, TcpIp_SockAddrType *RemoteAddr) {
  ASLOG(RADAR, ("BrakeEvent %s\n", isSubscribe ? "subscribed" : "unsubscribed"));
  lBrakeEventSubscribed = isSubscribe;
}

void RadarService_OnUpdateRateSubscribed(boolean isSubscribe, TcpIp_SockAddrType *RemoteAddr) {
  ASLOG(RADAR, ("UpdateRate %s\n", isSubscribe ? "subscribed" : "unsubscribed"));
}

/* ---- method handler ---- */
Std_ReturnType RadarService_Adjust(const Position_Type *target_position,
                                   AdjustOutput_Type *returnAdjustOutput) {
  returnAdjustOutput->success = TRUE;
  returnAdjustOutput->effective_position = *target_position;
  ASLOG(RADAR, ("Adjust to position (%u, %u, %u)\n", target_position->x, target_position->y,
                target_position->z));
  return E_OK;
}

Std_ReturnType RadarService_Adjust_Async(AdjustOutput_Type *returnAdjustOutput) {
  return E_OK;
}

/* ---- field get/set handlers ---- */
Std_ReturnType RadarService_GetUpdateRate(uint32_t *field) {
  *field = ++lUpdateRate;
  return E_OK;
}

Std_ReturnType RadarService_GetUpdateRate_Async(uint32_t *field) {
  return E_OK;
}

Std_ReturnType RadarService_SetUpdateRate(uint32_t *field) {
  lUpdateRate = *field;
  return E_OK;
}

Std_ReturnType RadarService_SetUpdateRate_Async(uint32_t *field) {
  return E_OK;
}

/* ---- periodic event/field notification ---- */
static void RadarServiceNotify(void) {
  if (lBrakeEventSubscribed) {
    RadarObjects_Type sample;
    uint8_t i;
    sample.active = TRUE;
    sample.objectsLen = lNum;
    for (i = 0; i < lNum; i++) {
      sample.objects[i].x = lNum + 1;
      sample.objects[i].y = lNum + 2;
      sample.objects[i].z = lNum + 3;
    }
    ASLOG(RADAR, ("sending %u radar objects\n", lNum));
    (void)RadarService_SendBrakeEvent(&sample);
    (void)RadarService_UpdateUpdateRate(++lUpdateRate);
    lNum++;
    if (lNum > 32) {
      lNum = 1;
    }
  }
}

int main(int argc, char *argv[]) {
  TcpIp_Init(NULL);
  SoAd_Init(NULL);
  Sd_Init(NULL);
  SomeIp_Init(NULL);
  E2E_Init(NULL);

  RadarService_OfferService();

  Std_TimerStart(&timer10ms);
  Std_TimerStart(&timer1s);

  for (;;) {
    if (Std_GetTimerElapsedTime(&timer10ms) >= 10000) {
      Std_TimerStart(&timer10ms);
      TcpIp_MainFunction();
      SoAd_MainFunction();
      Sd_MainFunction();
      SomeIp_MainFunction();
    }

    if (Std_GetTimerElapsedTime(&timer1s) >= 1000000) {
      Std_TimerStart(&timer1s);
      RadarServiceNotify();
    }
  }

  return 0;
}
