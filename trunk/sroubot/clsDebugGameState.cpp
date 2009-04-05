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

#include "clsDebugGameState.h"

using namespace Sroubot;

int clsDebugGameState::init()
{
    printf("Initializing Managers\n");

    mSceneManager=new clsSceneManager;
    mMaterialManager=new clsMaterialManager;
    mDataSource=new clsFilesystem;
    mDataSource->open("./data/");

    if (!mSceneManager || !mMaterialManager || !mDataSource) return 1;

    mSceneManager->injectDataSource(mDataSource);
    mSceneManager->injectMaterialManager(mMaterialManager);
    mSceneManager->initExts();

    printf("Inits done\n");

    clsModel* lCube=mSceneManager->loadModel("sb.som");
    mSceneManager->getRootNode()->attachModel(lCube);
    if (lCube) printf("Model loaded\n");

    mRot=.0f;

    return 0;
}
void clsDebugGameState::pause() {}
void clsDebugGameState::resume() {}
void clsDebugGameState::destroy()
{
    if (mSceneManager) delete mSceneManager;
    if (mMaterialManager) delete mMaterialManager;
    if (mDataSource) delete mDataSource;
    mApp=0;
}
void clsDebugGameState::processEvent(SDL_Event pEvent)
{
    if (pEvent.type==SDL_KEYDOWN)
    {
        if (pEvent.key.keysym.sym==SDLK_l) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if (pEvent.key.keysym.sym==SDLK_f) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
void clsDebugGameState::processLogic()
{
    mRot=SDL_GetTicks()/5.0f;
    mSceneManager->getRootNode()->setRot(0.0f,1.0f,0.0f,mRot);
}
void clsDebugGameState::processGraphics()
{
    mSceneManager->draw();
}
