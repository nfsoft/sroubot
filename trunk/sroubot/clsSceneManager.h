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

#ifndef _CLSSCENEMANAGER_H_
#define _CLSSCENEMANAGER_H_

#include <string>
#include <vector>

#include "clsDataSource.h"
#include "clsModel.h"
#include "clsMaterialManager.h"
#include "clsSceneNode.h"

namespace Sroubot
{
    class clsSceneManager
    {
    private:
        clsDataSource* mDataSource;
        clsMaterialManager* mMaterialManager;
        std::vector<clsModel*> mModelPool;

        PFNGLGENBUFFERSARBPROC mglGenBuffersARB;
        PFNGLBINDBUFFERARBPROC mglBindBufferARB;
        PFNGLBUFFERDATAARBPROC mglBufferDataARB;
        PFNGLDELETEBUFFERSARBPROC mglDeleteBuffersARB;

        clsSceneNode* mCameraNode;
        clsSceneNode* mCameraTarget;

        clsSceneNode* mRootNode;

    public:
        clsSceneManager();
        ~clsSceneManager();
        void initExts();
        void injectDataSource(clsDataSource* pDataSource);
        void injectMaterialManager(clsMaterialManager* pMaterialManager);
        clsModel* loadModel(const std::string pFilename);
        clsModel* duplicateModel(clsModel* pModel);
        clsSceneNode* getRootNode();
        clsSceneNode* getCameraNode();
        clsSceneNode* getCameraTarget();
        void draw();
    };
}


#endif
