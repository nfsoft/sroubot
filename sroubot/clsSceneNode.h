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

#ifndef _CLSSCENENODE_H_
#define _CLSSCENENODE_H_

#include <vector>

#include "clsModel.h"

namespace Sroubot
{
	class clsSceneNode;
	class clsSceneNode
	{
	private:
		clsModel* mModel;
		clsSceneNode* mParent;
		std::vector<clsSceneNode*> mChildrenPool;

		float mPos[3];
		float mRot[4];
		float mSca[3];
	public:
		clsSceneNode();
		void attachModel(clsModel* pModel);
		void detachModel();
		clsSceneNode* createChild();
		void attachChild(clsSceneNode* pChild);
		void detachChild(clsSceneNode* pChild);
		void _setParent(clsSceneNode* pParent); //try not to call this directly !
		clsSceneNode* getParent();

		void setPos(float x, float y, float z);
		void setRot(float x, float y, float z, float a);
		void setSca(float x, float y, float z);

		float* getPos();
		float* getRot();
		float* getSca();

		void draw(PFNGLBINDBUFFERARBPROC pProc);
	};
}


#endif
