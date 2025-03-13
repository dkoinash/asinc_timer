#include "Timer.h"

namespace Utils {

AsyncTimer::AsyncTimer(CallFn callback)
  : m_callback(callback)
  , m_running(false)
  , m_timerOn(true)
{
  m_worker = std::thread([this]() {
    std::mutex mtx;

    while (true) {
      std::unique_lock<std::mutex> lock(mtx);

      m_cvRun.wait(lock, [this] { return m_running || !m_timerOn; });

      if (!m_timerOn) break;

      if (m_cv.wait_for(lock, m_interval) == std::cv_status::timeout) m_callback();
    }
  });
}

void
AsyncTimer::start(Duration interval)
{
  m_interval = interval;

  if (m_running) return;

  m_running = true;

  m_cv.notify_one();
  m_cvRun.notify_one();
}

void
AsyncTimer::stop()
{
  if (!m_running) return;

  m_running = false;

  m_cv.notify_one();
  m_cvRun.notify_one();
}

bool
AsyncTimer::isRunning() const
{
  return m_running;
}

AsyncTimer::~AsyncTimer()
{
  m_timerOn = false;
  m_cvRun.notify_one();
  if (m_worker.joinable()) {
    m_worker.join();
  }
}

} // namespace Utils