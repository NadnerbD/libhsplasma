#ifndef _PLANIMPATH_H
#define _PLANIMPATH_H

#include "PRP/plCreatable.h"
#include "Math/hsAffineParts.h"
#include "Math/hsMatrix44.h"
#include "plTMController.h"

DllClass plAnimPath : public plCreatable {
    CREATABLE(plAnimPath, kAnimPath, plCreatable)

public:
    enum Flags {
        kNone = 0,
        kFavorFwdSearch = 0x1,
        kFavorBwdSearch = 0x2,
        kCalcPosOnly = 0x4,
        kFarthest = 0x8,
        kWrap = 0x10,
        kIncrement = 0x20
    };

protected:
   unsigned int fAnimPathFlags;
   float fMinDistSq, fLength;
   hsMatrix44 fLocalToWorld, fWorldToLocal;
   plCompoundController* fController;
   plTMController* fTMController;
   hsAffineParts fParts;

public:
    plAnimPath();
    virtual ~plAnimPath();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned int getFlags() const { return fAnimPathFlags; }
    float getMinDistSq() const { return fMinDistSq; }
    float getLength() const { return fLength; }
    const hsMatrix44& getLocalToWorld() const { return fLocalToWorld; }
    const hsMatrix44& getWorldToLocal() const { return fWorldToLocal; }
    plCompoundController* getController() const { return fController; }
    plTMController* getTMController() const { return fTMController; }
    const hsAffineParts& getAffineParts() const { return fParts; }

    void setFlags(unsigned int flags) { fAnimPathFlags = flags; }
    void setMinDistSq(float dist) { fMinDistSq = dist; }
    void setLength(float length) { fLength = length; }
    void setLocalToWorld(const hsMatrix44& l2w) { fLocalToWorld = l2w; }
    void setWorldToLocal(const hsMatrix44& w2l) { fWorldToLocal = w2l; }
    void setAffineParts(const hsAffineParts& parts) { fParts = parts; }

    void setController(plCompoundController* controller);
    void setTMController(plTMController* controller);
};

#endif
