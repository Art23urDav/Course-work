#ifndef ADC
#define ADC

#include "iUpdater.h" // for IUpdater
#include <iostream> // TODO ������� ����� ��������� ������ ���

class Adc : public IUpdater
{
public:
  void Update() const override
  {
    std::cout << "adc"; // TODO ������� ����� ��������� ������ ���
  }
  
};
#endif