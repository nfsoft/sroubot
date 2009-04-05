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

#include <math.h>

#include "clsMath.h"

using namespace Sroubot;

float clsMath::v3_norm(float* pV)
{
	return sqrt(pV[0]*pV[0]+pV[1]*pV[1]+pV[2]*pV[2]);
}
void clsMath::v3_normalize(float* pV)
{
	float lNorm=v3_norm(pV);
	pV[0]/=lNorm;
	pV[1]/=lNorm;
	pV[2]/=lNorm;
}
float clsMath::v3_dotProduct(float* pV1, float* pV2)
{
	return pV1[0]*pV2[0]+pV1[1]*pV2[1]+pV1[2]*pV2[2];
}
void clsMath::v3_crossProduct(float* pV1, float* pV2, float* pV3)
{
	pV3[0]=pV1[0]*pV2[0];
	pV3[1]=pV1[1]*pV2[1];
	pV3[2]=pV1[2]*pV2[2];
}
