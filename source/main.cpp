#include "rtos.hpp"         // for Rtos

#include "injectedchannel.h"          // for InjectedChannel 
#include "adc.h"                      // for Adc
#include "measurementTask.h"          // for MeasurementTask
#include "resistancethermometer.h"   // for ResistanceThermometers
#include "countmanager.h"            // for CountManager
#include "waterconsumption.h"        // for WaterConsumption
#include "timer1.h"                  // for Timer1


#include "rccregisters.hpp" // for RCC

#include "gpioaregisters.hpp"  // for GPIOA
#include "gpiocregisters.hpp"  // for GPIOC

#include "adc1registers.hpp" // for ADC1

#include "tim1registers.hpp" // for TIMER 1

#include "nvicregisters.hpp"         // for NVIC

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
  
  /* ADC setup */
  
  RCC::APB2ENR::ADC1EN::Enable::Set();
  
  NVIC::ISER0::Write(1<<27U);
  
  GPIOA::MODER::MODER0::Analog::Set(); // setting the port to analog input
  GPIOA::MODER::MODER4::Analog::Set(); // setting the port to analog input
  
  ADC1::CR1::RES::Bits12::Set();// ADC capacity
  
  ADC1::CR1::SCAN::Enable::Set(); // Enabling Scan Mode
  
  ADC1::CR2::CONT::SingleConversion::Set(); // Enabling single conversion mode
  ADC1::CR2::EOCS::SequenceConversion::Set(); // The selection of the end of transformation type EOC is set after the end of the transformation for the entire sequence
  
  ADC1::SMPR2::SMP0::Cycles480::Set(); // Selecting the sampling time for a channel
  ADC1::SMPR2::SMP5::Cycles480::Set(); // Selecting the sampling time for a channel
  
  ADC1::JSQR::JL::Conversions2::Set(); // Transform sequence length
  ADC1::JSQR::JSQ3::Channel0::Set(); // Change the channel number for TODO conversion to channel 0
  ADC1::JSQR::JSQ4::Channel4::Set();
  
  ADC1::CR2::ADON::Enable::Set(); // turn on ADC
  
  /* ADC setup end */
  
  /* TIM1 setup */
  
  RCC::APB2ENR::TIM1EN::Enable::Set();
  
  GPIOA::MODER::MODER9::Alternate::Set();
  GPIOA::MODER::MODER10::Alternate::Set();
  GPIOA::AFRH::AFRH9::Af1::Set();
  GPIOA::AFRH::AFRH10::Af1::Set();
  
  TIM1::CCMR1_Input::CC2S::Value1::Set();       //CC1 channel is configured as input, IC1 is mapped on TI1
  TIM1::CCMR1_Input::IC2F::Value1::Set();       //This bit-field defines the frequency used to sample TI1 input 
  
  TIM1::CCMR2_Input::CC3S::Value1::Set();       //CC1 channel is configured as input, IC1 is mapped on TI1
  TIM1::CCMR2_Input::IC3F::Value1::Set();       //This bit-field defines the frequency used to sample TI1 input 
  
  TIM1::CCER::CC2P::Value0::Set();              //non-inverted/rising edge
  TIM1::CCER::CC2NP::Value0::Set();             //This bit is used in conjunction with CC1P to define the polarity of TI1FP1 and TI2FP1. 
  
  TIM1::CCER::CC3P::Value0::Set();              //non-inverted/rising edge
  TIM1::CCER::CC3NP::Value0::Set();             //This bit is used in conjunction with CC1P to define the polarity of TI1FP1 and TI2FP1. 
  
  TIM1::CCER::CC2E::Value1::Set();              //This bit determines if a capture of the counter value can actually be done into the input capture/compare register 1 (TIMx_CCR1) or not. 1: Capture enabled.
  TIM1::CCER::CC3E::Value1::Set();              //This bit determines if a capture of the counter value can actually be done into the input capture/compare register 1 (TIMx_CCR1) or not. 1: Capture enabled.

  
  TIM1::DIER::CC2IE::Value1::Set();             //Capture/Compare 1 interrupt enable
  TIM1::DIER::CC3IE::Value1::Set();             //Capture/Compare 1 interrupt enable
  /* TIM1 setup end */
  
  return 1;
}
}

std::size_t buttonposition;
std::size_t previouspositionbutton;
std::size_t IsPressedButton;

extern ResistanceThermometer ResistanceThermometerDirect;
extern ResistanceThermometer ResistanceThermometerReverse;

extern MeasurementTask measurementTask;

InjectedChannel channelResistanceThermometerDirect(static_cast<IInjectedChannelNotifier&>(ResistanceThermometerDirect));
InjectedChannel channelResistanceThermometerReverse(static_cast<IInjectedChannelNotifier&>(ResistanceThermometerReverse));

ResistanceThermometer ResistanceThermometerDirect(static_cast<IDataProvider&>(channelResistanceThermometerDirect), 0.17918f, 289.5635f);
ResistanceThermometer ResistanceThermometerReverse(static_cast<IDataProvider&>(channelResistanceThermometerReverse), 0.17918f, 289.5635f);

CountManager pulseWaterFlowDirect;
CountManager pulseWaterFlowReverse;

Timer1 timer1(pulseWaterFlowDirect, pulseWaterFlowReverse);

WaterConsumption waterConsumptionDirect(static_cast<IDataProvider&>(pulseWaterFlowDirect), 
                                   static_cast<IFloatDataProvider&>(ResistanceThermometerDirect),
                                   static_cast<ICleanTracker&>(measurementTask),
                                   static_cast<ICleaner&>(pulseWaterFlowDirect));
WaterConsumption waterConsumptionReverse(static_cast<IDataProvider&>(pulseWaterFlowReverse), 
                                   static_cast<IFloatDataProvider&>(ResistanceThermometerReverse),
                                   static_cast<ICleanTracker&>(measurementTask),
                                   static_cast<ICleaner&>(pulseWaterFlowDirect));

Adc<channelResistanceThermometerDirect, channelResistanceThermometerReverse> adc1;
MeasurementTask measurementTask(adc1, waterConsumptionDirect, waterConsumptionReverse);

int main()
{

  using namespace OsWrapper;
  
  Rtos::CreateThread(measurementTask, "measurementTask");

  Rtos::Start();
  
  return 0;
}
