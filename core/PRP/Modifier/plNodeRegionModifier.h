#ifndef _PLNODEREGIONMODIFIER_H
#define _PLNODEREGIONMODIFIER_H

#include "plModifier.h"

DllClass plNodeRegionModifier : public plSingleModifier {
    CREATABLE(plNodeRegionModifier, kNodeRegionModifier, plSingleModifier)

protected:
    bool fEnabled;

public:
    plNodeRegionModifier();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
