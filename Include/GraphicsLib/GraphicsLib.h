///////////////////////////////////////////////////////////////////////
// GraphicsLib - Utility library graphics
// Copyright � 1999-2010  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_GRAPHICSLIB_GRAPHICSLIB_H_
#define INCLUDED_GRAPHICSLIB_GRAPHICSLIB_H_
#pragma once

// This is a master include file for the Graphics Library Package
#if defined(BUILDGRLIB)
	#error Do not use this header file in the Graphics Library Package
   #error It is for external users only
#endif

#include <GraphicsLib\PointMapper.h>
#include <GraphicsLib\AxisXY.h>
#include <GraphicsLib\GraphXY.h>
#include <GraphicsLib\GraphTool.h>

#endif // INCLUDED_GRAPHICSLIB_GRAPHICSLIB_H_