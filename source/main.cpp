#include "rtos.hpp"         // for Rtos

#include "injectedchannel.h"          // for InjectedChannel 
#include "adc.h"                      // for Adc
#include "measurementTask.h"          // for MeasurementTask
#include "resistancethermometer.h"   // for ResistanceThermometers

#include "rccregisters.hpp" // for RCC

#include "gpioaregisters.hpp"  // for GPIOA
#include "gpiocregisters.hpp"  // for GPIOC

#include "adc1registers.hpp" // for ADC1

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
  
  /* ADC setup */
  
  RCC::APB2ENR::ADC1EN::Enable::Set();
  
  GPIOA::MODER::MODER0::Analog::Set(); // setting the port to analog input
  GPIOA::MODER::MODER4::Analog::Set(); // setting the port to analog input
  
  ADC1::CR1::RES::Bits12::Set();// ADC capacity
  
  ADC1::CR1::SCAN::Enable::Set(); // Enabling Scan Mode
  
  ADC1::CR2::CONT::SingleConversion::Set(); // Enabling single conversion mode
  ADC1::CR2::EOCS::SequenceConversion::Set(); // The selection of the end of transformation type EOC is set after the end of the transformation for the entire sequence
  
  ADC1::JSQR::JL::Conversions4::Set(); // Transform sequence length
  ADC1::JSQR::JSQ1::Channel17::Set(); // Change the channel number for TODO conversion to channel 0
  ADC1::JSQR::JSQ2::Channel13::Set();
  
  ADC1::SMPR1::SMP16::Cycles480::Set(); // Selecting the sampling time for a channel
  
  ADC1::CR2::ADON::Enable::Set(); // turn on ADC
  
  /* ADC setup end */
  
  return 1;
}
}
extern ResistanceThermometer ResistanceThermometerDirect;
extern ResistanceThermometer ResistanceThermometerReverse;

InjectedChannel channelResistanceThermometerDirect(static_cast<IInjectedChannelNotifier&>(ResistanceThermometerDirect));
InjectedChannel channelResistanceThermometerReverse(static_cast<IInjectedChannelNotifier&>(ResistanceThermometerReverse));

ResistanceThermometer ResistanceThermometerDirect(static_cast<IDataProvider&>(channelResistanceThermometerDirect));
ResistanceThermometer ResistanceThermometerReverse(static_cast<IDataProvider&>(channelResistanceThermometerReverse));

Adc<channelResistanceThermometerDirect, channelResistanceThermometerReverse> adc1;
MeasurementTask measurementTask(adc1);

int main()
{

  using namespace OsWrapper;
  
  Rtos::CreateThread(measurementTask, "measurementTask");

  Rtos::Start();
  
  return 0;
}
