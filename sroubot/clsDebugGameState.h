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

#ifndef _CLSDEBUGGAMESTATE_H_
#define _CLSDEBUGGAMESTATE_H_

#include "clsGameState.h"

#include "clsFilesystem.h"
#include "clsSceneManager.h"
#include "clsMaterialManager.h"

namespace Sroubot
{
    class clsDebugGameState: public clsGameState
    {
    private:
        clsSceneManager* mSceneManager;
        clsMaterialManager* mMaterialManager;
        clsDataSource* mDataSource;
        float mRot;
    public:
        clsDebugGameState(const clsApplication* pApp)
        {
            mApp=(clsApplication*)pApp;
        }
        int init();
        void pause();
        void resume();
        void destroy();
        void processEvent(SDL_Event pEvent);
        void processLogic();
        void processGraphics();
    };
}

#endif

