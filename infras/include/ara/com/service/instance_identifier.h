/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2025 Parai Wang <parai@foxmail.com>
 *
 */
#ifndef ARA_COM_SERVICE_INSTANCE_IDENTIFIER_HPP
#define ARA_COM_SERVICE_INSTANCE_IDENTIFIER_HPP
/* ================================ [ INCLUDES  ] ============================================== */
#include "ara/core/result.h"
#include "ara/core/string_view.h"
#include <string>

namespace ara {
namespace com {
/* ================================ [ MACROS    ] ============================================== */
/* ================================ [ TYPES     ] ============================================== */
/* ================================ [ CLASS    ] ============================================== */
class InstanceIdentifier { /* @SWS_CM_00302 @brief Identifies an instance of a service by a serialized format string. */
public:
  /** @SWS_CM_00056 @brief Copy constructor. */
  explicit InstanceIdentifier(const InstanceIdentifier &other) noexcept
    : m_serializedFormat(other.m_serializedFormat) {
  }

  /** @SWS_CM_11525 @brief Copy assignment operator. */
  InstanceIdentifier &operator=(const InstanceIdentifier &other) noexcept {
    m_serializedFormat = other.m_serializedFormat;
    return *this;
  }

  /** @SWS_CM_00054 @brief Move assignment operator. */
  InstanceIdentifier &operator=(InstanceIdentifier &&other) noexcept {
    m_serializedFormat = other.m_serializedFormat;
    return *this;
  }

  /** @SWS_CM_00055 @brief Destructor. */
  ~InstanceIdentifier() noexcept {
  }

  /** @SWS_CM_11521 @brief Construct from a serialized format string. */
  explicit InstanceIdentifier(ara::core::StringView serializedFormat)
    : m_serializedFormat(serializedFormat.data(), serializedFormat.size()) {
  }

  /** @SWS_CM_00053 @brief Move constructor. */
  explicit InstanceIdentifier(const InstanceIdentifier &&other) noexcept
    : m_serializedFormat(other.m_serializedFormat) {
  }

  /** @SWS_CM_11520 @brief Create an InstanceIdentifier from a serialized format string. */
  static InstanceIdentifier Create(ara::core::StringView serializedFormat) noexcept {
    return InstanceIdentifier(serializedFormat);
  }

  /** @SWS_CM_11524 @brief Compare for ordering with another InstanceIdentifier. */
  bool operator<(const InstanceIdentifier &other) const noexcept {
    return m_serializedFormat < other.m_serializedFormat;
  }

  /** @SWS_CM_11523 @brief Compare for equality with another InstanceIdentifier. */
  bool operator==(const InstanceIdentifier &other) const noexcept {
    return m_serializedFormat == other.m_serializedFormat;
  }

  /** @SWS_CM_11522 @brief Return the serialized format as a StringView. */
  ara::core::StringView toString() const noexcept {
    return ara::core::StringView(m_serializedFormat.data(), m_serializedFormat.size());
  }

private:
  std::string m_serializedFormat;
};
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
/* ================================ [ LOCALS    ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
} // namespace com
} // namespace ara
#endif /* ARA_COM_SERVICE_INSTANCE_IDENTIFIER_HPP */
