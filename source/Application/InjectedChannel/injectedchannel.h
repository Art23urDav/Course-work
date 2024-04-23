#ifndef INJECTEDCHANNEL
#define INJECTEDCHANNEL

#include "iinjectedchannel.h" // for IInjectedChannel 
#include "idataprovider.h" // for IDataProvider

class InjectedChannel : public IInjectedChannel, IDataProvider
{
  public:
    void SetData(std::uint32_t data);
    
    std::uint32_t GetData();
  private:
    std::uint32_t mData;
};

#endif