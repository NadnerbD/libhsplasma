#include "pfGUIRadioGroupCtrl.h"
#include "pfGUICheckBoxCtrl.h"

pfGUIRadioGroupCtrl::pfGUIRadioGroupCtrl() : fDefaultValue(0) {
    fFlags.setName(kAllowNoSelection, "kAllowNoSelection");
}

void pfGUIRadioGroupCtrl::read(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::read(S, mgr);

    fControls.setSize(S->readInt());
    for (size_t i=0; i<fControls.getSize(); i++)
        fControls[i] = mgr->readKey(S);

    fDefaultValue = S->readShort();
}

void pfGUIRadioGroupCtrl::write(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::write(S, mgr);

    S->writeInt(fControls.getSize());
    for (size_t i=0; i<fControls.getSize(); i++)
        mgr->writeKey(S, fControls[i]);

    S->writeShort(fDefaultValue);
}

void pfGUIRadioGroupCtrl::IPrcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::IPrcWrite(prc);

    prc->startTag("Items");
    prc->writeParam("Default", fDefaultValue);
    prc->endTag();
    for (size_t i=0; i<fControls.getSize(); i++)
        fControls[i]->prcWrite(prc);
    prc->closeTag();
}

void pfGUIRadioGroupCtrl::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Items") {
        fDefaultValue = tag->getParam("Default", "0").toInt();
        fControls.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fControls.getSize(); i++) {
            fControls[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}
