#ifndef _PLMAINTAINERSMARKERMODIFIER_H
#define _PLMAINTAINERSMARKERMODIFIER_H

#include "plModifier.h"

DllClass plMaintainersMarkerModifier : public plMultiModifier {
    CREATABLE(plMaintainersMarkerModifier, kMaintainersMarkerModifier,
              plMultiModifier)

public:
    enum { kBroken, kRepaired, kCalibrated, kNumCalibratedLevels };

private:
    unsigned int fCalibrated;

public:
    plMaintainersMarkerModifier();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned int getCalibration() const { return fCalibrated; }
    void setCalibration(unsigned int cal) { fCalibrated = cal; }
};

#endif
