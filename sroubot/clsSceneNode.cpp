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

#include <vector>

#include "clsSceneNode.h"

using namespace Sroubot;

clsSceneNode::clsSceneNode()
{
	mPos[0]=mPos[1]=mPos[2]=0.0f;
	mRot[0]=mRot[1]=mRot[2]=0.0f;
	mSca[0]=mSca[1]=mSca[2]=1.0f;
	mModel=NULL;
	mParent=NULL;
	mMat=NULL;
}
void clsSceneNode::attachModel(clsModel* pModel)
{
	mModel=pModel;
}
void clsSceneNode::detachModel()
{
	mModel=NULL;
}
clsSceneNode* clsSceneNode::createChild()
{
	clsSceneNode* pNode=new clsSceneNode();
	attachChild(pNode);
	pNode->_setParent(this);
	return pNode;
}
void clsSceneNode::attachChild(clsSceneNode* pChild)
{
	for (std::vector<clsSceneNode*>::iterator viter = mChildrenPool.begin(); viter != mChildrenPool.end(); ++viter)
		if (*viter==pChild) return;
	mChildrenPool.push_back(pChild);
}
void clsSceneNode::detachChild(clsSceneNode* pChild)
{
	for (std::vector<clsSceneNode*>::iterator viter = mChildrenPool.begin(); viter != mChildrenPool.end(); ++viter)
		if (*viter==pChild)
		{
			mChildrenPool.erase(viter);
			return;
		}
}
void clsSceneNode::setMaterial(clsMaterial* pMat)
{
	mMat=pMat;
}
clsMaterial* clsSceneNode::getMaterial()
{
	return mMat;
}
void clsSceneNode::_setParent(clsSceneNode* pParent)
{
	mParent=pParent;
}
clsSceneNode* clsSceneNode::getParent()
{
	return mParent;
}
void clsSceneNode::setPos(float x, float y, float z)
{
	mPos[0]=x;
	mPos[1]=y;
	mPos[2]=z;
}
void clsSceneNode::setRot(float x, float y, float z, float a)
{
	mRot[0]=x;
	mRot[1]=y;
	mRot[2]=z;
	mRot[3]=a;
}
void clsSceneNode::setSca(float x, float y, float z)
{
	mSca[0]=x;
	mSca[1]=y;
	mSca[2]=z;
}

float* clsSceneNode::getPos()
{
	return &mPos[0];
}
float* clsSceneNode::getRot()
{
	return &mRot[0];
}
float* clsSceneNode::getSca()
{
	return &mSca[0];
}
void clsSceneNode::draw(PFNGLBINDBUFFERARBPROC pProc)
{
	glPushMatrix();
	glTranslatef(mPos[0],mPos[1],mPos[2]);
	glRotatef(mRot[3],mRot[0],mRot[1],mRot[2]);
	glScalef(mSca[0],mSca[1],mSca[2]);

	if (mMat) mMat->useMe();
	if (mModel) mModel->draw(pProc);
	for (std::vector<clsSceneNode*>::iterator viter = mChildrenPool.begin(); viter != mChildrenPool.end(); ++viter)
	{
		if (mMat) mMat->useMe(); //this has to be done every iteration, because it probably gets overridden by models attached to each children
		(*viter)->draw(pProc);
	}

	glPopMatrix();
}
