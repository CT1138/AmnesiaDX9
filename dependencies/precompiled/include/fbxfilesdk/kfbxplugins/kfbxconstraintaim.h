/*!  \file kfbxconstraintaim.h
 */

#ifndef FBXFILESDK_KFBXPLUGINS_KFBXCONSTRAINTAIM_H
#define FBXFILESDK_KFBXPLUGINS_KFBXCONSTRAINTAIM_H

/**************************************************************************************

 Copyright (C) 2001 - 2010 Autodesk, Inc. and/or its licensors.
 All Rights Reserved.

 The coded instructions, statements, computer programs, and/or related material 
 (collectively the "Data") in these files contain unpublished information 
 proprietary to Autodesk, Inc. and/or its licensors, which is protected by 
 Canada and United States of America federal copyright law and by international 
 treaties. 
 
 The Data may not be disclosed or distributed to third parties, in whole or in
 part, without the prior written consent of Autodesk, Inc. ("Autodesk").

 THE DATA IS PROVIDED "AS IS" AND WITHOUT WARRANTY.
 ALL WARRANTIES ARE EXPRESSLY EXCLUDED AND DISCLAIMED. AUTODESK MAKES NO
 WARRANTY OF ANY KIND WITH RESPECT TO THE DATA, EXPRESS, IMPLIED OR ARISING
 BY CUSTOM OR TRADE USAGE, AND DISCLAIMS ANY IMPLIED WARRANTIES OF TITLE, 
 NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE OR USE. 
 WITHOUT LIMITING THE FOREGOING, AUTODESK DOES NOT WARRANT THAT THE OPERATION
 OF THE DATA WILL BE UNINTERRUPTED OR ERROR FREE. 
 
 IN NO EVENT SHALL AUTODESK, ITS AFFILIATES, PARENT COMPANIES, LICENSORS
 OR SUPPLIERS ("AUTODESK GROUP") BE LIABLE FOR ANY LOSSES, DAMAGES OR EXPENSES
 OF ANY KIND (INCLUDING WITHOUT LIMITATION PUNITIVE OR MULTIPLE DAMAGES OR OTHER
 SPECIAL, DIRECT, INDIRECT, EXEMPLARY, INCIDENTAL, LOSS OF PROFITS, REVENUE
 OR DATA, COST OF COVER OR CONSEQUENTIAL LOSSES OR DAMAGES OF ANY KIND),
 HOWEVER CAUSED, AND REGARDLESS OF THE THEORY OF LIABILITY, WHETHER DERIVED
 FROM CONTRACT, TORT (INCLUDING, BUT NOT LIMITED TO, NEGLIGENCE), OR OTHERWISE,
 ARISING OUT OF OR RELATING TO THE DATA OR ITS USE OR ANY OTHER PERFORMANCE,
 WHETHER OR NOT AUTODESK HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH LOSS
 OR DAMAGE. 

**************************************************************************************/
#include <fbxfilesdk/fbxfilesdk_def.h>

#include <fbxfilesdk/kfbxplugins/kfbxconstraint.h>
#include <fbxfilesdk/kfbxplugins/kfbxgroupname.h>
#include <fbxfilesdk/kfbxmath/kfbxvector4.h>

#include <fbxfilesdk/components/kbaselib/klib/kerror.h>

#include <fbxfilesdk/fbxfilesdk_nsbegin.h>

class KFbxSdkManager;

/** An aim constraint governs an object's orientation so that the object points to other objects.
  * For example, you can use the aim constraint to point a light at an object or group of objects.
  * \nosubgrouping
  */
class KFBX_DLL KFbxConstraintAim : public KFbxConstraint
{
    KFBXOBJECT_DECLARE(KFbxConstraintAim,KFbxConstraint);

public:
    /**
      * \name Properties
      */
    //@{
        /** This property handles the rotation offset value.
          *
          * Default value is (0, 0, 0).
          */
        KFbxTypedProperty<fbxDouble3> RotationOffset;

        /** This property provides access to the object or objects which are the targets.
          */
        KFbxTypedProperty<fbxReference> AimAtObjects;

        /** This property provides access to the object being aimed.
          */
        KFbxTypedProperty<fbxReference> ConstrainedObject;

        /** This property handles world up type.
          */
        KFbxTypedProperty<fbxEnum> WorldUpType;

