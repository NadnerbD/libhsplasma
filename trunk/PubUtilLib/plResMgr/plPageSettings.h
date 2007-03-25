#ifndef _PLPAGESETTINGS_H
#define _PLPAGESETTINGS_H

#include "../../DynLib/PlasmaVersions.h"
#include "../../DynLib/PageID.h"
#include "plPageInfo.h"

struct plAgeSettings {
    unsigned int startDateTime, dayLength, maxCapacity, lingerTime;
    signed int sequencePrefix;
    unsigned int releaseVersion;
    std::vector<plPageInfo*> pages;
};

#endif
