///////////////////////////////////////////////////////////////////////
// LBAM Analysis Test - Test driver for LBAM analysis library
// Copyright � 1999-2010  Washington State Department of Transportation
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

// TestOverhang.h: interface for the CTestOverhang class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTOVERHANG_H__105091B2_A27D_11D5_B05D_00105A9AF985__INCLUDED_)
#define AFX_TESTOVERHANG_H__105091B2_A27D_11D5_B05D_00105A9AF985__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

class CTestOverhang  
{
public:
	ILBAMModel* CreateModel(bool doPois);
	HRESULT Test();
   void CreateWithNoPOis();
	CTestOverhang();
	virtual ~CTestOverhang();

private:
   void GetSSPoiLocs(ILongArray* ppoiList, ILBAMModel* pModel, std::vector<Float64>* poiLocs);

};

#endif // !defined(AFX_TESTOVERHANG_H__105091B2_A27D_11D5_B05D_00105A9AF985__INCLUDED_)
