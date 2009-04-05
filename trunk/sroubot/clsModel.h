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

#ifndef _CLSMODEL_H_
#define _CLSMODEL_H_

#include <cstdlib>
#include <string.h>

#include "clsMaterial.h"

namespace Sroubot
{
    struct sMesh
    {
        clsMaterial *mMat;

        float *mArray;
        unsigned int *mIndices;
        unsigned int numVertices;
        unsigned int numIndices;

        unsigned int VBOArray;
        unsigned int VBOIndices;
    };

    class clsModel
    {
    private:
        sMesh *mMeshes;
        unsigned int mNumMeshes;
    public:
        clsModel();
        ~clsModel();
        void allocateMeshes(unsigned int pNumMeshes);
        void injectMesh(unsigned int pID, sMesh* pMesh);
        void draw(PFNGLBINDBUFFERARBPROC pProc);
    };
}

#endif
