///////////////////////////////////////////////////////////////////////
// DManipTools - Direct Manipulation Tools
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

// LegendEntryImpl.h : Declaration of the CLegendEntryImpl

#ifndef __LEGENDENTRYIMPL_H_
#define __LEGENDENTRYIMPL_H_
#pragma once

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLegendEntryImpl
class ATL_NO_VTABLE CLegendEntryImpl:
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLegendEntryImpl, &CLSID_LegendEntry>,
	public ISupportErrorInfo,
   public iSymbolLegendEntry,
   public iDataPointFactory
{
public:
	CLegendEntryImpl();

DECLARE_REGISTRY_RESOURCEID(IDR_LEGENDENTRY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLegendEntryImpl)
   COM_INTERFACE_ENTRY(iLegendEntry)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(iSymbolLegendEntry)
   COM_INTERFACE_ENTRY(iDataPointFactory)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// iLegendEntry
public:
   STDMETHOD_(void,get_Name)(BSTR *pVal);
   STDMETHOD_(void,put_Name)(BSTR newVal);
   STDMETHOD_(void,Draw)(CDC* pDC, CRect& drawRect, BOOL beingDragged);
   STDMETHOD_(HRESULT,GetClassID)(CLSID *pClassID); // same as IPersist
   STDMETHOD_(void,WriteDragData)(iDragDataSink* pSink, UINT cfFormat);
   STDMETHOD_(void,ReadDragData)(iDragDataSource* pSource, UINT cfFormat);

// iSymbolLegendEntry 
   STDMETHOD_(void,get_SymbolFontFace)(TCHAR* *pVal);
   STDMETHOD_(void,put_SymbolFontFace)(LPCTSTR newVal);
   STDMETHOD_(long,get_SymbolSize)();
   STDMETHOD_(void,put_SymbolSize)(long code);
   STDMETHOD_(DWORD,get_SymbolCharacterCode)();
   STDMETHOD_(void,put_SymbolCharacterCode)(DWORD code);
   STDMETHOD_(COLORREF,get_Color)();
   STDMETHOD_(void,put_Color)(COLORREF color);
   STDMETHOD_(void,get_DoDrawLine)(BOOL* doDraw);
   STDMETHOD_(void,put_DoDrawLine)(BOOL doDraw);

// iDataPointFactory
   STDMETHOD_(HRESULT,CreateDataPoint)(Float64 dataX, Float64 dataY, Float64 graphX, Float64 graphY, iDisplayObject** dataPoint);

private:
   CComBSTR m_Name;
   CString  m_FontFace;
   long     m_FontSize;
   DWORD    m_CharCode;
   COLORREF m_Color;
   BOOL     m_DoDrawLine;

};

#endif //__LEGENDENTRYIMPL_H_
