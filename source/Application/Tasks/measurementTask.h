#ifndef MEASUREMENTTASK
#define MEASUREMENTTASK

#include "thread.hpp" //For OsWrapper::Thread

class MeasurementTask : public OsWrapper::Thread<128>
{
  public:
    MeasurementTask(IUpdater& adc) : _adc(adc){}
    void Execute() override
    {
      for(;;)
      {
        _adc.Update();
        Sleep(3000ms); // TODO �������� �� 3 ���
      }
    }
private:
  IUpdater& _adc;  
};

#endif //MEASUREMENTTASK