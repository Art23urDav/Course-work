#ifndef IDATAPROVIDER
#define IDATAPROVIDER

class IDataProvider
{
  public:
    virtual std::uint32_t GetData() const = 0;
};

#endif