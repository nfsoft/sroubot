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

#include "clsMaterial.h"

using namespace Sroubot;

clsMaterial::clsMaterial()
{
	mAmbientUsed=false; mAmbient[0]=.2f; mAmbient[1]=.2f; mAmbient[2]=.2f; mAmbient[3]=1.f;
	mDiffuseUsed=false; mDiffuse[0]=.8f; mDiffuse[1]=.8f; mDiffuse[2]=.8f; mDiffuse[3]=1.f;
	mSpecularUsed=false; mSpecular[0]=0.f; mSpecular[1]=0.f; mSpecular[2]=0.f; mSpecular[3]=1.f;
	mEmissionUsed=false; mEmission[0]=0.f; mEmission[1]=0.f; mEmission[2]=0.f; mEmission[3]=1.f;
	mShininessUsed=false; mShininess=64.f;
}
void clsMaterial::setAmbient(float pR, float pG, float pB, float pA, bool pUsed)
{
	mAmbientUsed=pUsed; mAmbient[0]=pR; mAmbient[1]=pG; mAmbient[2]=pB; mAmbient[3]=pA;
}
void clsMaterial::setDiffuse(float pR, float pG, float pB, float pA, bool pUsed)
{
	mDiffuseUsed=pUsed; mDiffuse[0]=pR; mDiffuse[1]=pG; mDiffuse[2]=pB; mDiffuse[3]=pA;
}
void clsMaterial::setSpecular(float pR, float pG, float pB, float pA, bool pUsed)
{
	mSpecularUsed=pUsed; mSpecular[0]=pR; mSpecular[1]=pG; mSpecular[2]=pB; mSpecular[3]=pA;
}
void clsMaterial::setEmission(float pR, float pG, float pB, float pA, bool pUsed)
{
	mEmissionUsed=pUsed; mEmission[0]=pR; mEmission[1]=pG; mEmission[2]=pB; mEmission[3]=pA;
}
void clsMaterial::setShininess(float pE, bool pUsed)
{
	mShininessUsed=pUsed; mShininess=pE;
}
void clsMaterial::useMe()
{
	if (mAmbientUsed) glMaterialfv(GL_FRONT,GL_AMBIENT,mAmbient);
	if (mDiffuseUsed) glMaterialfv(GL_FRONT,GL_DIFFUSE,mDiffuse);
	if (mSpecularUsed) glMaterialfv(GL_FRONT,GL_SPECULAR,mSpecular);
	if (mEmissionUsed) glMaterialfv(GL_FRONT,GL_EMISSION,mEmission);
	if (mShininessUsed) glMaterialf(GL_FRONT,GL_SHININESS,mShininess);
}
