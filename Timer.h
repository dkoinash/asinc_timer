#pragma once

#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <condition_variable>

/// Псевдоним функции, вызываемой по истечению таймаута
using CallFn = std::function<void()>;

/// Псевдомин для длительности
using Duration = std::chrono::steady_clock::duration;

namespace Utils {
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
  AsyncTimer(CallFn callback);

  /**
   * @brief Запуск отсчёта времени таймера
   *
   * @param[in] interval Интервал срабатывания таймера
   */
  void start(Duration interval);

  /**
   * @brief Остановка отсчёта времени таймера
   */
  void stop();

  /**
   * @brief Получение признака активации таймера
   *
   * @return Возвращает true если таймер запущен и false в противном случае
   */
  bool isRunning() const;

  /**
   * @brief Деструктор
   */
  ~AsyncTimer();

private:
  /// Интервал срабатывания
  Duration m_interval;
  /// Callback функция
  CallFn m_callback;
  /// Признак активности такймера
  std::atomic<bool> m_running;
  /// Поток таймера
  std::thread m_worker;
    /// Условная переменная для прерывания таймера
  std::condition_variable m_cv;
};
} // namespace Timer
