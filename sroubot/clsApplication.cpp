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

#include "clsApplication.h"
#include <time.h>
#include <math.h>

using namespace Sroubot;

clsApplication::clsApplication()
{

}
clsApplication::~clsApplication()
{

}
int clsApplication::setupSDL()
{
	printf("Initializing SDL\n");
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 )
	{
		fprintf(stderr,"Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	mScreen = SDL_SetVideoMode( 640, 480, 32, SDL_OPENGL );
	if ( !mScreen )
	{
		fprintf(stderr,"Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}
	return 0;
}

#define PERSPECTIVE(fovx,aspect,near,far) \
  float xmax = near * tan(fovx * M_PI / 360.0); \
  float xmin = -xmax; \
  float ymin = xmin / (aspect); \
  float ymax = xmax / (aspect); \
  float m[16] = {(2.0f*near)/(xmax-xmin),0.0f                   ,0.0f                       ,0.0f , \
                 0.0f                   ,(2.0f*near)/(ymax-ymin),0.0f                       ,0.0f , \
                 (xmax+xmin)/(xmax-xmin),(ymax+ymin)/(ymax-ymin),-(far+near)/(far-near)     ,-1.0f, \
                 0.0f                   ,0.0f                   ,-(2.0f*far*near)/(far-near),0.0f }; \
  glMultMatrixf(m);

int clsApplication::setupOpenGL()
{
	printf("Initializing OpenGL\n");

	glClearColor( 0.0f, 0.8f, 0.0f, 0.0f );

	glViewport( 0, 0, 640, 480 );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	PERSPECTIVE(45.0f, 4.0f/3.0f, 0.1f, 100.0f );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	glEnable(GL_LIGHTING);

	float LightAmbient[]= { 0.8f, 0.5f, 0.5f, 1.0f };
	float LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
	float LightPosition[]= { 40.0f, 5.0f, 0.0f, 1.0f };

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glEnable(GL_LIGHT1);

	return 0;
}
void clsApplication::pushGS(clsGameState* pGameState)
{
	mGSStack.push(pGameState);
}
void clsApplication::popGS()
{
	mGSStack.pop();
}
int clsApplication::run()
{

	int lErr;
	lErr=setupSDL();
	if (lErr) return lErr;
	lErr=setupOpenGL();
	if (lErr) return lErr;

	pushGS(new clsDebugGameState(this));

	mGSStack.top()->init();

	mRun=true;

	while (mRun)
	{
		mGSStack.top()->processLogic();

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mGSStack.top()->processGraphics();
		SDL_GL_SwapBuffers();

		SDL_Event lEvent;
		while (SDL_PollEvent(&lEvent))
		{
			switch (lEvent.type)
			{
			case SDL_KEYDOWN:
				if (lEvent.key.keysym.sym==SDLK_ESCAPE) mRun=false;
			case SDL_KEYUP:
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				mGSStack.top()->processEvent(lEvent);
				break;
			case SDL_QUIT:
				mRun = 0;
				break;
			}
		}
	}

	return 0;
}
