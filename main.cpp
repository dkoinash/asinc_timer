#include <cstdio>
#include <iostream>

#include "myTimer.h"

void
TestFunc()
{
  std::cout << " >> CallBack: Вход." << std::endl;
  // std::this_thread::sleep_for(std::chrono::milliseconds(10));
  // std::cout << " >> CallBack: Выход." << std::endl;
}

int
main(int argc, char** argv)
{
  Timer::Timer timer;

  timer.Start(std::chrono::milliseconds(1000), TestFunc);
  std::cout << "Старт" << std::endl;

  std::this_thread::sleep_for(std::chrono::milliseconds(4000));

  timer.Stop();
  std::cout << "Done" << std::endl;

  return 0;
}