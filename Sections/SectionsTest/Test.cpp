///////////////////////////////////////////////////////////////////////
// Sections Test - Test driver for Sections library
// Copyright � 1999-2019  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the Alternate Route Library Open Source License as 
// published by the Washington State Department of Transportation,
// Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful,
// but is distributed AS IS, WITHOUT ANY WARRANTY; without even the
// implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
// PURPOSE.  See the Alternate Route Library Open Source License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License
// along with this program; if not, write to the Washington State
// Department of Transportation, Bridge and Structures Office,
// P.O. Box 47340, Olympia, WA 98503, USA or e-mail
// Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <initguid.h>
#include <WBFLTools_i.c>
#include <WBFLGeometry_i.c>
#include <WBFLSections_i.c>

#include "TestMassProperties.h"
#include "TestElasticProperties.h"
#include "TestCompositeSectionItem.h"
#include "TestCompositeSection.h"
#include "TestCompositeBeam.h"
#include "TestCompositeSectionEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int main(int argc, TCHAR* argv[])
{
   ::CoInitialize(nullptr);
   {
      CTestMassProperties::Test();
      CTestElasticProperties::Test();
      CTestCompositeSectionItem::Test();
      CTestCompositeSection::Test();
      CTestCompositeBeam::Test();
      CTestCompositeSectionEx::Test();
   }
   ::CoUninitialize();
	return 0;
}
