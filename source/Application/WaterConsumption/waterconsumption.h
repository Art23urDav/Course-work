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
      mDataProvider(dataProvider), 
      mFloatDataProvider(floatDataProvider),
      mCleanTracker(iCleanTracker),
      mCleaner(iCleaner)
  {
    
  }
  void Update() override;
  const IDataProvider& mDataProvider;
  const IFloatDataProvider& mFloatDataProvider;
  ICleanTracker& mCleanTracker;
  ICleaner& mCleaner;
  float waterConsumption = std::numeric_limits<float>::signaling_NaN();
private:
  float Calculate(std::uint32_t numberPulses, float temp) const;
  float PulsesPerLiter = 7.5f;
  float Coefficient1ForWaterDensity = 995.7f;
  float Coefficient2ForWaterDensity = 0.984f;  
  float Coefficient3ForWaterDensity = 0.000483f;
};
#endif