#include "waterconsumption.h"
#include <iostream>                   // for std::cout

void WaterConsumption::Update()
{
  waterConsumption = Calculate(mDataProvider.GetData(), mFloatDataProvider.GetData());
  if(mCleanTracker.CleanCheck())
  {
    mCleaner.Clean();
    mCleanTracker.ResetCleanChecker();
  }
  std::cout <<  waterConsumption << std::endl; // TODO delete 
}

float WaterConsumption::Calculate(std::uint32_t numberPulses, float temp) const
{
  return (numberPulses / PulsesPerLiter) * 
    (Coefficient1ForWaterDensity / (Coefficient2ForWaterDensity + Coefficient3ForWaterDensity * temp));
}