#include "measurementTask.h"

void MeasurementTask::Execute() 
{
  for(;;)
  {
    mAdc.Update();
    mWaterConsumptionDirect.Update();
    mWaterConsumptionReverse.Update();
    UpdateCleanFlag();
    Sleep(mCalculationPeriod);
  }
}

bool MeasurementTask::CleanCheck() const 
{
  return mIsCleanNeeded;
}

void MeasurementTask::ResetCleanChecker() 
{
  mIsCleanNeeded = false;
}

void MeasurementTask::UpdateCleanFlag()
{
  mCounter++;
  if(mCounter == oneHourCounts) 
  {
    mCounter = 0U;
    mIsCleanNeeded = true;
  }   
}