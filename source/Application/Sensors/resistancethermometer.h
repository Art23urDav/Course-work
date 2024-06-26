#ifndef RESISTANCETHERMOMETER
#define RESISTANCETHERMOMETER

#include <cstdint> // for std::uint32_t
#include <limits> // std::numeric_limits
#include "idataprovider.h" // for IDataProvider and IFloatDataProvider
#include "iinjectedchannelnotifier.h" // for IInjectedChannel 

class ResistanceThermometer : public IInjectedChannelNotifier, public IFloatDataProvider
{
  public:
    ResistanceThermometer(IDataProvider& dataProvider, float gain, float offset) : 
      mAdcCode(dataProvider), 
      mGain(gain),
      mOffset(offset)
    {
    }
    void NotifyDataArrived() override;
    float GetData() const override;
  private:
    float Calculate(std::uint32_t adcCode) const;
    const IDataProvider& mAdcCode;
    float mValue = std::numeric_limits<float>::signaling_NaN();
    const float mGain;
    const float mOffset;
};

#endif