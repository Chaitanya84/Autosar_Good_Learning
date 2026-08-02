/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2025 Parai Wang <parai@foxmail.com>
 */

#ifndef ARA_COM_SERVICE_SERVICE_IDENTIFIER_HPP
#define ARA_COM_SERVICE_SERVICE_IDENTIFIER_HPP

/* ================================ [ INCLUDES  ] ============================================== */
#include <cstdint>
#include "ara/core/string_view.h"

namespace ara {
namespace com {

/* ================================ [ CLASS    ] ============================================== */
/**
 * @SWS_CM_11510
 * @brief Identifies a service by its service ID.
 */
class ServiceIdentifierType {
public:
  /** @SWS_CM_11513 @brief Copy assignment operator. */
  ServiceIdentifierType &operator=(const ServiceIdentifierType &other);

  /** @brief Construct from a service ID. */
  constexpr explicit ServiceIdentifierType(uint16_t serviceId) noexcept : m_serviceId(serviceId) {
  }

  /** @SWS_CM_11512 @brief Compare for ordering with another ServiceIdentifierType. */
  bool operator<(const ServiceIdentifierType &other) const {
    return m_serviceId < other.m_serviceId;
  }

  /** @SWS_CM_11511 @brief Compare for equality with another ServiceIdentifierType. */
  bool operator==(const ServiceIdentifierType &other) const {
    return m_serviceId == other.m_serviceId;
  }

  /** @SWS_CM_11514 @brief Return the service identifier as a StringView. */
  ara::core::StringView toString() const;

private:
  uint16_t m_serviceId;
};

/* ================================ [ FUNCTIONS ] ============================================== */

} // namespace com
} // namespace ara

#endif /* ARA_COM_SERVICE_SERVICE_IDENTIFIER_HPP */
