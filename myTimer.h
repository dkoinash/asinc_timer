#pragma once
#include <chrono>
#include <ctime>
#include <functional>
#include <thread>


namespace Timer {
using CallBackFn = std::function<void()>;

class Timer
{
public:
  Timer(CallBackFn callBackFn);

  void SetDuration(std::chrono::milliseconds value);

  void Start();

  void Stop();

private:
  CallBackFn m_callBackFn = nullptr;

  std::chrono::milliseconds m_delay = std::chrono::milliseconds(1000);

  std::chrono::time_point<std::chrono::steady_clock> m_start;

  bool m_isActive = false;
};
} // namespace Timer