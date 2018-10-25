///////////////////////////////////////////////////////////////////////
// MfcTools - Extension library for MFC
// Copyright � 1999-2015  Washington State Department of Transportation
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

#include "stdafx.h"
#include <MfcTools\RebarMaterialComboBox.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void DDX_RebarMaterial(CDataExchange* pDX,UINT nIDC,matRebar::Type& type,matRebar::Grade& grade)
{
   HWND hWndCtrl = pDX->PrepareCtrl(nIDC);

   if ( pDX->m_bSaveAndValidate )
   {
      int curSel = (int)::SendMessage(hWndCtrl,CB_GETCURSEL,0,0L);
      switch(curSel)
      {
      case 0:  type = matRebar::A615;  grade = matRebar::Grade40;  break;
      case 1:  type = matRebar::A615;  grade = matRebar::Grade60;  break;
      case 2:  type = matRebar::A615;  grade = matRebar::Grade75;  break;
      case 3:  type = matRebar::A615;  grade = matRebar::Grade80;  break;
      case 4:  type = matRebar::A706;  grade = matRebar::Grade60;  break;
      case 5:  type = matRebar::A706;  grade = matRebar::Grade80;  break;
      case 6:  type = matRebar::A1035; grade = matRebar::Grade100; break;
      default:
         ATLASSERT(false); // should never get here
      }
   }
   else
   {
      int curSel;
      if ( type == matRebar::A615 )
      {
         if ( grade == matRebar::Grade40 )
            curSel = 0;
         else if ( grade == matRebar::Grade60 )
            curSel = 1;
         else if ( grade == matRebar::Grade75 )
            curSel = 2;
         else if ( grade == matRebar::Grade80 )
            curSel = 3;
      }
      else if ( type == matRebar::A706 )
      {
         if ( grade == matRebar::Grade60 )
            curSel = 4;
         else if ( grade == matRebar::Grade80 )
            curSel = 5;
      }
      else if ( type == matRebar::A1035 )
      {
         if ( grade == matRebar::Grade100 )
            curSel = 6;
      }
      else
      {
         ATLASSERT(false); // should never get here
         curSel = CB_ERR;
      }
      ::SendMessage(hWndCtrl, CB_SETCURSEL, (WPARAM)curSel, (LPARAM)0);
   }
}


/////////////////////////////////////////////////////////////////////////////
// CRebarMaterialComboBox

CRebarMaterialComboBox::CRebarMaterialComboBox()
{
}

CRebarMaterialComboBox::~CRebarMaterialComboBox()
{
}

IMPLEMENT_DYNAMIC(CRebarMaterialComboBox, CComboBox)

BEGIN_MESSAGE_MAP(CRebarMaterialComboBox, CComboBox)
    //{{AFX_MSG_MAP(CRebarMaterialComboBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CRebarMaterialComboBox::Initialize(bool bFilterBySpec)
{
   ResetContent();

   AddString( lrfdRebarPool::GetMaterialName(matRebar::A615,  matRebar::Grade40).c_str()  );
   AddString( lrfdRebarPool::GetMaterialName(matRebar::A615,  matRebar::Grade60).c_str()  );
   AddString( lrfdRebarPool::GetMaterialName(matRebar::A615,  matRebar::Grade75).c_str()  );
   AddString( lrfdRebarPool::GetMaterialName(matRebar::A615,  matRebar::Grade80).c_str()  );
   AddString( lrfdRebarPool::GetMaterialName(matRebar::A706,  matRebar::Grade60).c_str()  );
   AddString( lrfdRebarPool::GetMaterialName(matRebar::A706,  matRebar::Grade80).c_str()  );

   if ( bFilterBySpec )
   {
      if ( lrfdVersionMgr::SixthEditionWith2013Interims <= lrfdVersionMgr::GetVersion() )
      {
         AddString( lrfdRebarPool::GetMaterialName(matRebar::A1035, matRebar::Grade100).c_str() );
      }
   }
}

/////////////////////////////////////////////////////////////////////////////
// CRebarMaterialComboBox message handlers
void CRebarMaterialComboBox::PreSubclassWindow()
{
   CComboBox::PreSubclassWindow();
   Initialize();
}
