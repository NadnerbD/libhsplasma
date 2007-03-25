#ifndef _HSGMATERIAL_H
#define _HSGMATERIAL_H

#include "../../NucleusLib/pnNetCommon/plSynchedObject.h"
#include "../../CoreLib/hsTArray.hpp"

class hsGMaterial : public plSynchedObject {
public:
    enum hsGCompFlags {
        kCompShaded = 0x1,
        kCompEnvironMap = 0x2,
        kCompProjectOnto = 0x4,
        kCompSoftShadow = 0x8,
        kCompSpecular = 0x10,
        kCompTwoSided = 0x20,
        kCompDrawAsSplats = 0x40,
        kCompAdjusted = 0x80,
        kCompNoSoftShadow = 0x100,
        kCompDynamic = 0x200,
        kCompDecal = 0x400,
        kCompIsEmissive = 0x800,    // OBSOLETE
        kCompIsLightMapped = 0x1000,
        kCompNeedsBlendChannel = 0x2000
    };
    
    enum UpdateFlags {
        kUpdateAgain = 0x1
    };

private:
    int LOD;
    hsTArray<plKey*> Layers, PiggyBacks;
    unsigned int compFlags, loadFlags;
    float lastUpdateTime;

public:
    hsGMaterial(PlasmaVer pv = pvUnknown);
    virtual ~hsGMaterial();

    virtual short ClassIndex();
    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

    virtual void readData(hsStream* S);
    virtual void writeData(hsStream* S);

    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif
