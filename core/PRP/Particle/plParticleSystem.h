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

#ifndef _PLPARTICLESYSTEM_H
#define _PLPARTICLESYSTEM_H

#include "PRP/Modifier/plModifier.h"
#include "PRP/Animation/plController.h"
#include "plParticleEmitter.h"

class PLASMA_DLL plParticleSystem : public virtual plModifier {
    CREATABLE(plParticleSystem, kParticleSystem, plModifier)

public:
    enum EffectType {
        kEffectForce = 0x1,
        kEffectMisc = 0x2,
        kEffectConstraint = 0x4
    };

    enum MiscFlags {
        kParticleSystemAlwaysUpdate = 0x1
    };

protected:
    plKey fMaterial;
    unsigned int fXTiles, fYTiles;
    hsVector3 fAccel;
    float fPreSim, fDrag, fWindMult;
    unsigned int fMaxTotalParticles, fNumValidEmitters, fMaxEmitters;
    std::vector<plParticleEmitter*> fEmitters;
    std::vector<plKey> fForces, fEffects, fConstraints;
    std::vector<plKey> fPermaLights;
    plController* fAmbientCtl;
    plController* fDiffuseCtl;
    plController* fOpacityCtl;
    plController* fWidthCtl;
    plController* fHeightCtl;

public:
    plParticleSystem()
        : fXTiles(0), fYTiles(0), fPreSim(0.0f), fDrag(0.0f), fWindMult(0.0f),
          fMaxTotalParticles(0), fNumValidEmitters(0), fMaxEmitters(0),
          fAmbientCtl(NULL), fDiffuseCtl(NULL), fOpacityCtl(NULL),
          fWidthCtl(NULL), fHeightCtl(NULL) { }
    virtual ~plParticleSystem();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getMaterial() const { return fMaterial; }
    unsigned int getXTiles() const { return fXTiles; }
    unsigned int getYTiles() const { return fYTiles; }
    hsVector3 getAccel() const { return fAccel; }
    float getPreSim() const { return fPreSim; }
    float getDrag() const { return fDrag; }
    float getWindMult() const { return fWindMult; }
    unsigned int getMaxTotalParticles() const { return fMaxTotalParticles; }
    plController* getAmbientCtl() const { return fAmbientCtl; }
    plController* getDiffuseCtl() const { return fDiffuseCtl; }
    plController* getOpacityCtl() const { return fOpacityCtl; }
    plController* getWidthCtl() const { return fWidthCtl; }
    plController* getHeightCtl() const { return fHeightCtl; }

    void setMaterial(plKey mat) { fMaterial = mat; }
    void setTiles(unsigned int xtiles, unsigned int ytiles) { fXTiles = xtiles; fYTiles = ytiles; }
    void setAccel(const hsVector3& accel) { fAccel = accel; }
    void setPreSim(float preSim) { fPreSim = preSim; }
    void setDrag(float drag) { fDrag = drag; }
    void setWindMult(float windMult) { fWindMult = windMult; }
    void setMaxTotalParticles(unsigned int max) { fMaxTotalParticles = max; }
    void setAmbientCtl(plController* ctl);
    void setDiffuseCtl(plController* ctl);
    void setOpacityCtl(plController* ctl);
    void setWidthCtl(plController* ctl);
    void setHeightCtl(plController* ctl);

    unsigned int getNumValidEmitters() const { return fNumValidEmitters; }
    unsigned int getMaxEmitters() const { return fMaxEmitters; }
    plParticleEmitter* getEmitter(size_t idx) const { return fEmitters[idx]; }
    void allocEmitters(unsigned int max);
    void setEmitter(size_t idx, plParticleEmitter* emitter);
    void addEmitter(plParticleEmitter* emitter);
    void delEmitter(size_t idx);
    void clearEmitters();

    const std::vector<plKey>& getForces() const { return fForces; }
    std::vector<plKey>& getForces() { return fForces; }
    void addForce(plKey force) { fForces.push_back(force); }
    void delForce(size_t idx) { fForces.erase(fForces.begin() + idx); }
    void clearForces() { fForces.clear(); }

    const std::vector<plKey>& getEffects() const { return fEffects; }
    std::vector<plKey>& getEffects() { return fEffects; }
    void addEffect(plKey force) { fEffects.push_back(force); }
    void delEffect(size_t idx) { fEffects.erase(fEffects.begin() + idx); }
    void clearEffects() { fEffects.clear(); }

    const std::vector<plKey>& getConstraints() const { return fConstraints; }
    std::vector<plKey>& getConstraints() { return fConstraints; }
    void addConstraint(plKey force) { fConstraints.push_back(force); }
    void delConstraint(size_t idx) { fConstraints.erase(fConstraints.begin() + idx); }
    void clearConstraints() { fConstraints.clear(); }

    const std::vector<plKey>& getPermaLights() const { return fPermaLights; }
    std::vector<plKey>& getPermaLights() { return fPermaLights; }
    void addPermaLight(plKey force) { fPermaLights.push_back(force); }
    void delPermaLight(size_t idx) { fPermaLights.erase(fPermaLights.begin() + idx); }
    void clearPermaLights() { fPermaLights.clear(); }
};

#endif
