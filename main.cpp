#include <cstdio>
#include <iostream>

#include "Timer.h"

void
TestFunc()
{
  std::cout << " > > > CallBack." << std::endl;
}

int
main(int argc, char** argv)
{
  Utils::AsyncTimer timer(TestFunc);

  timer.start(std::chrono::milliseconds(500));
  std::cout << "Старт" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(5));
  timer.stop();
  std::this_thread::sleep_for(std::chrono::seconds(5));
  timer.start(std::chrono::milliseconds(500));
  std::this_thread::sleep_for(std::chrono::seconds(5));
  timer.stop();
  std::cout << "Done" << std::endl;

  return 0;
}