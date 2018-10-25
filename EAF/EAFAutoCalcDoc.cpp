///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
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


// EAFAutoCalcDoc.cpp : implementation file
//

#include "stdafx.h"
#include <EAF\EAFAutoCalcDoc.h>
#include <EAF\EAFAutoCalcView.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcDocMixin
CEAFAutoCalcDocMixin::CEAFAutoCalcDocMixin()
{
   m_pDocument = NULL;
}

CEAFAutoCalcDocMixin::~CEAFAutoCalcDocMixin()
{
}

void CEAFAutoCalcDocMixin::SetDocument(CDocument* pDoc)
{
   m_pDocument = pDoc;
}

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcDocMixin serialization

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcDocMixin commands
void CEAFAutoCalcDocMixin::OnUpdateNow()
{
   POSITION pos = m_pDocument->GetFirstViewPosition();
   while (pos != NULL)   
   {
      CView* pView = m_pDocument->GetNextView(pos);
      CEAFAutoCalcViewMixin* pAutoCalcView = dynamic_cast<CEAFAutoCalcViewMixin*>(pView);
      if ( pAutoCalcView )
      {
         pAutoCalcView->OnUpdateNow();
      }
   }
}

void CEAFAutoCalcDocMixin::OnUpdateUpdateNow(CCmdUI* pCmdUI)
{
   if ( IsAutoCalcEnabled() )
      pCmdUI->Enable( FALSE );
   else
      pCmdUI->Enable( TRUE );
}