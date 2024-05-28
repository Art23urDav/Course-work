#ifndef TIMER1
#define TIMER1

#include "tim1registers.hpp"            // for TIMER 1
#include "countmanager.h"               // for CountManager

class Timer1
{
  public:
    Timer1(CountManager& countManagerDirect, CountManager& countManagerReverse) 
      : mPulseWaterFlowDirect(countManagerDirect), mPulseWaterFlowReverse(countManagerReverse) { }
    void handler()
    {
      if(TIM1::SR::CC2IF::InterruptPending::IsSet() 
         and TIM1::DIER::CC2IE::Value1::IsSet())
      {
        mPulseWaterFlowDirect.UpdateNumberPulses();
        TIM1::SR::CC2IF::NoInterruptPending::Set();
      }
      
      if(TIM1::SR::CC3IF::InterruptPending::IsSet() 
         and TIM1::DIER::CC3IE::Value1::IsSet())
      {
        mPulseWaterFlowReverse.UpdateNumberPulses();
        TIM1::SR::CC3IF::NoInterruptPending::Set();
      }

    }
  private:
    CountManager& mPulseWaterFlowDirect;
    CountManager& mPulseWaterFlowReverse;
    std::uint32_t counters = 0U;
};
#endif