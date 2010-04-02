#ifndef _PLPSEUDOLINKEFFECTMSG_H
#define _PLPSEUDOLINKEFFECTMSG_H

#include "plMessage.h"

DllClass plPseudoLinkEffectMsg : public plMessage {
    CREATABLE(plPseudoLinkEffectMsg, kPseudoLinkEffectMsg, plMessage)

protected:
    plKey fLinkObjKey, fAvatarKey;

public:
    plPseudoLinkEffectMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
