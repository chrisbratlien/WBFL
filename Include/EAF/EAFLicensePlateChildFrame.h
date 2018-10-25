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


#pragma once

#include <EAF\EAFExp.h>
#include <EAF\EAFTypes.h>


/*****************************************************************************
CLASS 
   CEAFLicensePlateChildFrame

   A multi-doc child frame window that puts a "license plate frame" around the view
   in your application.

DESCRIPTION
   Use this class to put a frame which contains a message around your view. One use
   of the class is to put a "Information Out of Date" message around a view that
   contains information that is not in synch with the state of the current document.
   You can also provide your own bitmap to be used in the background of the frame.

   The steps for using this class are:
 1.Change the CChildFrame class generated by Appwizard to be derived from ClicensePlateChildFrm.
 2.Change the message map stuff in the CChildFrame class to map to ClicensePlateChildFrm 
   instead of CMDIChildWnd.
 3.Do not override the OnSize or OnEraseBackground functions in your CChildFrame class.
 3.Make sure the window style for your view has WS_CLIPCHILDREN enabled.

   To get a pointer to the frame around your view, call CLicensePlateChildFrame::GetLpFrame.
   You can then use this pointer to call the license plate frame to:
     - Set the frame into license plate mode or check its state.
     - Change the bitmap or text in the frame
   


EXAMPLES
   EXAMPLE
   Example here, repeat as needed
   END

BUGS          
   For some unknown reason, the z order of the view/frame gets screwed up causing the 
   frame to get drawn over the top of your view windows. Hence, it is necessary to set 
   the WS_CLIPCHILDREN style for the view window.

KEYWORDS
   word1, word2, ..., wordn

COPYRIGHT
   Copyright (c) 1997
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class EAFCLASS CEAFLicensePlateChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CEAFLicensePlateChildFrame)
public:
	CEAFLicensePlateChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLicensePlateChildFrame)
	//}}AFX_VIRTUAL

// Implementation
public:

   //------------------------------------------------------------------------
	CString GetLicensePlateText();

   //------------------------------------------------------------------------
   // Set frame window into or out of license plate mode
   void SetLicensePlateMode(eafTypes::LpFrameMode mode);

   //------------------------------------------------------------------------
   // See which mode frame is in.
	eafTypes::LpFrameMode GetLicensePlateMode();

   //------------------------------------------------------------------------
   // Toggles the mode between on and off
   void Toggle();

   //------------------------------------------------------------------------
   void SetView(CView* pView);

   //------------------------------------------------------------------------
   CView* GetView();

   //------------------------------------------------------------------------
   // Returns true if the m_Mode is On
   bool IsLicensePlateModeEnabled() const;

   //------------------------------------------------------------------------
   // Set the background bit map for the license plate frame

   // set parameters for license plate window
   // Typicaly called from CMyView::OnCreate()
	void SetBackground(UINT BitMapID);

   //------------------------------------------------------------------------
   // Set the text in the license plate frame.
	void SetLicensePlateText(const CString& Message);

	virtual ~CEAFLicensePlateChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CLicensePlateChildFrame)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void PositionView();
	bool    m_IsBitmap;
	int     m_LpBorderWidth;
	CString m_LpMessage;
   CBitmap m_bmBackground;
   CSize   m_szBackground;
   eafTypes::LpFrameMode m_Mode;
   CView*  m_pView;
   CRect   m_OuterRect;

   void UpdateOuterRect();
   CRect& GetOuterBorder();
   CRect  GetInnerBorder();
};