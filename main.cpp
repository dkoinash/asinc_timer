#include <cstdio>
#include <iostream>

#include "myTimer.h"


void
TestFunc()
{
  std::cout << " >> CallBack: Вход." << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::cout << " >> CallBack: Выход." << std::endl;

}

int
main(int argc, char** argv)
{
  Timer::Timer timer(TestFunc);

  timer.SetDuration(std::chrono::milliseconds(500));

  timer.Start();
    
  

  std::this_thread::sleep_for(std::chrono::milliseconds(10000));

 timer.Stop();
  std::cout << "Done" << std::endl;

  return 0;
}