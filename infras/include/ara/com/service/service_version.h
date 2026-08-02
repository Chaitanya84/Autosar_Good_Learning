/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2025 Parai Wang <parai@foxmail.com>
 */
#ifndef ARA_COM_SERVICE_SERVICE_VERSION_HPP
#define ARA_COM_SERVICE_SERVICE_VERSION_HPP

/* ================================ [ INCLUDES ] ============================================== */
#include <cstdint>

#include "ara/core/string_view.h"

namespace ara {
namespace com {

/* ================================ [ TYPES ] ============================================== */

/** @SWS_CM_11515 @brief Represents the version of a service. */
class ServiceVersionType {
public:
  /** @SWS_CM_11518 @brief Copy assignment operator. */
  ServiceVersionType &operator=(const ServiceVersionType &other) {
    m_version = other.m_version;
  }

  /** @SWS_CM_11519 @brief Return the version as a StringView. */
  ara::core::StringView ToString() const;

  /** @SWS_CM_11517 @brief Compare for ordering with another ServiceVersionType. */
  bool operator<(const ServiceVersionType &other) const {
    return m_version < other.m_version;
  }

  /** @SWS_CM_11516 @brief Compare for equality with another ServiceVersionType. */
  bool operator==(const ServiceVersionType &other) const {
    return m_version == other.m_version;
  }

  /** @brief Construct from a raw version integer. */
  constexpr ServiceVersionType(uint32_t version) noexcept : m_version(version) {
  }

private:
  uint32_t m_version;
};

} // namespace com
} // namespace ara

#endif /* ARA_COM_SERVICE_SERVICE_VERSION_HPP */
