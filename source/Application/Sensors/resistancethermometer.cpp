#include "resistancethermometer.h" //for ResistanceThermometers

void ResistanceThermometer::NotifyDataArrived()
{
  mValue = Calculate(mAdcCode.GetData());
}

float ResistanceThermometer::Calculate(std::uint32_t adcCode) const 
{
  return mGain * static_cast<float>(adcCode) - mOffset;
}

float ResistanceThermometer::GetData() const
{
  return mValue;
}