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

#include "clsModel.h"
#include <stdio.h>
#include <GL/gl.h>

using namespace Sroubot;

clsModel::clsModel()
{
	mMeshes=NULL;
	mNumMeshes=0;
}
clsModel::~clsModel()
{
	if (mMeshes) free(mMeshes);
}
void clsModel::allocateMeshes(unsigned int pNumMeshes)
{
	mNumMeshes=pNumMeshes;
	mMeshes=(sMesh*)realloc(mMeshes,mNumMeshes*sizeof(sMesh));
}
void clsModel::injectMesh(unsigned int pID, sMesh* pMesh)
{
	memcpy(&mMeshes[pID],pMesh,sizeof(sMesh));
}

void clsModel::draw(PFNGLBINDBUFFERARBPROC pProc)
{
	glColor3f(0.5f,0.5f,0.5f);

//fprintf(stdout,"drawing..\n");

	for (unsigned int i=0;i<mNumMeshes;++i)
	{
		//mMeshes[i].mMat->useMe();
		if (pProc)
		{
			pProc(GL_ARRAY_BUFFER_ARB, mMeshes[i].VBOArray);
			glVertexPointer(3, GL_FLOAT, 32, NULL);
			glNormalPointer( GL_FLOAT, 32, (char*)12);
			//glTexCoordPointer(2, GL_FLOAT, 8, (char*)6);

			//fprintf(stdout,"semidone..\n");

			pProc(GL_ELEMENT_ARRAY_BUFFER_ARB, mMeshes[i].VBOIndices);
			glDrawElements(GL_TRIANGLES, mMeshes[i].numIndices, GL_UNSIGNED_INT, NULL);
		}
		else
		{
			glVertexPointer(3, GL_FLOAT, 32, mMeshes[i].mArray);
			glNormalPointer( GL_FLOAT, 32, (mMeshes[i].mArray)+3);
			//glTexCoordPointer(2, GL_FLOAT, 8, (char*)6);
			//fprintf(stdout,"semidone.h..........\n");

			glDrawElements(GL_TRIANGLES, mMeshes[i].numIndices, GL_UNSIGNED_INT, mMeshes[i].mIndices);
		}
	}
	glPopMatrix();

//fprintf(stdout,"done..\n");
}
