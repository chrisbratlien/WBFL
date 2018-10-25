///////////////////////////////////////////////////////////////////////
// GenericBridgeTest - Test driver for generic bridge library
// Copyright � 1999-2017  Washington State Department of Transportation
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

// TestCrossBeam.cpp: implementation of the CTestCrossBeam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestCrossBeam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestCrossBeam::CTestCrossBeam()
{

}

CTestCrossBeam::~CTestCrossBeam()
{

}

void CTestCrossBeam::Test()
{
   //// Create a default bridge
   //CComPtr<IGenericBridge> bridge;
   //bridge.CoCreateInstance(CLSID_GenericBridge);

   //bridge->InsertSpanAndPier(0, 10.00, qcbAfter, qcbRight);

   //CComPtr<IPierCollection> piers;
   //bridge->get_Piers(&piers);

   //CComPtr<IPier> pier;
   //piers->get_Item(0,&pier);

   //CComPtr<ITransversePierDescription> tpd;
   //pier->CreateTransversePierDescription();
   //pier->get_TransversePierDescription(&tpd);

   //CComPtr<ICrossBeam> crossBeam;
   //TRY_TEST(tpd->get_CrossBeam(nullptr),E_POINTER);
   //TRY_TEST(tpd->get_CrossBeam(&crossBeam),S_OK);
   //TRY_TEST(crossBeam != nullptr,true);

   //Float64 length;
   //TRY_TEST(crossBeam->get_Length(nullptr),E_POINTER);
   //TRY_TEST(crossBeam->get_Length(&length),S_OK);
   //TRY_TEST(IsEqual(length,0.0),true);

   //CollectionIndexType count;
   //TRY_TEST(crossBeam->get_SegmentCount(nullptr),E_POINTER);
   //TRY_TEST(crossBeam->get_SegmentCount(&count),S_OK);
   //TRY_TEST(count,0);

   //VARIANT_BOOL bFractional;
   //TRY_TEST(crossBeam->get_Fractional(nullptr),E_POINTER);
   //TRY_TEST(crossBeam->get_Fractional(&bFractional),S_OK);
   //TRY_TEST(bFractional,VARIANT_FALSE);

   //VARIANT_BOOL bSymmetrical;
   //TRY_TEST(crossBeam->get_Symmetrical(nullptr),E_POINTER);
   //TRY_TEST(crossBeam->get_Symmetrical(&bSymmetrical),S_OK);
   //TRY_TEST(bSymmetrical,VARIANT_FALSE);

   /////////////////////////////////////////
   //// Test Error Info
   //CComQIPtr<ISupportErrorInfo> eInfo(crossBeam);
   //TRY_TEST( eInfo != 0, true );

   //// Interfaces that should be supported
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ICrossBeam ), S_OK );
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   //// Interface that is not supported
   //TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );

   //// Test IObjectSafety
   //TRY_TEST( TestIObjectSafety(crossBeam,IID_ICrossBeam,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
   //TRY_TEST( TestIObjectSafety(crossBeam,IID_IStructuredStorage2,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA), true);
}
