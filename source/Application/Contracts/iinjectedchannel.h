#ifndef IINJECTEDCHANNEL
#define IINJECTEDCHANNEL

class IInjectedChannel
{
  public:
    virtual void SetData(std::uint32_t data) = 0;
};

#endif