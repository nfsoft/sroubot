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

#include "clsBncNode.h"

namespace Sroubot
  {

    clsBncNode::clsBncNode (char pValue=0)
    {
      mValue=pValue;
      mWeight=0;
      mChildL=0;
      mChildR=0;
    }
    int clsBncNode::countChildren (clsBncNode* pNode)
    {
      if (mChildR!=0) return 2;
      if (mChildL!=0) return 1;
      return 0;
    }
    void clsBncNode::injectChild (clsBncNode* pChild)
    {
      int i=countChildren();

      if (i==1) mChildR=aChild;
      else if (i==0) mChildL=aChild;
    }
    clsBncNode* clsBncNode::join (clsBncNode* pChild)
    {
      clsBncNode* lPar=new clsBncNode;

      lPar->setWeight(mWeight+pChild->getWeight());
      lPar->injectChild(pChild);
      lPar->injectChild(this);

      return lPar;
    }
    clsBncNode* clsBncNode::getChildL ()
    {
      return mChildL;
    }
    clsBncNode* clsBncNode::getChildR ()
    {
      return mChildR;
    }
    char clsBncNode::isLeaf ()
    {
      if (mChildL==0) return 1; else return 0;
    }
    unsigned char clsBncNode::getValue ()
    {
      return mValue;
    }
    unsigned int clsBncNode::getWeight ()
    {
      return mWeight;
    }
    void clsBncNode::setWeight (unsigned int pWeight)
    {
      mWeight=pWeight;
    }
  }
