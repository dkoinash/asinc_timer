#pragma once
#include <chrono>
#include <ctime>
#include <functional>
#include <thread>

namespace Timer {

class Timer
{
public:
  /**
   * @brief                 Запуск таймера
   *
   * @tparam Rep            Количество тиков
   * @tparam Period         Период тика
   * @param[in] delay       Заданное время срабатывания таймера
   * @param[in] callBackFn  Функция, вызываемая при завершении отсчёта времени таймера
   */
  template<class Rep, class Period>
  void Start(const std::chrono::duration<Rep, Period>& delay, std::function<void()> callBackFn)
  {
    if (m_isActive) return;
    if (delay.count() == 0) return;
    if (callBackFn == nullptr) return;

    std::cout << "Start called!" << std::endl;
    m_isActive = true;

    std::thread([&]() {
      std::chrono::time_point<std::chrono::steady_clock> nextTimepoint =
        std::chrono::steady_clock::now();

      while (true) {
        nextTimepoint += delay;

        std::this_thread::sleep_until(nextTimepoint);
        if (!m_isActive) break;
        std::cout << "callBackFn called!" << std::endl;
        callBackFn();
      }
    }).detach();
  }

  /**
   * @brief Остановка таймера
   */
  void Stop() { m_isActive = false; }

  /**
   * @brief Запрос состояния таймера
   *
   * @return Возвращает true если таймер запущен и false в противном случае
   */
  bool IsActive() const { return m_isActive; }

private:
  bool m_isActive = false;
};
} // namespace Timer