/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2025 Parai Wang <parai@foxmail.com>
 *
 */
#ifndef ARA_COM_SERVICE_FIND_SERVICE_HANDLE_HPP
#define ARA_COM_SERVICE_FIND_SERVICE_HANDLE_HPP
/* ================================ [ INCLUDES  ] ============================================== */
#include <cstdint>

namespace ara {
namespace com {
/* ================================ [ MACROS    ] ============================================== */
/* ================================ [ TYPES     ] ============================================== */
/* ================================ [ CLASS    ] ============================================== */
/* @SWS_CM_00303 @brief Handle identifying an ongoing FindService search. */
struct FindServiceHandle {
public:
  /** @SWS_CM_00353 @brief Default constructor is deleted. */
  FindServiceHandle() = delete;

  /** @SWS_CM_11528 @brief Copy assignment operator. */
  FindServiceHandle &operator=(const FindServiceHandle &other);

  /** @SWS_CM_11527 @brief Compare for ordering with another FindServiceHandle. */
  bool operator<(const FindServiceHandle &other) const;

  /** @SWS_CM_11526 @brief Compare for equality with another FindServiceHandle. */
  bool operator==(const FindServiceHandle &other) const;

private:
  uint64_t m_serviceId;
};
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
/* ================================ [ LOCALS    ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
} // namespace com
} // namespace ara
#endif /* ARA_COM_SERVICE_FIND_SERVICE_HANDLE_HPP */
