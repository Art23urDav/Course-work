#ifndef INJECTEDCHANNEL
#define INJECTEDCHANNEL

#include <cstdint> // for std::uint32_t
#include "iinjectedchannel.h" // for IInjectedChannel 
#include "idataprovider.h" // for IDataProvider

class InjectedChannel : public IInjectedChannel, IDataProvider
{
  public:
    void SetData(std::uint32_t data) override;
    
    std::uint32_t GetData() const override;
  private:
    std::uint32_t mData;
};

#endif