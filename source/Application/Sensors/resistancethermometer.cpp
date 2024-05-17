#include "resistancethermometer.h" //for ResistanceThermometers
#include <iostream>                   // for std::cout

void ResistanceThermometer::NotifyDataArrived()
{
  mValue = Calculate(mDataProvider.GetData());
  std::cout <<  mValue << std::endl; // TODO delete 
}

float ResistanceThermometer::Calculate(std::uint32_t adcCode) const 
{
  return mGain * static_cast<float>(adcCode) + mOffset;
}

float ResistanceThermometer::GetData() const
{
  return mValue;
}