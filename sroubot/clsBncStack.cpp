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

#include "clsBncStack.h"

namespace Sroubot
  {
    clsBncStack::clsBncStack ()
    {
      mStack=0;
      mSize=0;
    }
    clsBncStack::~clsBncStack ()
    {
      if (mStack)
      {
        unsigned int i;

        for (i=0; i<mSize; i++) free(mStack[i]);
        free(mStack);
      }
    }
    clsBncNode clsBncStack::pop ()
    {
      clsBncNode lRet;

      if (mSize==0) return 0;
      mSize--;
      lRet=mStack[mSize];
      mStack=(clsBncNode*)realloc(mStack, mSize*sizeof(clsBncNode));
      return lRet;
    }
    void clsBncStack::push (clsBncNode pHayFork)
    {
      mSize++;
      mStack=(clsBncNode*)realloc(mStack, mSize*sizeof(clsBncNode));
      mStack[mSize-1]=pHayFork;
    }
    unsigned int clsBncStack::size ()
    {
      return mSize;
    }
    clsBncNode clsBncStack::top (unsigned int pOffset)
    {
      if (mSize==0) return 0;
      return mStack[mSize-pOffset-1];
    }
  }
