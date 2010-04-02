#ifndef _PLSOUND_H
#define _PLSOUND_H

#include "PRP/Object/plSceneObject.h"
#include "Math/hsGeometry3.h"
#include "plEAXEffects.h"

DllClass plSound : public plSynchedObject {
    CREATABLE(plSound, kSound, plSynchedObject)

public:
    enum Property {
        kPropIs3DSound = 0x1,
        kPropDisableLOD = 0x2,
        kPropLooping = 0x4,
        kPropAutoStart = 0x8,
        kPropLocalOnly = 0x10,
        kPropLoadOnlyOnCall = 0x20,
        kPropFullyDisabled = 0x40,
        kPropDontFade = 0x80,
        kPropIncidental = 0x100
    };

    enum Type {
        kStartType = 0,
        kSoundFX = kStartType, kAmbience, kBackgroundMusic, kGUISound,
        kNPCVoices, kNumTypes
    };

    enum StreamType {
        kNoStream, kStreamFromRAM, kStreamFromDisk, kStreamCompressed
    };

public:
    DllClass plFadeParams {
    public:
        enum Type { kLinear, kLogarithmic, kExponential };

        float fLengthInSecs, fVolStart, fVolEnd;
        unsigned char fType;
        bool fStopWhenDone, fFadeSoftVol;
        float fCurrTime;

    public:
        plFadeParams();

        void read(hsStream* S);
        void write(hsStream* S);
        void prcWrite(pfPrcHelper* prc);
        void prcParse(const pfPrcTag* tag);
    };

protected:
    unsigned char fType, fPriority;
    bool fPlaying;
    double fTime;
    int fMaxFalloff, fMinFalloff;
    int fOuterVol, fInnerCone, fOuterCone;
    float fCurrVolume, fDesiredVol, fFadedVolume;
    unsigned int fProperties;
    plEAXSourceSettings fEAXSettings;
    plFadeParams fFadeInParams, fFadeOutParams;
    plKey fSoftRegion, fSoftOcclusionRegion, fDataBuffer;
    plString fSubtitleId;

public:
    plSound();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);

public:
    unsigned char getType() const { return fType; }
    unsigned char getPriority() const { return fPriority; }
    bool isPlaying() const { return fPlaying; }
    double getTime() const { return fTime; }
    int getMaxFalloff() const { return fMaxFalloff; }
    int getMinFalloff() const { return fMinFalloff; }
    int getOuterVol() const { return fOuterVol; }
    int getInnerCone() const { return fInnerCone; }
    int getOuterCone() const { return fOuterCone; }
    float getCurrVolume() const { return fCurrVolume; }
    float getDesiredVolume() const { return fDesiredVol; }
    float getFadedVolume() const { return fFadedVolume; }
    unsigned int getProperties() const { return fProperties; }
    plKey getSoftRegion() const { return fSoftRegion; }
    plKey getSoftOcclusionRegion() const { return fSoftOcclusionRegion; }
    plKey getDataBuffer() const { return fDataBuffer; }
    plString getSubtitleId() const { return fSubtitleId; }

    void setType(unsigned char type) { fType = type; }
    void setPriority(unsigned char priority) { fPriority = priority; }
    void setPlaying(bool playing) { fPlaying = playing; }
    void setTime(double time) { fTime = time; }
    void setFalloff(int min, int max) { fMinFalloff = min; fMaxFalloff = max; }
    void setOuterVol(int vol) { fOuterVol = vol; }
    void setCone(int inner, int outer) { fInnerCone = inner; fOuterCone = outer; }
    void setCurrVolume(float vol) { fCurrVolume = vol; }
    void setDesiredVolume(float vol) { fDesiredVol = vol; }
    void setFadedVolume(float vol) { fFadedVolume = vol; }
    void setProperties(unsigned int props) { fProperties = props; }
    void setSoftRegion(plKey region) { fSoftRegion = region; }
    void setSoftOcclusionRegion(plKey region) { fSoftOcclusionRegion = region; }
    void setDataBuffer(plKey buffer) { fDataBuffer = buffer; }
    void setSubtitleId(const plString& subtitle) { fSubtitleId = subtitle; }

    const plEAXSourceSettings& getEAXSettings() const { return fEAXSettings; }
    const plFadeParams& getFadeInParams() const { return fFadeInParams; }
    const plFadeParams& getFadeOutParams() const { return fFadeOutParams; }

    plEAXSourceSettings& getEAXSettings() { return fEAXSettings; }
    plFadeParams& getFadeInParams() { return fFadeInParams; }
    plFadeParams& getFadeOutParams() { return fFadeOutParams; }
};

#endif
