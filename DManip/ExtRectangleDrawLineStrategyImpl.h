///////////////////////////////////////////////////////////////////////
// DManip - Direct Manipulation Framework
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

#ifndef INCLUDED_EXTRECTANGLEDRAWELINESTRATEGYIMPL_H_
#define INCLUDED_EXTRECTANGLEDRAWELINESTRATEGYIMPL_H_
// ExtRectangleDrawLineStrategyImpl.h: interface for the CExtRectangleDrawLineStrategyImpl class.
//
//////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class ATL_NO_VTABLE CExtRectangleDrawLineStrategyImpl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExtRectangleDrawLineStrategyImpl, &CLSID_ExtRectangleDrawLineStrategy>,
   public iExtRectangleDrawLineStrategy,
   public iGravityWellStrategy
{
public:
	CExtRectangleDrawLineStrategyImpl();
	virtual ~CExtRectangleDrawLineStrategyImpl();
   HRESULT FinalConstruct();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_EXTRECTANGLEDRAWLINESTRATEGY)

BEGIN_COM_MAP(CExtRectangleDrawLineStrategyImpl)
   COM_INTERFACE_ENTRY(iDrawLineStrategy)
   COM_INTERFACE_ENTRY(iExtRectangleDrawLineStrategy)
   COM_INTERFACE_ENTRY(iGravityWellStrategy)
END_COM_MAP()

// iLineDrawStrategy
public:
   STDMETHOD_(void,Draw)(iLineDisplayObject* pDO,CDC* pDC);
   STDMETHOD_(void,DrawDragImage)(iLineDisplayObject* pDO,CDC* pDC, iCoordinateMap* map, const CPoint& dragStart, const CPoint& dragPoint);
   STDMETHOD_(void,DrawHighlite)(iLineDisplayObject* pDO,CDC* pDC,BOOL bHighlite);
   STDMETHOD_(void,GetBoundingBox)(iLineDisplayObject* pDO,IRect2d** box);

// iExtRectangleLineDrawStrategy
public:
   STDMETHOD_(void,SetLeftOffset)(Float64 offset);
   STDMETHOD_(Float64,GetLeftOffset)();
   STDMETHOD_(void,SetRightOffset)(Float64 offset);
   STDMETHOD_(Float64,GetRightOffset)();
   STDMETHOD_(void,SetStartExtension)(Float64 ext);
   STDMETHOD_(Float64,GetStartExtension)();
   STDMETHOD_(void,SetEndExtension)(Float64 ext);
   STDMETHOD_(Float64,GetEndExtension)();
   STDMETHOD_(void,SetStartSkew)(Float64 skew);
   STDMETHOD_(Float64,GetStartSkew)();
   STDMETHOD_(void,SetEndSkew)(Float64 skew);
   STDMETHOD_(Float64,GetEndSkew)();
   STDMETHOD_(void,SetLineWidth)(UINT nWidth);
   STDMETHOD_(UINT,GetLineWidth)();
   STDMETHOD_(void,SetColor)(COLORREF crColor);
   STDMETHOD_(COLORREF,GetColor)();
   STDMETHOD_(void,SetLineStyle)(LineStyleType style);
   STDMETHOD_(LineStyleType,GetLineStyle)();
   STDMETHOD_(void,PerimeterGravityWell)(BOOL bPerimeterGravityWell);
   STDMETHOD_(void,SetFillColor)(COLORREF crColor);
   STDMETHOD_(COLORREF,GetFillColor)();
   STDMETHOD_(void,SetDoFill)(BOOL doFill);
   STDMETHOD_(BOOL,GetDoFill)();

// iGravityWellStrategy
public:
   STDMETHOD_(void,GetGravityWell)(iDisplayObject* pDO,CRgn* pRgn);

private:
   BOOL m_bPerimeterGravityWell;
   BOOL m_bDoFill;
   Float64 m_LeftOffset, m_RightOffset;
   Float64 m_StartSkew, m_EndSkew;
   Float64 m_StartExtension, m_EndExtension;
   UINT m_nWidth;
   COLORREF m_crColor;
   COLORREF m_crFillColor;

   LineStyleType m_Style;

   void GetStartPoint(iLineDisplayObject* pDO,IPoint2d* *point);
   void GetEndPoint(iLineDisplayObject* pDO,IPoint2d* *point);
   void GetPoints(iLineDisplayObject* pDO,IPoint2d** pntTopLeft,IPoint2d** pntBottomLeft,IPoint2d** pntBottomRight,IPoint2d** pntTopRight);
   void GetDrawRect(iLineDisplayObject* pDO,CPoint* p1,CPoint* p2,CPoint* p3,CPoint* p4);
   void DrawPerimeter(CDC* pDC,COLORREF color, int penStyle, CPoint& p1,CPoint& p2,CPoint& p3,CPoint& p4);
};

#endif // INCLUDED_EXTRECTANGLEDRAWELINESTRATEGYIMPL_H_