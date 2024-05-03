#include "rtos.hpp"         // for Rtos
#include "mailbox.hpp"      // for Mailbox
#include "event.hpp"        // for Event

#include "mytask.hpp"       // for MyTask
#include "led1task.hpp"     // for Led1Task
#include "myled1task.h"     // for MyLed1Task
#include "myled2task.h"     // for MyLed2Task
#include "mypin.h"          // for for MyPin
//#include "myfirsttask.h"    // for MyFirstTask
//#include "buttontask.h"   //for ButtonTask
#include "rccregisters.hpp" // for RCC

#include  "buttonnextmode.h"

#include "Application/Diagnostic/GlobalStatus.hpp"
#include "gpioaregisters.hpp"  // for GPIOA
#include "gpiocregisters.hpp"  // for GPIOC

#include "adc1registers.hpp" // 
#include "adccommonregisters.hpp"
#include <iostream>

std::uint32_t SystemCoreClock = 16'000'000U;


extern "C" {
int __low_level_init(void)
{
  //Switch on external 16 MHz oscillator
  RCC::CR::HSION::On::Set();
 // while (RCC::CR::HSIRDY::NotReady::IsSet())
  {

  }
  //Switch system clock on external oscillator
  RCC::CFGR::SW::Hsi::Set();
//  while (!RCC::CFGR::SWS::Hsi::IsSet())
 {

  }
  //Switch on clock on PortA and PortC
  RCC::AHB1ENRPack<
      RCC::AHB1ENR::GPIOCEN::Enable,
      RCC::AHB1ENR::GPIOAEN::Enable
  >::Set();

  RCC::APB2ENR::SYSCFGEN::Enable::Set();
  

  //LED1 on PortA.5, set PortA.5 as output
  GPIOA::MODER::MODER5::Output::Set();

  /* LED2 on PortC.9, LED3 on PortC.8, LED4 on PortC.5 so set PortC.5,8,9 as output */
  GPIOC::MODERPack<
      GPIOC::MODER::MODER5::Output,
      GPIOC::MODER::MODER8::Output,
      GPIOC::MODER::MODER9::Output
  >::Set();

  RCC::APB2ENR::ADC1EN::Enable::Set();
  
  return 1;
}
}

MyPin<GPIOC, 5> led4;
MyPin<GPIOC, 8> led3;
MyPin<GPIOC, 9> led2;
MyLed2Task myLed2Task(led2, 100ms);
MyLed2Task myLed3Task(led3, 100ms);
MyLed2Task myLed4Task(led4, 500ms);

ButtonNextMode<GPIOC, 13> button;

OsWrapper::Event event{500ms, 1};

//MyTask myTask(event, UserButton::GetInstance());
//Led1Task led1Task(event, LedsController::GetInstance());



OsWrapper::Event buttonEvent(500ms, 1);
OsWrapper::MailBox<int, 1> buttonMailBox;
//ButtonTask buttonTask(buttonMailBox);
//MyFirstTask myFirstTask;

int main()
{
  GPIOA::MODER::MODER0::Analog::Set();
  
  ADC1::CR1::RES::Bits12::Set();
  
  ADC1::CR1::JDISCEN::Enable::Set();
  
  ADC1::CR2::CONT::SingleConversion::Set();
  ADC1::CR2::EOCS::SequenceConversion::Set();
  
  ADC_Common::CCR::TSVREFE::Enable::Set();
  
  ADC1::JSQR::JL::Conversions2::Set();
  ADC1::JSQR::JSQ1::Channel17::Set();
  //ADC1::JSQR::JSQ2::Channel0::Set();
  
  ADC1::SMPR1::SMP16::Cycles480::Set();
  
  ADC1::CR2::ADON::Enable::Set(); // turn on ADC
  
  ADC_Common::CCR::TSVREFE::Enable::Set();
    
  std::float_t adcCodeTemp;
  std::float_t adcCodePoten;
 
    
  for(;;)
  {
    ADC1::CR2::JSWSTART::On::Set(); // start transformation

    while(!ADC1::SR::JEOC::ConversionComplete::IsSet())
    {
      
    }
    adcCodePoten = (ADC1::JDR1::JDATA::Get());
    adcCodeTemp = (ADC1::JDR2::JDATA::Get());
   // adcCodePoten= (adcCodePoten * 3.3f) / 4095;
    
    std::cout << "V = " << adcCodePoten <<std::endl;
    std::cout << "t = " << adcCodeTemp <<std::endl;
    
    
  }
  
  
  
  
  /*using namespace OsWrapper;
  
  Rtos::CreateThread(myLed2Task, "MyLed2Task", ThreadPriority::lowest);
  Rtos::CreateThread(myLed3Task, "MyLed3Task", ThreadPriority::lowest);
  Rtos::CreateThread(myLed4Task, "MyLed4Task", ThreadPriority::lowest);
//Rtos::CreateThread(myTask, "myTask", ThreadPriority::lowest);
//Rtos::CreateThread(led1Task, "Led1Task");
//  Rtos::CreateThread(myFirstTask, "MyFirstTask", ThreadPriority::highest);
//  Rtos::CreateThread(buttonTask, "ButtonTask", ThreadPriority::normal);
  Rtos::Start();
*/
  return 0;
}
