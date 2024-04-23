#include "injectedchannel.h" // for InjectedChannel

void InjectedChannel::SetData(std::uint32_t data) override
{
  mData = data;
}

std::uint32_t InjectedChannel::GetData() const override
{
  return mData;
}