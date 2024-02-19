#include "myTimer.h"

#include <iostream>
#include <thread>

#define DEBUG 1

namespace Timer {

Timer::Timer(CallBackFn callBackFn)
  : m_callBackFn(callBackFn)
{}
void
Timer::SetDuration(std::chrono::milliseconds value)
{
  m_delay = value;
}

void
Timer::Start()
{
  using namespace std::literals;
  if (m_callBackFn == nullptr) return;

  m_isActive = true;
#if DEBUG
  std::cout << "Timer started!" << std::endl;
#endif
  std::thread([=]() {
    m_start = std::chrono::steady_clock::now();

    while (true) {
#if DEBUG
      std::cout << "Timestamp = " << m_start.time_since_epoch().count() << std::endl;
#endif
      m_start += m_delay;
      std::this_thread::sleep_until(m_start /* m_start + m_delay */);
#if DEBUG
      std::cout << "Timer Up!" << std::endl;
#endif
      if (!m_isActive) break;
#if DEBUG
      std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::steady_clock::now() - m_start)
                     .count()
                << std::endl;
#endif
      // m_start = __until; // std::chrono::steady_clock::now();
      m_callBackFn();
    }
  }).detach();
}

void
Timer::Stop()
{
  m_isActive = false;
#if DEBUG
  std::cout << "Timer stopped!" << std::endl;
#endif
}

} // namespace Timer