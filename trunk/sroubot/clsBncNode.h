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

#ifndef _CLSBNCNODE_H_
#define _CLSBNCNODE_H_

#include <stdlib.h>

namespace Sroubot
  {
    class clsBncNode;

    class clsBncNode
      {
      private:
        char mValue;
        unsigned int mWeight;
        clsBncNode* mChildL;
        clsBncNode* mChildR;

      public:
        clsBncNode (char pValue=0);
        unsigned char countChildren ();
        void injectChild (clsBncNode* pChild);
        clsBncNode* join (clsBncNode* pChild);
        clsBncNode* getChildL ();
        clsBncNode* getChildR ();
        char isLeaf ();
        unsigned char getValue ();
        unsigned int getWeight ();
        void setWeight (unsigned int pWeight);
      }
  }

#endif
