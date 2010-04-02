#include "pfGUIDynDisplayCtrl.h"

void pfGUIDynDisplayCtrl::read(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::read(S, mgr);

    fTextMaps.setSize(S->readInt());
    for (size_t i=0; i<fTextMaps.getSize(); i++)
        fTextMaps[i] = mgr->readKey(S);

    fLayers.setSize(S->readInt());
    for (size_t i=0; i<fLayers.getSize(); i++)
        fLayers[i] = mgr->readKey(S);

    if (S->getVer() >= pvPots) {
        fMaterials.setSize(S->readInt());
        for (size_t i=0; i<fMaterials.getSize(); i++)
            fMaterials[i] = mgr->readKey(S);
    }
}

void pfGUIDynDisplayCtrl::write(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::write(S, mgr);

    S->writeInt(fTextMaps.getSize());
    for (size_t i=0; i<fTextMaps.getSize(); i++)
        mgr->writeKey(S, fTextMaps[i]);

    S->writeInt(fLayers.getSize());
    for (size_t i=0; i<fLayers.getSize(); i++)
        mgr->writeKey(S, fLayers[i]);

    if (S->getVer() >= pvPots) {
        S->writeInt(fMaterials.getSize());
        for (size_t i=0; i<fMaterials.getSize(); i++)
            mgr->writeKey(S, fMaterials[i]);
    }
}

void pfGUIDynDisplayCtrl::IPrcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::IPrcWrite(prc);

    prc->writeSimpleTag("TextMaps");
    for (size_t i=0; i<fTextMaps.getSize(); i++)
        fTextMaps[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Layers");
    for (size_t i=0; i<fLayers.getSize(); i++)
        fLayers[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Materials");
    for (size_t i=0; i<fMaterials.getSize(); i++)
        fMaterials[i]->prcWrite(prc);
    prc->closeTag();
}

void pfGUIDynDisplayCtrl::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "TextMaps") {
        fTextMaps.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fTextMaps.getSize(); i++) {
            fTextMaps[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Layers") {
        fLayers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fLayers.getSize(); i++) {
            fLayers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Materials") {
        fMaterials.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMaterials.getSize(); i++) {
            fMaterials[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}