        /** This property handles world up object.
          */
        KFbxTypedProperty<fbxReference> WorldUpObject;

        /** This property handles world up vector.
          *
          * Default value is (0, 1, 0).
          */
        KFbxTypedProperty<fbxDouble3> WorldUpVector;

        /** This property handles up vector.
          *
          * Default value is (0, 1, 0).
          */
        KFbxTypedProperty<fbxDouble3> UpVector;

        /** This property enables you set a specific axis for the constrained object to orient towards.
          *
          * Default value is (1, 0, 0).
          */
        KFbxTypedProperty<fbxDouble3> AimVector;
        
        /** This property handles whether to affect the rotation around X axis.
          *
          * Default value is true.
          */
        KFbxTypedProperty<fbxBool1> AffectX;

        /** This property handles whether to affect the rotation around  Y axis.
          *
          * Default value is true.
          */
        KFbxTypedProperty<fbxBool1> AffectY;

        /** This property handles whether to affect the rotation around  Z axis.
          *
          * Default value is true.
          */
        KFbxTypedProperty<fbxBool1> AffectZ;
    //@}
    

public:
    /** \enum EAimConstraintWorldUpType Constraint world up type, which has the same meaning with Maya
      * - \e eAimAtSceneUp
      * - \e eAimAtObjectUp
      * - \e eAimAtObjectRotationUp
      * - \e eAimAtVector
      * - \e eAimAtNone
      * - \e eAimAtCount
      */
    typedef enum 
    {
        eAimAtSceneUp,
        eAimAtObjectUp,
        eAimAtObjectRotationUp,
        eAimAtVector,
        eAimAtNone,
        eAimAtCount
    } EAimConstraintWorldUpType;

    /** Set the constraint lock state.
      * \param pLock The new state of the lock flag.
      */
    inline void SetLock(bool pLock) { Lock.Set(pLock); }

    /** Retrieve the constraint lock state.
      * \return The current value of the lock flag.
      */
    inline bool GetLock()            { return Lock.Get(); }

    /** Set the weight of the constraint.
      * \param pWeight The new weight value.
      */
    void SetWeight(double pWeight);

    /** Set the rotation offset.
      * \param pRotation The new rotation offset vector.
      */
    virtual void SetOffset(KFbxVector4 pRotation);

    /** Retrieve the constraint rotation offset.
      * \return The current rotation offset vector.
      */
    KFbxVector4 GetOffset() const;

    /** Add a source to the constraint.
      * \param pObject New source object.
      * \param pWeight Weight of the source object.
      */
    void AddConstraintSource(KFbxObject* pObject, double pWeight = 100);

    /** Retrieve the constraint source count.
      * \return Current constraint source count.
      */
    int GetConstraintSourceCount() const;

    /** Retrieve a constraint source object.
      * \param pIndex The specified index.
      * \return Current source at the specified index.
      */
    KFbxObject* GetConstraintSource(int pIndex) const;

    /** Set the constrained object.
      * \param pObject The constrained object.
      */
    void SetConstrainedObject(KFbxObject* pObject);

    /** Retrieve the constrained object.
      * \return Current constrained object.
      */
    KFbxObject* GetConstrainedObject() const;

    /** Set the world up type.
      * \param pType The world up type.
      */
    void SetWorldUpType(EAimConstraintWorldUpType pType);

    /** Retrieve the world up type.
      * \return Current world up type.
      */
    EAimConstraintWorldUpType GetWorldUpType() const;

    /** Set the world up object.
      * \param pObject The new world up object.
      */
    void SetWorldUpObject(KFbxObject* pObject);

    /** Retrieve the world up object.
      * \return The current world up object.
      */
    KFbxObject* GetWorldUpObject() const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
    KFbxConstraintAim(KFbxSdkManager& pManager, char const* pName);

    virtual bool ConstructProperties(bool pForceSet);

    virtual EConstraintType GetConstraintType() const;
#endif // #ifndef DOXYGEN_SHOULD_SKIP_THIS
};

inline EFbxType FbxTypeOf( KFbxConstraintAim::EAimConstraintWorldUpType const &pItem ) { return eENUM; }

#include <fbxfilesdk/fbxfilesdk_nsend.h>

#endif // FBXFILESDK_KFBXPLUGINS_KFBXCONSTRAINTAIM_H

