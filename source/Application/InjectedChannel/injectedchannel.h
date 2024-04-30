#ifndef INJECTEDCHANNEL
#define INJECTEDCHANNEL

#include <cstdint> // for std::uint32_t
#include "iinjectedchannel.h" // for IInjectedChannel 
#include "idataprovider.h" // for IDataProvider
#include "iinjectedchannelnotifare.h" // for IInjectedChannel 

class InjectedChannel : public IInjectedChannel, public IDataProvider
{
  public:
    InjectedChannel(IInjectedChannelNotifare& notifare) : mNotifare(notifare)
    {
    }
    void SetData(std::uint32_t data) override;
    
    std::uint32_t GetData() const override;
  private:
    std::uint32_t mData;
    IInjectedChannelNotifare& mNotifare;
};

#endif