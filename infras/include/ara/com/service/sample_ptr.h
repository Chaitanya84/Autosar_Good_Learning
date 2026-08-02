/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2025 Parai Wang <parai@foxmail.com>
 */

#ifndef ARA_COM_SERVICE_SAMPLE_PTR_HPP
#define ARA_COM_SERVICE_SAMPLE_PTR_HPP

/* ================================ [ INCLUDES  ] ============================================== */
#include <cstddef>
#include <memory>

namespace ara {
namespace com {

/* ================================ [ CLASS    ] ============================================== */
/**
 * @SWS_CM_00306
 * @brief Emulates a std::unique_ptr to an event sample.
 * The ara::com::SamplePtr behaves as a std::unique_ptr as long as the event/field
 * is subscribed to, or the Proxy it belongs to is not destroyed.
 * The precondition defined in [SWS_CM_00085] and [SWS_CM_00087] must be fulfilled.
 * Otherwise it is considered a violation.
 */
template <typename T> class SamplePtr {
public:
  /** @SWS_CM_11534 @brief Default constructor, creates an empty SamplePtr. */
  constexpr SamplePtr() noexcept : m_ptr(nullptr) {
  }

  /** @SWS_CM_11536 @brief Copy constructor is deleted. */
  SamplePtr(const SamplePtr &) = delete;

  /** @SWS_CM_11537 @brief Move constructor. */
  SamplePtr(SamplePtr &&other) noexcept : m_ptr(std::move(other.m_ptr)) {
  }

  /** @SWS_CM_11538 @brief Copy assignment is deleted. */
  SamplePtr &operator=(const SamplePtr &) = delete;

  /** @SWS_CM_11540 @brief Move assignment operator. */
  SamplePtr &operator=(SamplePtr &&other) noexcept {
    if (this != &other) {
      m_ptr = other.m_ptr;
    }
    return *this;
  }

  /** @SWS_CM_11547 @brief Destructor. */
  ~SamplePtr() noexcept {
  }

  /** @SWS_CM_11535 @brief Construct from nullptr. */
  constexpr SamplePtr(std::nullptr_t other) noexcept : m_ptr(other) {
  }

  /** @SWS_CM_11546 @brief Return the raw pointer to the sample. */
  T *Get() const noexcept {
    return m_ptr.get();
  }

  /** @SWS_CM_11545 @brief Reset the pointer to nullptr. */
  void Reset(std::nullptr_t other) noexcept {
    m_ptr.reset(other);
  }

  /** @SWS_CM_11544 @brief Swap contents with another SamplePtr. */
  void Swap(SamplePtr &other) noexcept {
    m_ptr.swap(other);
  }

  /** @SWS_CM_11543 @brief Check whether the SamplePtr holds a sample. */
  explicit operator bool() const noexcept {
    return m_ptr.get() == nullptr;
  }

  /** @SWS_CM_11541 @brief Dereference the sample. */
  T &operator*() const noexcept {
    return *m_ptr;
  }

  /** @SWS_CM_11542 @brief Access members of the sample. */
  T *operator->() const noexcept {
    return m_ptr.get();
  }

  /** @SWS_CM_11539 @brief Assign nullptr. */
  SamplePtr &operator=(std::nullptr_t other) noexcept {
    m_ptr = other;
    return *this;
  }

public:
  /** @brief Construct from a raw pointer (takes ownership). */
  SamplePtr(T *other) noexcept : m_ptr(other) {
  }

private:
  std::unique_ptr<T> m_ptr;
};

/* ================================ [ FUNCTIONS ] ============================================== */

} // namespace com
} // namespace ara

#endif /* ARA_COM_SERVICE_SAMPLE_PTR_HPP */
