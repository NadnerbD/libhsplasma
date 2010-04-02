#ifndef _PLGENERICPHYSICAL_H
#define _PLGENERICPHYSICAL_H

#include "plPhysical.h"
#include "Math/hsGeometry3.h"
#include "Math/hsQuat.h"
#include "Util/hsBitVector.h"

/**************
 * plGenericPhysical attempts to be a generic interface for plHKPhysical,
 * plODEPhysical and plPXPhysical.  When setting properties, try to set as
 * many as possible, as the three engines may have different ways of storing
 * the same physical data.  Obviously, more work still needs to be done here,
 * but hopefully this generic interface will cover most cases and eventually
 * provide fully working physical objects for all 3 engines.
 **************/

DllClass plGenericPhysical : public plPhysical {
    CREATABLE(plGenericPhysical, kGenericPhysical, plPhysical)

public:
    enum PhysType {
        kPhysNone, kPhysHavok, kPhysODE, kPhysX, kNumPhysTypes
    };

protected:
    // Generic properties
    PhysType fInternalType;
    unsigned char* fInternalBuffer;
    size_t fInternalSize;

    // Shared Properties
    float fMass, fFriction, fRestitution;
    plSimDefs::Bounds fBounds;
    plSimDefs::Group fGroup;
    unsigned int fCategory;
    unsigned short fLOSDBs;
    plKey fObjectKey, fSceneNode, fSubWorld, fSoundGroup;
    hsVector3 fPos;
    hsQuat fRot;
    hsVector3 fDimensions, fOffset;
    float fRadius, fLength;

    hsBitVector fProps;
    hsTArray<hsVector3> fVerts;
    hsTArray<unsigned int> fIndices;

    // Havok Properties
    unsigned int fUnk1, fUnk2;
    bool fHKBool1, fHKBool2;

    // ODE Properties
    //unsigned int fUnk1, fUnk2;
    size_t fTMDSize;
    unsigned char* fTMDBuffer;

    // PhysX Properties
    unsigned int fReportsOn;

    void IReadHKPhysical(hsStream* S, plResManager* mgr);
    void IReadODEPhysical(hsStream* S, plResManager* mgr);
    void IReadPXPhysical(hsStream* S, plResManager* mgr);
    void IWriteHKPhysical(hsStream* S, plResManager* mgr);
    void IWriteODEPhysical(hsStream* S, plResManager* mgr);
    void IWritePXPhysical(hsStream* S, plResManager* mgr);

public:
    plGenericPhysical();
    virtual ~plGenericPhysical();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getMass() const { return fMass; }
    float getFriction() const { return fFriction; }
    float getRestitution() const { return fRestitution; }
    plSimDefs::Bounds getBoundsType() const { return fBounds; }
    plSimDefs::Group getGroup() const { return fGroup; }
    unsigned int getCategory() const { return fCategory; }
    unsigned short getLOSDBs() const { return fLOSDBs; }
    unsigned int getReportsOn() const { return fReportsOn; }

    plKey getObject() const { return fObjectKey; }
    plKey getSceneNode() const { return fSceneNode; }
    plKey getSubWorld() const { return fSubWorld; }
    plKey getSoundGroup() const { return fSoundGroup; }
    hsVector3 getPos() const { return fPos; }
    hsQuat getRot() const { return fRot; }

    bool getProperty(size_t prop) const { return fProps.get(prop); }
    void setProperty(size_t prop, bool value) { fProps.set(prop, value); }

    hsVector3 getDimensions() const { return fDimensions; }
    hsVector3 getOffset() const { return fOffset; }
    float getRadius() const { return fRadius; }
    float getLength() const { return fLength; }

    const hsTArray<hsVector3>& getVerts() const { return fVerts; }
    hsTArray<hsVector3>& getVerts() { return fVerts; }
    const hsTArray<unsigned int>& getIndices() const { return fIndices; }
    hsTArray<unsigned int>& getIndices() { return fIndices; }
    size_t getTMDSize() const { return fTMDSize; }
    const unsigned char* getTMDBuffer() const { return fTMDBuffer; }

    void setMass(float mass) { fMass = mass; }
    void setFriction(float friction) { fFriction = friction; }
    void setRestitution(float restitution) { fRestitution = restitution; }
    void setBoundsType(plSimDefs::Bounds bounds) { fBounds = bounds; }
    void setGroup(plSimDefs::Group group) { fGroup = group; }
    void setCategory(unsigned int category) { fCategory = category; }
    void setLOSDBs(unsigned short los) { fLOSDBs = los; }
    void setReportsOn(unsigned int reports) { fReportsOn = reports; }

    void setObject(plKey object) { fObjectKey = object; }
    void setSceneNode(plKey node) { fSceneNode = node; }
    void setSubWorld(plKey world) { fSubWorld = world; }
    void setSoundGroup(plKey group) { fSoundGroup = group; }
    void setPos(const hsVector3& pos) { fPos = pos; }
    void setRot(const hsQuat& rot) { fRot = rot; }

    void setDimensions(const hsVector3& box) { fDimensions = box; }
    void setOffset(const hsVector3& offset) { fOffset = offset; }
    void setRadius(float radius) { fRadius = radius; }
    void setLength(float length) { fLength = length; }
    void setVerts(size_t numVerts, const hsVector3* verts);
    void setIndices(size_t numIndices, const unsigned int* indices);
    void setTMDBuffer(size_t tmdSize, const unsigned char* tmdBuffer);

    // Direct baked data buffer access (Currently only for PhysX with baked data)
    PhysType getBufferType() const;
    size_t getBufferSize() const;
    const unsigned char* getBufferData() const;
    void setBuffer(PhysType type, size_t size, const unsigned char* data);
};

#endif
