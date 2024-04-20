#ifndef ADC
#define ADC

#include "iUpdater.h" // for IUpdater
#include <iostream> // TODO удалить после настройки класса АЦП

class Adc : public IUpdater
{
public:
  void Update() const override
  {
    std::cout << "adc"; // TODO удалить после настройки класса АЦП
  }
  
};
#endif