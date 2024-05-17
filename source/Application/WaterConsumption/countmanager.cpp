#include "countmanager.h"

std::uint32_t CountManager::UpdateNumberPulses()
{
  numberPulses++;
}

void CountManager::Clean()
{
  numberPulses = 0U;
}

std::uint32_t CountManager::GetData() const
{
  return numberPulses;
}