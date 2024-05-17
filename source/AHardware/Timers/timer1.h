#ifndef TIMER1
#define TIMER1

#include "tim1registers.hpp"            // for TIMER 1
#include "countmanager.h"               // for CountManager

class Timer1
{
  public:
    Timer1(CountManager& countManager) : mCountManager(countManager) { }
    void handler()
    {
      if(TIM1::SR::CC1IF::InterruptPending::IsSet())
      {
        mCountManager.UpdateNumberPulses();
      }
      TIM1::SR::CC1IF::NoInterruptPending::Set();
    }
  private:
    CountManager& mCountManager;
    std::uint32_t counters = 0U;
};
#endif