/*
 Sroubot - open source game
 Copyright (C) 2008,2009 NewFolder Software

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _CLSMATERIAL_H_
#define _CLSMATERIAL_H_

#include <SDL/SDL_opengl.h>

namespace Sroubot
{

	class clsMaterial
	{
	private:
		bool mAmbientUsed;
		float mAmbient[4];
		bool mDiffuseUsed;
		float mDiffuse[4];
		bool mSpecularUsed;
		float mSpecular[4];
		bool mEmissionUsed;
		float mEmission[4];
		bool mShininessUsed;
		float mShininess;
	public:
		clsMaterial();
		void setAmbient(float pR, float pG, float pB, float pA, bool pUsed=true);
		void setDiffuse(float pR, float pG, float pB, float pA, bool pUsed=true);
		void setSpecular(float pR, float pG, float pB, float pA, bool pUsed=true);
		void setEmission(float pR, float pG, float pB, float pA, bool pUsed=true);
		void setShininess(float pE, bool pUsed=true);
		void useMe();
	};
}

#endif
