#ifndef IINJECTEDCHANNELNOTIFIER
#define IINJECTEDCHANNELNOTIFIER

class IInjectedChannelNotifier
{
  public:
      virtual void NotifyDataArrived() = 0;
};

#endif