//#include "measurementTask.h"

//void MeasurementTask::Execute() 
//{
//  for(;;)
//  {
//    _adc.Update();
//    UpdateCleanFlag();
//    Sleep(_calculationPeriod); 
//  }
//}
//
//bool MeasurementTask::CleanCheck() const 
//{
//  return _isCleanNeeded;
//}
//
//void MeasurementTask::ResetCleanChecker() 
//{
//  _isCleanNeeded = false;
//}
//
//void MeasurementTask::UpdateCleanFlag()
//{
//  _counter++;
//  if(_counter == oneHourCounts) 
//  {
//    _counter = 0U;
//    _isCleanNeeded = true;
//  }   
//}