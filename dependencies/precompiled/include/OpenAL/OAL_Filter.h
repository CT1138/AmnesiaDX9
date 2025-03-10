#ifndef _OAL_FILTER_H
#define _OAL_FILTER_H

#include "OpenAL/OAL_Types.h"
#include "OAL_LowLevelObject.h"



class cOAL_Filter : public iOAL_LowLevelObject
{
public:
	cOAL_Filter();
	~cOAL_Filter();

	bool CreateLowLevelID();
	bool DestroyLowLevelID();

	void SaveObjectState(){}
	void RestoreObjectState(){}

	bool IsValidObject();

    void SetType ( eOALFilterType aeType );
	void SetGain ( float afGain );
	void SetGainHF ( float afGainHF );
	void SetGainLF ( float afGainHF );

	inline eOALFilterType GetType () { return mType; }
	inline float GetGain () { return mfGain; }
	inline float GetGainHF() { return mfGainHF; }
	inline float GetGainLF() { return mfGainLF; }

protected:
	float	mfGain;
	float	mfGainHF;
	float	mfGainLF;
	eOALFilterType mType;
};

#endif

