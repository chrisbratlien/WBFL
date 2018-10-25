///////////////////////////////////////////////////////////////////////
// EAF - Extensible Application Framework
// Copyright � 1999-2016  Washington State Department of Transportation
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
#include <EAF\EAFDocument.h>

// EAFAutoCalcDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEAFAutoCalcDocMixin document
//
// Mix-in class that provides AutoCalc features

class EAFCLASS CEAFAutoCalcDocMixin
{
public:
	CEAFAutoCalcDocMixin();
	virtual ~CEAFAutoCalcDocMixin();

   void SetDocument(CEAFDocument* pDoc);
   virtual void CreateAcceleratorKeys();
   virtual void RemoveAcceleratorKeys();


   virtual bool IsAutoCalcEnabled() const = 0;
   virtual void EnableAutoCalc(bool bEnable) = 0;

   void OnAutoCalc();
   void OnUpdateAutoCalc(CCmdUI* pCmdUI);


   void OnUpdateNow();
	void OnUpdateUpdateNow(CCmdUI* pCmdUI);

private:
   CEAFDocument* m_pDocument;
};
