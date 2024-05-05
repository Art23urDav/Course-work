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
    float mValue = 0.0f;
    float Calculate(std::uint32_t adcCode);
    
};

#endif