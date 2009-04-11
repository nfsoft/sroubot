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

#include "clsFilesystem.h"
#include <stdlib.h>
#include <string.h>

using namespace Sroubot;

clsFilesystem::clsFilesystem()
{
	mDir="";
	mFile=0;
}
clsFilesystem::~clsFilesystem()
{
	close();
}
int clsFilesystem::open(std::string pSourceIdentificator)
{
	mDir=pSourceIdentificator;
	close();
	return 0;
}
int clsFilesystem::close()
{
	if (mFile)
	{
		fclose(mFile);
		mFile=0;
		return 0;
	}
	else
		return -1;
}
bool clsFilesystem::exists(std::string pName)
{
	FILE* lFp=NULL;
	std::string lBuffer=mDir+pName;
	lFp=fopen(lBuffer.c_str(),"rb");
	if (lFp!=NULL)
	{
		fclose(lFp);
		return true;
	}
	return false;
}
int clsFilesystem::get(std::string pName)
{
	close();
	std::string lBuffer=mDir+pName;
	mFile=fopen(lBuffer.c_str(),"rb");
	if (mFile==0)
	{
		fprintf(stderr,"Error opening %s\n",lBuffer.c_str());
		return -1;
	}
	return 0;
}
unsigned int clsFilesystem::seek(unsigned long pOffset)
{
	return fseek(mFile,pOffset,SEEK_SET);
}
unsigned int clsFilesystem::tell()
{
	return ftell(mFile);
}
bool clsFilesystem::eof()
{
	return feof(mFile);
}
int clsFilesystem::read(void *pBuffer, unsigned int pCount)
{
	return (int)fread(pBuffer,1,pCount,mFile);
}
int clsFilesystem::readLine(void *pBuffer, unsigned int pCount)
{
	if (!fgets((char*)pBuffer,pCount,mFile))
		return -(ferror(mFile)!=0); //0 = EOF; -1 = error
	return strlen((char*)pBuffer);
}
unsigned int clsFilesystem::size()
{
	long int lPos, lSize;
	lPos=ftell(mFile);
	fseek(mFile, 0, SEEK_END);
	lSize=ftell(mFile);
	fseek(mFile,lPos,SEEK_SET);
	return lSize;
}
