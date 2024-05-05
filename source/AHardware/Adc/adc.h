#ifndef ADC
#define ADC

#include "iUpdater.h" // for IUpdater
#include "iinjectedchannel.h" // for IInjectedChannel

#include "adc1registers.hpp" // for ADC1
#include "adccommonregisters.hpp" // for ADC

template<auto& ...injectedChannels>
class Adc : public IUpdater
{
public:
  void Update() override
  {
    
    ADC1::CR2::JSWSTART::On::Set(); //Start Conversation
    while(!ADC1::SR::JEOC::ConversionComplete::IsSet())
    {
    }
    constexpr std::uint32_t jdr1Addr = 0x4001203C;
    auto* jdrRegisterPonter = reinterpret_cast<std::uint32_t*>(jdr1Addr);
    for (auto& it : mInjectedChannels)
    {
      const auto value = *jdrRegisterPonter;
      jdrRegisterPonter++;
      it->SetData(value);
    }
  }
private:
    std::array<IInjectedChannel*, sizeof ...(injectedChannels)> mInjectedChannels = {static_cast<IInjectedChannel*> (&injectedChannels)... };
  
};
#endif