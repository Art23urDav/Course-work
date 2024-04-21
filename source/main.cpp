#include "rtos.hpp"         // for Rtos

#include <iostream>
#include "adc.h"
#include "measurementTask.h"          // for MeasurementTask

#include "rccregisters.hpp" // for RCC

#include "gpioaregisters.hpp"  // for GPIOA
#include "gpiocregisters.hpp"  // for GPIOC

#include "adc1registers.hpp" // for ADC1
#include "adccommonregisters.hpp"

std::uint32_t SystemCoreClock = 16'000'000U;


extern "C" {
int __low_level_init(void)
{
  //Switch on external 16 MHz oscillator
  RCC::CR::HSION::On::Set();
  while (RCC::CR::HSIRDY::NotReady::IsSet())
  {

  }
  //Switch system clock on external oscillator
  RCC::CFGR::SW::Hsi::Set();
  while (!RCC::CFGR::SWS::Hsi::IsSet())
  {

  }
  //Switch on clock on PortA and PortC
  RCC::AHB1ENRPack<
      RCC::AHB1ENR::GPIOCEN::Enable,
      RCC::AHB1ENR::GPIOAEN::Enable
  >::Set();

  RCC::APB2ENR::SYSCFGEN::Enable::Set();
  

  RCC::APB2ENR::ADC1EN::Enable::Set();
  
  return 1;
}
}
Adc adc1;
MeasurementTask measurementTask(adc1);

int main()
{
  using namespace OsWrapper;
  
  Rtos::CreateThread(measurementTask, "measurementTask");

  Rtos::Start();
  
  return 0;
}
