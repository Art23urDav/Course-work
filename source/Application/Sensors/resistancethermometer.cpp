#include "resistancethermometer.h" //for ResistanceThermometers
#include <iostream>                   // for std::cout

void ResistanceThermometer::NotifyDataArrived()
{
  mValue = Calculate(mDataProvider.GetData());
  std::cout << mValue << std::endl;
}

float ResistanceThermometer::Calculate(std::uint32_t adcCode)
{
  voltage = (maxVoltageAdc * adcCode) / maxAdcCode;
  koefK = (maxTempResistor - minTempResistor) / (maxVoltageResistor - minVoltageResistor);
  koefB = maxVoltageResistor - (koefK - maxTempResistor);
  mValue = koefK * voltage + koefB; 
  return mValue;
}

float ResistanceThermometer::GetData() const
{
  return mValue;
}