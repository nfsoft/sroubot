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

#ifndef _CLSMATH_H_
#define _CLSMATH_H_

namespace Sroubot
{

	class clsMath
	{
	public:
		static float v3_norm(float* pV);
		static void v3_normalize(float* pV);
		static float v3_dotProduct(float* pV1, float* pV2);
		static void v3_crossProduct(float* pV1, float* pV2, float* pV3);
	};
}


#endif

