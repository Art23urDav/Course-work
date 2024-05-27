#ifndef ICLEANTRACKER
#define ICLEANTRACKER

class ICleanTracker
{
public:
    virtual bool CleanCheck() const = 0;
    virtual void ResetCleanChecker() = 0;
};

#endif