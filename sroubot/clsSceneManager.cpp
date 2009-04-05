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

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include <GL/glu.h>

#include "clsSceneManager.h"
#include "clsMath.h"

using namespace Sroubot;

clsSceneManager::clsSceneManager()
{
    mglGenBuffersARB=0;
    mglBindBufferARB=0;
    mglBufferDataARB=0;
    mglDeleteBuffersARB=0;

    mRootNode=new clsSceneNode();
    mCameraNode=new clsSceneNode();
    mCameraTarget=new clsSceneNode();

    mCameraNode->setPos(30,30,30);
    mCameraTarget->setPos(0,0,0);
}

clsSceneManager::~clsSceneManager()
{
    delete mRootNode;
}

void clsSceneManager::initExts()
{
    mglGenBuffersARB=(PFNGLGENBUFFERSARBPROC) SDL_GL_GetProcAddress("glGenBuffersARB");
    //mglGenBuffersARB=0;
    if (mglGenBuffersARB)
    {
        mglBindBufferARB=(PFNGLBINDBUFFERARBPROC) SDL_GL_GetProcAddress("glBindBufferARB");
        mglBufferDataARB=(PFNGLBUFFERDATAARBPROC) SDL_GL_GetProcAddress("glBufferDataARB");
        mglDeleteBuffersARB=(PFNGLDELETEBUFFERSARBPROC) SDL_GL_GetProcAddress("glDeleteBuffersARB");

        printf("VBOs supported\n");
    }
    else
        printf("INFO: VBOs not supported, gonna be slow\n");

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
}
void clsSceneManager::injectDataSource(clsDataSource* pDataSource)
{
    mDataSource=pDataSource;
}
void clsSceneManager::injectMaterialManager(clsMaterialManager* pMaterialManager)
{
    mMaterialManager=pMaterialManager;
}
clsModel* clsSceneManager::loadModel(const std::string pFilename)
{
    mDataSource->get(pFilename);

    printf("File opened\n");

    clsModel* lModel=new clsModel();
    unsigned int lNumMeshes;
    sMesh lMesh;
    char lFormat[4];
    mDataSource->read(lFormat,3);
    lFormat[3]=0;

    if (strcmp(lFormat,"SOM")!=0)
    {
        fprintf(stderr,"Model is not SOM\n");
        return NULL;
    }

    mDataSource->read(&lNumMeshes,sizeof(unsigned int));

    lModel->allocateMeshes(lNumMeshes);

    for (unsigned int i=0;i<lNumMeshes;i++)
    {
        unsigned char lTmpChar;
        char lTmpMatName[80];
        unsigned int x=0;
        do
        {
            mDataSource->read(&lTmpChar, 1);
            lTmpMatName[x]=lTmpChar;
            x++;
        }
        while (lTmpChar!='\0' && i<80);


        mDataSource->read(&lMesh.numVertices,sizeof(float));

        lMesh.mArray=(float*)malloc(sizeof(float)*8*lMesh.numVertices);

        mDataSource->read(lMesh.mArray,sizeof(float)*8*lMesh.numVertices);

        mDataSource->read(&lMesh.numIndices,sizeof(unsigned int));
        lMesh.mIndices=(unsigned int*)malloc(sizeof(unsigned int)*lMesh.numIndices);
        mDataSource->read(lMesh.mIndices ,sizeof(unsigned int)*lMesh.numIndices);

        //BuildVBO
        if (mglGenBuffersARB)
        {
            //fprintf(stdout,"Generating VBOs\n");
            mglGenBuffersARB(1, &lMesh.VBOArray);
            mglBindBufferARB(GL_ARRAY_BUFFER_ARB, lMesh.VBOArray);
            mglBufferDataARB(GL_ARRAY_BUFFER_ARB, lMesh.numVertices*sizeof(float)*8, lMesh.mArray, GL_STATIC_DRAW_ARB);

            mglGenBuffersARB(1, &lMesh.VBOIndices);
            mglBindBufferARB(GL_ARRAY_BUFFER_ARB, lMesh.VBOIndices);
            mglBufferDataARB(GL_ARRAY_BUFFER_ARB, lMesh.numIndices*sizeof(unsigned int), lMesh.mIndices, GL_STATIC_DRAW_ARB);
        }
        //fprintf(stdout,"Injecting mesh\n");
        lModel->injectMesh(i,&lMesh);
    }

    mModelPool.push_back(lModel);

    return lModel;
}
clsSceneNode* clsSceneManager::getRootNode()
{
    return mRootNode;
}
clsSceneNode* clsSceneManager::getCameraNode()
{
    return mCameraNode;
}
clsSceneNode* clsSceneManager::getCameraTarget()
{
    return mCameraTarget;
}
void clsSceneManager::draw()
{

    float* lEye=mCameraNode->getPos();
    float* lAt=mCameraTarget->getPos();

    glLoadIdentity();
    gluLookAt(lEye[0],lEye[1],lEye[2],lAt[0],lAt[1],lAt[2],0.0f,0.0f,1.0f);

    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(100,0,0);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);

    glColor3f(0,100,0);
    glVertex3f(0,0,0);
    glVertex3f(0,100,0);

    glColor3f(0,0,100);
    glVertex3f(0,0,0);
    glVertex3f(0,0,100);

    glEnd();
    glEnable(GL_LIGHTING);

    /*float x[3], y[3], z[3];
    float mat[16];

    //view dir
    z[0]=lEye[0]-lAt[0];
    z[1]=lEye[1]-lAt[1];
    z[2]=lEye[2]-lAt[2];

    //up
    y[0]=.0f;
    y[1]=1.0f;
    y[2]=.0f;

    clsMath::v3_normalize(z);
    clsMath::v3_crossProduct(y, z, x);
    clsMath::v3_normalize(x);
    clsMath::v3_crossProduct(z, x, y);

    clsMath::v3_normalize(x);
    clsMath::v3_normalize(y);

    mat[ 0] = x[0];
    mat[ 1] = y[0];
    mat[ 2] = -z[0];
    mat[ 3] = 0.0;

    mat[ 4] = x[1];
    mat[ 5] = y[1];
    mat[ 6] = -z[2];
    mat[ 7] = 0.0;

    mat[ 8] = x[2];
    mat[ 9] = y[2];
    mat[10] = -z[2];
    mat[11] = 0.0;

    mat[12] = -(clsMath::v3_dotProduct(x,lEye));
    mat[13] = -(clsMath::v3_dotProduct(y,lEye));
    mat[14] = (clsMath::v3_dotProduct(z,lEye));
    mat[15] = 1.0;

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glLoadMatrixf(mat);*/

    mRootNode->draw(mglBindBufferARB);
}
