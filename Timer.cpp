#include "Timer.h"

namespace Utils {

AsyncTimer::AsyncTimer(CallFn callback)
  : m_callback(callback)
  , m_running(false)
{}

void
AsyncTimer::start(Duration interval)
{
  m_interval = interval;
  if (m_running) return;
  m_running = true;
  m_worker  = std::thread([this]() {
    std::mutex mtx;

    while (true) {
      if (!m_running) break;

      std::unique_lock<std::mutex> lock(mtx);

      if (m_cv.wait_for(lock, m_interval) == std::cv_status::no_timeout) break;

      if (!m_running) break;

      m_callback();
    }
  });
}

void
AsyncTimer::stop()
{
  if (!m_running) return;

  m_running = false;

  m_cv.notify_one();

  if (m_worker.joinable()) {
    m_worker.join();
  }
}

bool
AsyncTimer::isRunning() const
{
  return m_running;
}

AsyncTimer::~AsyncTimer()
{
  stop();
}

} // namespace Utils