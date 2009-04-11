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

#ifndef _CLSDATASOURCE_H_
#define _CLSDATASOURCE_H_

#include <string>

namespace Sroubot
{
	class clsDataSource
	{
	public:
		virtual ~clsDataSource() {}
		virtual int open(std::string pSourceIdentificator) = 0;
		virtual int close() = 0;
		virtual bool exists(std::string pName) = 0;
		virtual int get(std::string pName) = 0;
		virtual unsigned int seek(unsigned long pOffset) = 0;
		virtual unsigned int tell() = 0;
		virtual bool eof() = 0;
		virtual int read(void *pBuffer, unsigned int pCount) = 0;
		virtual int readLine(void *pBuffer, unsigned int pCount) = 0;
		virtual unsigned int size() = 0;
	};
}

#endif
