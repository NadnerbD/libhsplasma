#ifndef _PLFACINGCONDITIONALOBJECT_H
#define _PLFACINGCONDITIONALOBJECT_H

#include "plConditionalObject.h"

DllClass plFacingConditionalObject : public plConditionalObject {
    CREATABLE(plFacingConditionalObject, kFacingConditionalObject,
              plConditionalObject)

protected:
    float fTolerance;
    bool fDirectional;

public:
    plFacingConditionalObject();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
