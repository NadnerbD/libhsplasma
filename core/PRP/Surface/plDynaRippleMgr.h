/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLDYNARIPPLEMGR_H
#define _PLDYNARIPPLEMGR_H

#include "plDynaDecalMgr.h"
#include "PRP/Animation/plAnimPath.h"

class PLASMA_DLL plDynaRippleMgr : public virtual plDynaDecalMgr {
    CREATABLE(plDynaRippleMgr, kDynaRippleMgr, plDynaDecalMgr)

protected:
    hsVector3 fInitUVW, fFinalUVW;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plDynaRippleVSMgr : public virtual plDynaRippleMgr {
    CREATABLE(plDynaRippleVSMgr, kDynaRippleVSMgr, plDynaRippleMgr)

protected:
    plKey fWaveSetBase;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plDynaTorpedoMgr : public virtual plDynaRippleMgr {
    CREATABLE(plDynaTorpedoMgr, kDynaTorpedoMgr, plDynaRippleMgr)
};


class PLASMA_DLL plDynaTorpedoVSMgr : public virtual plDynaTorpedoMgr {
    CREATABLE(plDynaTorpedoVSMgr, kDynaTorpedoVSMgr, plDynaTorpedoMgr)

protected:
    plKey fWaveSetBase;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plDynaPuddleMgr : public virtual plDynaRippleMgr {
    CREATABLE(plDynaPuddleMgr, kDynaPuddleMgr, plDynaRippleMgr)
};

class PLASMA_DLL plDynaWakeMgr : public virtual plDynaRippleMgr {
    CREATABLE(plDynaWakeMgr, kDynaWakeMgr, plDynaRippleMgr)

protected:
    hsVector3 fDefaultDir;
    plAnimPath* fAnimPath;
    float fAnimWgt, fVelWgt;

public:
    plDynaWakeMgr() : fAnimPath(NULL), fAnimWgt(0.0f), fVelWgt(0.0f) { }
    virtual ~plDynaWakeMgr();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    void setAnimPath(plAnimPath* path);
};

#endif
