#ifndef MEASUREMENTTASK
#define MEASUREMENTTASK

#include <cstdint> // for std::uint8_t
#include <chrono> // for 'ms' literal
#include "thread.hpp" //For OsWrapper::Thread
#include "icleantracker.h" // for ICleanTracker

class MeasurementTask : public OsWrapper::Thread<512>, public ICleanTracker
{
  public:
    MeasurementTask(IUpdater& adc, IUpdater& waterConsumptionDirect, IUpdater& waterConsumptionReverse) : 
      mAdc(adc),
      mWaterConsumptionDirect(waterConsumptionDirect),
      mWaterConsumptionReverse(waterConsumptionReverse){}
    void Execute() override
    {
      for(;;)
      {
        mAdc.Update();
        mWaterConsumptionDirect.Update();
        mWaterConsumptionReverse.Update();
        UpdateCleanFlag();
        Sleep(mCalculationPeriod); // TODO поменять на 3 мин
      }
    }
    bool CleanCheck() const override
    {
      return mIsCleanNeeded;
    }
    void ResetCleanChecker() override
    {
      mIsCleanNeeded = false;
    }
private:
  const std::chrono::milliseconds mCalculationPeriod = 3000ms;
  const std::uint32_t oneHourCounts = 3600000ms / mCalculationPeriod;
  IUpdater& mAdc; 
  IUpdater& mWaterConsumptionDirect;
  IUpdater& mWaterConsumptionReverse;
  std::uint8_t mCounter = 0U;
  bool mIsCleanNeeded = false;
  void UpdateCleanFlag()
  {
    mCounter++;
    if(mCounter == oneHourCounts) 
    {
      mCounter = 0U;
      mIsCleanNeeded = true;
    }   
  }
  
};

#endif //MEASUREMENTTASK