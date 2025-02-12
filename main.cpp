#include <cstdio>
#include <iostream>

#include "Timer.h"

void
TestFunc()
{
  std::cout << " >> CallBack." << std::endl;
}

int
main(int argc, char** argv)
{
  Utils::AsyncTimer timer(TestFunc);

  timer.start(std::chrono::milliseconds(800));
  std::cout << "Старт" << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(10));

  timer.stop();
  std::cout << "Done" << std::endl;

  return 0;
}