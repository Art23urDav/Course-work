#include "resistancethermometers.h" //for ResistanceThermometers

void ResistanceThermometers::NotifyDataArrived()
{
  temp = (mDataProvider.GetData());
}
