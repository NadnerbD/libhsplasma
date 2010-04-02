#include "plServerReplyMsg.h"
#include "Debug/plDebug.h"

plServerReplyMsg::plServerReplyMsg() : fType(kUnInit) { }

void plServerReplyMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fType = S->readInt();
}

void plServerReplyMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    S->writeInt(fType);
}

void plServerReplyMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("ReplyType");
    prc->writeParamHex("value", (unsigned int)fType);
    prc->endTag(true);
}

void plServerReplyMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ReplyType") {
        fType = tag->getParam("value", "0").toInt();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
