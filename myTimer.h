#pragma once

#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

/// Псевдоним функции, вызываемой по истечению таймаута
using CallFn = std::function<void()>;

/// Псевдомин для длительности
using Duration = std::chrono::steady_clock::duration;

namespace Timer {
/**
 * @brief Асинхронный таймер
 */
class AsyncTimer
{
public:
  /**
   * @brief Конструктор
   *
   * @param[in] callback Callback функция
   */
  AsyncTimer(CallFn callback)
    : m_callback(callback)
    , m_running(false)
  {}

  /**
   * @brief Запуск отсчёта времени таймера
   *
   * @param[in] interval Интервал срабатывания таймера
   */
  void start(Duration interval)
  {
    m_interval = interval;
    if (m_running) return;
    m_running = true;
    m_worker  = std::thread([this]() {
      while (m_running) {
        std::this_thread::sleep_for(m_interval);
        if (m_running) m_callback();
      }
    });
  }

  /**
   * @brief Остановка отсчёта времени таймера
   */
  void stop()
  {
    m_running = false;
    if (m_worker.joinable()) {
      m_worker.join();
    }
  }

  /**
   * @brief Получение признака активации таймера
   *
   * @return Возвращает true если таймер запущен и false в противном случае
   */
  bool isRunning() const { return m_running; }

  /**
   * @brief Деструктор
   */
  ~AsyncTimer() { stop(); }

private:
  /// Интервал срабатывания
  Duration m_interval;
  /// Callback функция
  CallFn m_callback;
  /// Признак активности такймера
  std::atomic<bool> m_running;
  /// Поток таймера
  std::thread m_worker;
};
} // namespace Timer
