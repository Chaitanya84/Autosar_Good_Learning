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
#include "RadarServiceProxy.h"
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
static boolean lIsAvailable = FALSE;
static boolean lSubscribed = FALSE;
static boolean lBrakeEventSubscribed = FALSE;
static boolean lUpdateRateSubscribed = FALSE;
static uint32_t lAdjustIndex = 0;
/* ================================ [ LOCALS    ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
/* ---- callbacks implemented by the user ---- */
void SomeIp_RadarService_OnAvailability(boolean isAvailable) {
  ASLOG(RADAR, ("service %s\n", isAvailable ? "online" : "offline"));
  lIsAvailable = isAvailable;
  if (!isAvailable) {
    lSubscribed = FALSE;
    lBrakeEventSubscribed = FALSE;
    lUpdateRateSubscribed = FALSE;
  }
}

void RadarService_SubscribeBrakeEventAck(boolean isSubscribe) {
  ASLOG(RADAR, ("BrakeEvent %s\n", isSubscribe ? "subscribed" : "unsubscribed"));
  lBrakeEventSubscribed = isSubscribe;
}

void RadarService_SubscribeUpdateRateAck(boolean isSubscribe) {
  ASLOG(RADAR, ("UpdateRate %s\n", isSubscribe ? "subscribed" : "unsubscribed"));
  lUpdateRateSubscribed = isSubscribe;
}

void RadarService_BrakeEvent(const RadarObjects_Type *sample) {
  if (sample->active) {
    ASLOG(RADAR, ("%u objects: [(%u, %u, %u), (%u, %u, %u), ...]\n", sample->objectsLen,
                  sample->objects[0].x, sample->objects[0].y, sample->objects[0].z,
                  sample->objects[1].x, sample->objects[1].y, sample->objects[1].z));
  } else {
    ASLOG(RADAR, ("sample is not active\n"));
  }
}

void RadarService_UpdateRate(uint32_t field) {
  ASLOG(RADAR, ("UpdateRate: %u\n", field));
}

void RadarService_Adjust_Return(Std_ReturnType ercd, const AdjustOutput_Type *AdjustOutput) {
  if (ercd == E_OK) {
    ASLOG(RADAR, ("Adjust with: %s (%u, %u, %u)\n", AdjustOutput->success ? "success" : "fail",
                  AdjustOutput->effective_position.x, AdjustOutput->effective_position.y,
                  AdjustOutput->effective_position.z));
  } else {
    ASLOG(RADAR, ("Adjust with error: %d\n", ercd));
  }
}

void RadarService_GetUpdateRate_Return(Std_ReturnType ercd, uint32_t field) {
  if (ercd == E_OK) {
    ASLOG(RADAR, ("Get Field UpdateRate with: %u\n", field));
  } else {
    ASLOG(RADAR, ("Get UpdateRate with error: %d\n", ercd));
  }
}

void RadarService_SetUpdateRate_Return(Std_ReturnType ercd, const uint32_t value) {
  if (ercd == E_OK) {
    ASLOG(RADAR, ("Set Field UpdateRate with: %u\n", value));
  } else {
    ASLOG(RADAR, ("Set UpdateRate with error: %d\n", ercd));
  }
}

static void RadarServiceMethodRequest(void) {
  if (lIsAvailable && lBrakeEventSubscribed) {
    {
      Position_Type target_position = {lAdjustIndex, lAdjustIndex + 1, lAdjustIndex + 2};
      (void)RadarService_Adjust(&target_position);
    }
    {
      uint32_t newField = lAdjustIndex * 3;
      (void)RadarService_SetUpdateRate(newField);
    }
    {
      (void)RadarService_GetUpdateRate();
    }
    lAdjustIndex++;
  }
}

int main(int argc, char *argv[]) {
  TcpIp_Init(NULL);
  SoAd_Init(NULL);
  Sd_Init(NULL);
  SomeIp_Init(NULL);
  E2E_Init(NULL);

  RadarService_FindService();

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
      if (lIsAvailable && !lSubscribed) {
        lSubscribed = TRUE;
        (void)RadarService_SubscribeBrakeEvent();
        (void)RadarService_SubscribeUpdateRate();
      }
      RadarServiceMethodRequest();
    }
  }

  return 0;
}
