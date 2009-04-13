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

#include "clsMaterialManager.h"
#include <vector>
#include <string.h>
#include <iostream>

#include <stdlib.h>

using namespace Sroubot;

clsMaterialManager::~clsMaterialManager()
{
	for (std::map<std::string,clsMaterial*>::iterator viter=mMaterialPool.begin();viter!=mMaterialPool.end();viter++)
		delete viter->second;
	mMaterialPool.clear();
}
void clsMaterialManager::injectDataSource(clsDataSource* pDataSource)
{
	mDataSource=pDataSource;
}
int clsMaterialManager::loadMaterialScript(const std::string pFilename)
{
	if (mDataSource->get(pFilename.c_str())<0) return -1;

	std::vector<std::string> lCmd;
	char lLine[256], *lPos, *lPos2;
	unsigned int lMatCount=0, lLineCount=1;
	std::string lMatName;
	clsMaterial* lMat=NULL;

	while (!mDataSource->eof())
	{
		lCmd.clear();
		mDataSource->readLine(lLine,256);

		if (lLine[strlen(lLine)-1]<' ') lLine[strlen(lLine)-1]=0; // removes eol characters
		if (lLine[strlen(lLine)-1]<' ') lLine[strlen(lLine)-1]=0; // just in case someone uses cr+lf or some other form of two-byte eol

		unsigned int lLength=strlen(lLine);
		lPos=lLine;
		while (lPos<lLine+lLength)
		{
			lPos2=strchr(lPos,'\t');
			if (!lPos2) lPos2=lPos+strlen(lPos);
			lPos2[0]=0;
			lCmd.push_back(std::string(lPos));
			lPos=lPos2+1;
		}

/*		for (unsigned int i=0;i<lCmd.size();i++)
			std::cout << "[" << lCmd[i] << "]";
		std::cout << std::endl; */

		if (lCmd[0]=="name") {
			if (lMat)
			{
				mMaterialPool.insert(std::pair<std::string,clsMaterial*>(lMatName,lMat));
				lMatCount++;
				printf("Material '%s' loaded.\n",lMatName.c_str());
			}
			if (lCmd.size()!=2)
				fprintf(stderr,"Error parsing material script %s (line %u), 'name' element needs 1 argument\n",pFilename.c_str(),lLineCount);
			else {
				lMat=new clsMaterial();
				lMatName=lCmd[1];
			}
		} else if (lCmd[0]=="ambi") {
			if (!lMat)
				fprintf(stderr,"Error parsing material script %s (line %u), 'name' element has to be first\n",pFilename.c_str(),lLineCount);
			else if (lCmd.size()!=5)
				fprintf(stderr,"Error parsing material script %s (line %u), 'ambi' element needs 4 arguments\n",pFilename.c_str(),lLineCount);
			else {
				lMat->setAmbient(atof(lCmd[1].c_str()),atof(lCmd[2].c_str()),atof(lCmd[3].c_str()),atof(lCmd[4].c_str()));
			}
		} else if (lCmd[0]=="diff") {
			if (!lMat)
				fprintf(stderr,"Error parsing material script %s (line %u), 'name' element has to be first\n",pFilename.c_str(),lLineCount);
			else if (lCmd.size()!=5)
				fprintf(stderr,"Error parsing material script %s (line %u), 'diff' element needs 4 arguments\n",pFilename.c_str(),lLineCount);
			else {
				lMat->setDiffuse(atof(lCmd[1].c_str()),atof(lCmd[2].c_str()),atof(lCmd[3].c_str()),atof(lCmd[4].c_str()));
			}
		} else if (lCmd[0]=="spec") {
			if (!lMat)
				fprintf(stderr,"Error parsing material script %s (line %u), 'name' element has to be first\n",pFilename.c_str(),lLineCount);
			else if (lCmd.size()!=5)
				fprintf(stderr,"Error parsing material script %s (line %u), 'spec' element needs 4 arguments\n",pFilename.c_str(),lLineCount);
			else {
				lMat->setSpecular(atof(lCmd[1].c_str()),atof(lCmd[2].c_str()),atof(lCmd[3].c_str()),atof(lCmd[4].c_str()));
			}
		} else if (lCmd[0]=="emis") {
			if (!lMat)
				fprintf(stderr,"Error parsing material script %s (line %u), 'name' element has to be first\n",pFilename.c_str(),lLineCount);
			else if (lCmd.size()!=5)
				fprintf(stderr,"Error parsing material script %s (line %u), 'emis' element needs 4 arguments\n",pFilename.c_str(),lLineCount);
			else {
				lMat->setEmission(atof(lCmd[1].c_str()),atof(lCmd[2].c_str()),atof(lCmd[3].c_str()),atof(lCmd[4].c_str()));
			}
		} else if (lCmd[0]=="shin") {
			if (!lMat)
				fprintf(stderr,"Error parsing material script %s (line %u), 'name' element has to be first\n",pFilename.c_str(),lLineCount);
			else if (lCmd.size()!=2)
				fprintf(stderr,"Error parsing material script %s (line %u), 'shin' element needs 1 argument\n",pFilename.c_str(),lLineCount);
			else {
				lMat->setShininess(atof(lCmd[1].c_str()));
			}
		} else if (lCmd.size()!=0) { //ignore empty lines
			fprintf(stderr,"Error parsing material script %s (line %u), unknown element '%s' found\n",pFilename.c_str(),lLineCount,lCmd[0].c_str());
		}

		lLineCount++;
	}
	if (lMat) //ending last material
	{
		mMaterialPool.insert(std::pair<std::string,clsMaterial*>(lMatName,lMat));
		lMatCount++;
		printf("Material '%s' loaded.\n",lMatName.c_str());
	}
	return lMatCount;
}
clsMaterial* clsMaterialManager::getMaterial(const std::string pMaterialName)
{
	std::map<std::string,clsMaterial*>::iterator lResult=mMaterialPool.find(pMaterialName);
	if (lResult==mMaterialPool.end()) {
		fprintf(stderr,"Material %s not loaded!\n",pMaterialName.c_str());
		return NULL;
	} else
		return lResult->second;
}
