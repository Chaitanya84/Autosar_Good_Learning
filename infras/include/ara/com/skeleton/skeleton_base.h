/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2025 Parai Wang <parai@foxmail.com>
 *
 */
#ifndef ARA_COM_SKELETON_BASE_HPP
#define ARA_COM_SKELETON_BASE_HPP
/* ================================ [ INCLUDES  ] ============================================== */
#include <functional>
#include <unordered_set>
#include <memory>
#include <mutex>
#include <deque>
#include <atomic>
#include <thread>
#include <chrono>
#include "ara/core/result.h"
#include "ara/core/instance_specifier.h"
#include "ara/com/service/instance_identifier.h"
#include "ara/com/types.h"
#include "ara/core/future.h"
#include "ara/com/com_error_domain.h"

namespace ara {
namespace com {
namespace skeleton {
/* ================================ [ MACROS    ] ============================================== */
/* ================================ [ TYPES     ] ============================================== */
/* ================================ [ CLASS    ] ============================================== */
class SkeletonBase {
public:
  /** @SWS_CM_00130 @brief Construct a skeleton for a single service instance. */
  SkeletonBase(
    ara::com::InstanceIdentifier instanceId,
    ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent);

  /** @brief Create a skeleton for a single service instance. */
  static ara::core::Result<SkeletonBase> Create(
    const ara::com::InstanceIdentifier &instanceID,
    ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent) noexcept;

  /** @SWS_CM_00153 @brief Construct a skeleton for multiple service instances. */
  SkeletonBase(
    ara::com::InstanceIdentifierContainer instanceIds,
    ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent);

  /** @brief Create a skeleton for multiple service instances. */
  static ara::core::Result<SkeletonBase> Create(
    const ara::com::InstanceIdentifierContainer &instanceIDs,
    ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent) noexcept;

  /** @SWS_CM_00152 @brief Construct a skeleton from an InstanceSpecifier. */
  SkeletonBase(
    ara::core::InstanceSpecifier instanceSpec,
    ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent);

  /** @brief Create a skeleton from an InstanceSpecifier. */
  static ara::core::Result<SkeletonBase> Create(
    const ara::core::InstanceSpecifier &instanceSpec,
    ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent) noexcept;

  /** @SWS_CM_00134 @brief Copy constructor is deleted. */
  SkeletonBase(const SkeletonBase &other) = delete;

  /** @SWS_CM_11548 @brief Copy assignment is deleted. */
  SkeletonBase &operator=(const SkeletonBase &other) = delete;

  /** @SWS_CM_11370 @brief Destructor. */
  ~SkeletonBase();

  /** @SWS_CM_00101 @brief Offer the service to the network. */
  ara::core::Result<void> OfferService() noexcept;

  /** @SWS_CM_00111 @brief Stop offering the service. */
  void StopOfferService() noexcept;

  /** @SWS_CM_00199 @brief Process the next pending method call (polling mode). */
  bool ProcessNextMethodCall() noexcept;
};
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
/* ================================ [ LOCALS    ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
} // namespace skeleton
} // namespace com
} // namespace ara
#endif /* ARA_COM_SKELETON_BASE_HPP */
