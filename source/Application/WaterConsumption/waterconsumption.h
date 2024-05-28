#ifndef WATERCONSUMPTION
#define WATERCONSUMPTION

#include <cstdint> // for std::uint32_t
#include <limits> // std::numeric_limits
#include "idataprovider.h" // for IDataProvider and IFloatDataProvider
#include "icleantracker.h"      // for iCleanTracker
#include "icleaner.h"           // for ICleaner
#include "iUpdater.h" // for IUpdater

class WaterConsumption : public IUpdater
{
public:
  WaterConsumption(IDataProvider& dataProvider, IFloatDataProvider& floatDataProvider,
                   ICleanTracker& iCleanTracker, ICleaner& iCleaner) : 
      mNumberOfPulses(dataProvider), 
      mTemperature(floatDataProvider),
      mCleanTracker(iCleanTracker),
      mCleaner(iCleaner)
  {
    
  }
  void Update() override;
  const IDataProvider& mNumberOfPulses;
  const IFloatDataProvider& mTemperature;
  ICleanTracker& mCleanTracker;
  ICleaner& mCleaner;
  float waterConsumption = std::numeric_limits<float>::signaling_NaN();
private:
  float Calculate(std::uint32_t numberPulses, float temp) const;
  float PulsesPerLiter = 0.00222f;
  static constexpr float Coefficient1ForWaterDensity = 995.7f;
  static constexpr float Coefficient2ForWaterDensity = 0.984f;  
  static constexpr float Coefficient3ForWaterDensity = 0.000483f;
  static constexpr float convertFromLInMcube = 1000.0f;
};
#endif