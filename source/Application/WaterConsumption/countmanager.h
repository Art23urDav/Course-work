#ifndef COUNTMANAGER
#define COUNTMANAGER

#include <cstdint> // for std::uint32_t
#include "idataprovider.h" // for IDataProvider
#include "icleaner.h"      // for ICleaner

class CountManager : public IDataProvider, public ICleaner
{
  public:
    std::uint32_t UpdateNumberPulses();
    void Clean() override;
    std::uint32_t GetData() const override;
  private:
    std::uint32_t numberPulses = 0U; 
    bool isCleanNeeded = false;
};
#endif