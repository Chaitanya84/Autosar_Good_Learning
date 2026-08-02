/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2025 Parai Wang <parai@foxmail.com>
 *
 */
#ifndef ARA_COM_PROXY_BASE_HPP
#define ARA_COM_PROXY_BASE_HPP
/* ================================ [ INCLUDES  ] ============================================== */
#include <functional>
#include <unordered_set>
#include <memory>
#include <mutex>
#include <deque>
#include <atomic>
#include "ara/core/result.h"
#include "ara/core/future.h"
#include "ara/core/instance_specifier.h"
#include "ara/com/types.h"
#include "ara/com/service/instance_identifier.h"
#include "ara/com/service/sample_ptr.h"

namespace ara {
namespace com {
namespace proxy {
/* ================================ [ MACROS    ] ============================================== */
/* ================================ [ TYPES     ] ============================================== */
/* ================================ [ CLASS    ] ============================================== */
class ProxyEventBase {
public:
  /** @SWS_CM_00141 @brief Subscribe to the event with a maximum number of samples. */
  ara::core::Result<void> Subscribe(std::size_t maxSampleCount) noexcept;

  /** @SWS_CM_00316 @brief Return the current subscription state. */
  ara::com::SubscriptionState GetSubscriptionState() const noexcept;

  /** @SWS_CM_00151 @brief Unsubscribe from the event. */
  void Unsubscribe() noexcept;

  /** @SWS_CM_11603 @brief Return the number of free sample slots. */
  std::size_t GetFreeSampleCount() const noexcept;

  /** @SWS_CM_11605 @brief Set a handler called when new event data arrives. */
  ara::core::Result<void> SetReceiveHandler(ara::com::EventReceiveHandler handler) noexcept;

  /** @SWS_CM_11606 @brief Unset the previously set receive handler. */
  ara::core::Result<void> UnsetReceiveHandler() noexcept;

  /** @SWS_CM_12008 @brief Set a handler called when the subscription state changes. */
  ara::core::Result<void>
  SetSubscriptionStateChangeHandler(ara::com::SubscriptionStateChangeHandler handler) noexcept;

  /** @SWS_CM_12010 @brief Unset the previously set subscription state change handler. */
  void UnsetSubscriptionStateChangeHandler() noexcept;

  /** @SWS_CM_11610 @brief Get new samples since the last call via a caller-provided callback. */
  template <typename F>
  ara::core::Result<std::size_t>
  GetNewSamples(F &&f, std::size_t maxNumberOfSamples = std::numeric_limits<std::size_t>::max());
};

class ProxyMethodBase {
public:
  /** @brief Invoke a fire-and-forget (one-way) method. */
  ara::core::Result<void> operator()();

  /** @brief Invoke a method with a return value. */
  template <typename OutputT> ara::core::Future<OutputT> operator()(...);
};

class HandleTypeBase { /** @SWS_CM_00312 @brief Base class encapsulating a service handle identifying a service instance. */
public:
  /** @SWS_CM_00317 @brief Copy constructor. */
  HandleTypeBase(const HandleTypeBase &other);

  /** @SWS_CM_00318 @brief Move constructor. */
  HandleTypeBase(HandleTypeBase &&other);

  /** @SWS_CM_00349 @brief Default constructor is deleted. */
  HandleTypeBase() = delete;

  /** @SWS_CM_11532 @brief Copy assignment operator. */
  HandleTypeBase &operator=(const HandleTypeBase &other);

  /** @SWS_CM_11533 @brief Move assignment operator. */
  HandleTypeBase &operator=(HandleTypeBase &&other);

  /** @SWS_CM_11371 @brief Destructor. */
  ~HandleTypeBase() noexcept;

  /** @SWS_CM_11531 @brief Return the InstanceIdentifier of the handled service instance. */
  const ara::com::InstanceIdentifier &GetInstanceId() const;

  /** @SWS_CM_11530 @brief Compare for ordering with another handle. */
  bool operator<(const HandleTypeBase &other) const;

  /** @SWS_CM_11529 @brief Compare for equality with another handle. */
  bool operator==(const HandleTypeBase &other) const;
};

template <typename HandleType> class ProxyBase {
public:
  /** @SWS_CM_00123 @brief Asynchronously start searching for a service by InstanceIdentifier. */
  static ara::core::Result<ara::com::FindServiceHandle>
  StartFindService(ara::com::FindServiceHandler<HandleType> handler,
                   ara::com::InstanceIdentifier instanceId) noexcept;

  /** @SWS_CM_00623 @brief Asynchronously start searching for a service by InstanceSpecifier. */
  static ara::core::Result<ara::com::FindServiceHandle>
  StartFindService(ara::com::FindServiceHandler<HandleType> handler,
                   ara::core::InstanceSpecifier instanceSpec);

  /** @SWS_CM_11365 @brief Start searching for a service with a custom executor (InstanceSpecifier). */
  template <typename ExecutorT>
  static ara::com::FindServiceHandle
  StartFindService(ara::com::FindServiceHandler<HandleType> handler,
                   ara::core::InstanceSpecifier instance, ExecutorT &&executor) noexcept;

  /** @SWS_CM_11352 @brief Start searching for a service with a custom executor (InstanceIdentifier). */
  template <typename ExecutorT>
  static ara::com::FindServiceHandle
  StartFindService(ara::com::FindServiceHandler<HandleType> handler,
                   ara::com::InstanceIdentifier instance, ExecutorT &&executor) noexcept;

  /** @SWS_CM_00125 @brief Stop an ongoing FindService search. */
  static void StopFindService(ara::com::FindServiceHandle handle) noexcept;

  /** @SWS_CM_00122 @brief Synchronously find service instances by InstanceIdentifier. */
  static ara::core::Result<ara::com::ServiceHandleContainer<HandleType>>
  FindService(ara::com::InstanceIdentifier instance) noexcept;

  /** @SWS_CM_00622 @brief Synchronously find service instances by InstanceSpecifier. */
  static ara::core::Result<ara::com::ServiceHandleContainer<HandleType>>
  FindService(ara::core::InstanceSpecifier instanceSpec);

  /** @SWS_CM_00131 @brief Construct a proxy from a service handle. */
  explicit ProxyBase(HandleType &handle);

  /** @SWS_CM_00136 @brief Copy constructor is deleted. */
  ProxyBase(ProxyBase &other) = delete;

  /** @SWS_CM_11551 @brief Copy assignment is deleted. */
  ProxyBase &operator=(const ProxyBase &other) = delete;
};
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
/* ================================ [ LOCALS    ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
} // namespace proxy
} // namespace com
} // namespace ara
#endif /* ARA_COM_PROXY_BASE_HPP */
