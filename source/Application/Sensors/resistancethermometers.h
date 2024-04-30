#ifndef RESISTANCETHERMOMETERS
#define RESISTANCETHERMOMETERS

#include <cstdint> // for std::uint32_t
#include "idataprovider.h" // for IDataProvider
#include "iinjectedchannelnotifare.h" // for IInjectedChannel 

class ResistanceThermometers : public IInjectedChannelNotifare
{
  public:
    ResistanceThermometers(IDataProvider& dataProvider) : mDataProvider(dataProvider)
    {
    }
    void NotifyDataArrived() override;
  private:
    IDataProvider& mDataProvider;
    std::uint16_t temp = 0U;
  
};

#endif