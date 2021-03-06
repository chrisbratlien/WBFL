///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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
// Transportation, Bridge and Structures Office, 4500 3rd Ave SE - P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#ifndef INCLUDED_COGO_COGO_H_
#define INCLUDED_COGO_COGO_H_
#pragma once

// Master include file for clients of the Cogo library

#if defined(BUILDCOGOLIB)
	#error Do not use this header file in the COGO Library Package
   #error It is for external users only
#endif

#include <Cogo\CogoModel.h>
#include <Cogo\CogoDirection.h>
#include <Cogo\CogoAngle.h>
#include <Cogo\CogoHelpers.h>
#include <Cogo\Roadway.h>
#include <Cogo\Profile.h>
#include <Cogo\Curve.h>
#include <Cogo\VCurve.h>
#include <Cogo\Engine.h>

#endif // INCLUDED_COGO_COGO_H_