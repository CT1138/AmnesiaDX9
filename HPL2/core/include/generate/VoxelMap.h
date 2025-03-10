/*
 * Copyright © 2009-2020 Frictional Games
 * 
 * This file is part of Amnesia: The Dark Descent.
 * 
 * Amnesia: The Dark Descent is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version. 

 * Amnesia: The Dark Descent is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Amnesia: The Dark Descent.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef HPL_VOXEL_MAP_H
#define HPL_VOXEL_MAP_H

#include "system/SystemTypes.h"
#include "math/MathTypes.h"
#include "graphics/GraphicsTypes.h"
#include "generate/GenerateTypes.h"

namespace hpl {

	//-------------------------------

	class iLowLevelGraphics;

	//-------------------------------

	class cVoxelMap
	{
	public:
		cVoxelMap(const cVector3l& avSize);
		~cVoxelMap();

		/////////////////////////////////
		// Action
		void SetVoxel(const cVector3l &avPos, char alVal);

		/////////////////////////////////
		// Properties
		const cVector3l& GetSize(){ return mvSize; }
		void SetSize(const cVector3l& avSize);

		float GetVoxelSize(){ return mfVoxelSize;}
		void SetVoxelSize(float afX){ mfVoxelSize = afX;}

		const cVector3f& GetPosition(){ return mvPosition;}
		void SetPosition(const cVector3f& avPos){ mvPosition = avPos;}

		/////////////////////////////////
		// Debug
		void DebugRender(iLowLevelGraphics *apLowGfx, const cColor &aCol);

	private:
		unsigned char* mpData;

		cVector3l mvSize;

		float mfVoxelSize;
		cVector3f mvPosition;
	};

}
#endif // HPL_VOXEL_MAP_H
