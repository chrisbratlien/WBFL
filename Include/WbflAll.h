///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#ifndef INCLUDED_WBFLALL_H_
#define INCLUDED_WBFLALL_H_
#pragma once

#ifndef _WBFL_VERSION
#define _WBFL_VERSION 330 // version 3.3.0
#endif 

#include <System\AutoLib.h>

// Make sure compiler settings are correct.
#if !defined(_DLL)
	#error Please use the /MD switch for DLL builds (Multithreaded DLL's)
#endif

#if !defined(_CPPRTTI)
   #error Please use the /GR switch to enable Run Time Type Information
#endif

#if !defined(_CPPUNWIND)
   #error Please use the /GX switch to enable Exception Handling
#endif

#include <WbflTypes.h>
#include <System\Log.h>

#endif // INCLUDED_WBFLALL_H_