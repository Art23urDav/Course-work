#include "waterconsumption.h"

void WaterConsumption::Update()
{
  waterConsumption = Calculate(mNumberOfPulses.GetData(), mTemperature.GetData());
  if(mCleanTracker.CleanCheck())
  {
    mCleaner.Clean();
    mCleanTracker.ResetCleanChecker();
  }
}

float WaterConsumption::Calculate(std::uint32_t numberPulses, float temp) const
{
  return (numberPulses * PulsesPerLiter) * 
    (Coefficient1ForWaterDensity / (Coefficient2ForWaterDensity + Coefficient3ForWaterDensity * temp)) / convertFromLInMcube;
}