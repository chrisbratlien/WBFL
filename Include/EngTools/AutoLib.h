///////////////////////////////////////////////////////////////////////
// EngTools - Library of miscellaneous engineering tools
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

#ifndef INCLUDED_ENGTOOLS_AUTOLIB_H_
#define INCLUDED_ENGTOOLS_AUTOLIB_H_
#pragma once


#if !defined (BUILDENGTOOLSLIB)

#define ENGTOOLS_AUTOLIBNAME "WBFLEngTools.lib"

#pragma comment(lib,ENGTOOLS_AUTOLIBNAME)
#if defined AUTOLIB
#pragma message("Linking with " ENGTOOLS_AUTOLIBNAME )
#endif

#endif // BUILDENGTOOLSLIB

#endif // INCLUDED_ENGTOOLS_AUTOLIB_H_