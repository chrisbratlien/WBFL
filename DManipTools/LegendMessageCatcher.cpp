///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
// Copyright � 1999-2017  Washington State Department of Transportation
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

// LegendMessageCatcher.cpp : implementation file
//

#include "stdafx.h"
#include "WBFLDManipTools.h"
#include "LegendMessageCatcher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLegendMessageCatcher

CLegendMessageCatcher::CLegendMessageCatcher(iMessageListener* plistener):
m_pListener(plistener)
{
}

CLegendMessageCatcher::~CLegendMessageCatcher()
{
}


BEGIN_MESSAGE_MAP(CLegendMessageCatcher, CWnd)
	//{{AFX_MSG_MAP(CLegendMessageCatcher)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
   ON_COMMAND_RANGE(MC_MSG_BASE, MC_MSG_MAX, OnMessageCaught)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLegendMessageCatcher message handlers
void CLegendMessageCatcher::OnMessageCaught(UINT id)
{
   int idx = id - MC_MSG_BASE;
   m_pListener->OnCaughtMessage( idx );
}

