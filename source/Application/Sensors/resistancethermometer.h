#ifndef RESISTANCETHERMOMETER
#define RESISTANCETHERMOMETER

#include <cstdint> // for std::uint32_t
#include "idataprovider.h" // for IDataProvider
#include "iinjectedchannelnotifier.h" // for IInjectedChannel 
#include "idataprovider.h" // for IFloatDataProvider

class ResistanceThermometer : public IInjectedChannelNotifier, public IFloatDataProvider
{
  public:
    ResistanceThermometer(IDataProvider& dataProvider) : mDataProvider(dataProvider)
    {
    }
    void NotifyDataArrived() override;
    float GetData() const override;
  private:
    IDataProvider& mDataProvider;
    std::uint32_t mAdcCode = 0U;
    float maxAdcCode = 4096.0f;
    float maxVoltageAdc = 3.0f;
    float mValue = 0.0f;
    float Calculate(std::uint32_t adcCode);
    float voltage = 0.0f;
    float koefK = 0.0f;
    float koefB = 0.0f;
    float maxTempResistor = 150.0f; 
    float minTempResistor = 0.0f; 
    float maxVoltageResistor = 3.0f; // TODO measure experimentally
    float minVoltageResistor = 0.0f; // TODO measure experimentally
    
};

#endif