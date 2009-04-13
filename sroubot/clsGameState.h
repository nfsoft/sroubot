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

#ifndef _CLSGAMESTATE_H_
#define _CLSGAMESTATE_H_

#include "clsApplication.h"

namespace Sroubot
{
	class clsGameState
	{
	protected:
		clsApplication* mApp;
	public:
		~clsGameState()
		{
			if (mApp) fprintf(stderr,"clsGameState was not destroyed properly!");
		}
		virtual int init() = 0;
		virtual void pause() = 0;
		virtual void resume() = 0;
		virtual void destroy() = 0;
		virtual void processEvent(SDL_Event pEvent) = 0;
		virtual void processLogic(unsigned int pTicks) = 0;
		virtual void processGraphics() = 0;
	};
}

#endif
