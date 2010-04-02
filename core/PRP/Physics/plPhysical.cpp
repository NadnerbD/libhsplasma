#include "plPhysical.h"

const char* plSimDefs::BoundsNames[] = {
    "(Invalid)", "kBoxBounds", "kSphereBounds", "kHullBounds",
    "kProxyBounds", "kExplicitBounds", "kCylinderBounds"
};

const char* plSimDefs::GroupNames[] = {
    "kGroupStatic", "kGroupAvatarBlocker", "kGroupDynamicBlocker",
    "kGroupAvatar", "kGroupDynamic", "kGroupDetector", "kGroupLOSOnly"
};
