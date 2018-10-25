///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright � 1999-2011  Washington State Department of Transportation
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

// UBeam.h : Declaration of the CUBeam

#ifndef __UBEAM_H_
#define __UBEAM_H_

#include "resource.h"       // main symbols
#include "GeometryCP.h"

/////////////////////////////////////////////////////////////////////////////
// CUBeam
class ATL_NO_VTABLE CUBeam : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUBeam, &CLSID_UBeam>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CUBeam,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IUBeam,
	public IShape,
   public IXYPosition,
   public IStructuredStorage2,
   public IPersist,
   public IPoint2dEvents,
   public CProxyDPoint2dEvents< CUBeam >,
   public IConnectionPointContainerImpl<CUBeam>
{
public:
	CUBeam()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_UBEAM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUBeam)
	COM_INTERFACE_ENTRY(IUBeam)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPoint2dEvents)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IUBeam
public:
	STDMETHOD(get_T)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_T)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_D7)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_D7)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_D6)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_D6)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_D5)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_D5)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_D4)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_D4)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_D3)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_D3)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_D2)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_D2)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_D1)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_D1)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_W5)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_W5)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_W4)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_W4)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_W3)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_W3)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_W2)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_W2)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_W1)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_W1)(/*[in]*/ Float64 newVal);
   STDMETHOD(get_Slope)(/*[in]*/long webIdx,/*[out,retval]*/Float64* slope);
	STDMETHOD(get_TopWidth)(/*[out,retval]*/Float64* width);
	STDMETHOD(get_TopFlangeWidth)(/*[out,retval]*/Float64* width);
	STDMETHOD(get_WebLocation)(/*[in]*/long webIdx,/*[out,retval]*/Float64* location);
	STDMETHOD(get_WebSpacing)(/*[out,retval]*/Float64* spacing);

// IShape
	STDMETHOD(FurthestDistance)(/*[in]*/ILine2d* line,/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_Perimeter)(/*[out, retval]*/ Float64 *pVal);
   STDMETHOD(get_ShapeProperties)(/*[out,retval]*/ IShapeProperties* *pVal);
	STDMETHOD(get_BoundingBox)(/*[out, retval]*/ IRect2d* *pVal);
	STDMETHOD(get_PolyPoints)(/*[out,retval]*/ IPoint2dCollection** ppPolyPoints);
	STDMETHOD(PointInShape)(/*[in]*/ IPoint2d* pPoint,/*[out,retval]*/ VARIANT_BOOL* pbResult);
	STDMETHOD(Clone)(/*[out,retval]*/ IShape** pClone);
	STDMETHOD(ClipWithLine)(/*[in]*/ ILine2d* pLine,/*[out,retval]*/ IShape** pShape);
	STDMETHOD(ClipIn)(/*[in]*/ IRect2d* pRect,/*[out,retval]*/ IShape** pShape);

// IXYPosition
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy);
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize);
	STDMETHOD(get_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[out,retval]*/ IPoint2d** point);
	STDMETHOD(put_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[in]*/ IPoint2d* point);
	STDMETHOD(MoveEx)(/*[in]*/ IPoint2d* pFrom,/*[in]*/ IPoint2d* pTo);
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pPoint,/*[in]*/ Float64 angle);
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx,/*[in]*/ Float64 cy,/*[in]*/ Float64 angle);

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID);

// IStructuredStorage2
public:
	STDMETHOD(get_StructuredStorage)(/*[out, retval]*/ IStructuredStorage2* *pVal);
	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal);
	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal);
	STDMETHOD(get_Height)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_HookPoint)(/*[out, retval]*/ IPoint2d* *pVal);
	STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* newVal);
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

// IPoint2dEvents
public:
	STDMETHOD(OnPointChanged)(IPoint2d* point);


private:
   CComPtr<IPoint2d> m_pHookPoint; // BottomCenter
   CComPtr<IPolyShape> m_pShape; // Implementation Polygon
   Float64   m_Rotation;
   Float64   m_D1;
   Float64   m_D2;
   Float64   m_D3;
   Float64   m_D4;
   Float64   m_D5;
   Float64   m_D6;
   Float64   m_D7;
   Float64   m_T;
   Float64   m_W1;
   Float64   m_W2;
   Float64   m_W3;
   Float64   m_W4;
   Float64   m_W5;

   bool   m_Dirty;

   unsigned long   m_HookPointCookie;

   HRESULT GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py);
   HRESULT UpdateShape();


   void MakeDirty()
   {
      m_Dirty = true;
   }
public :

BEGIN_CONNECTION_POINT_MAP(CUBeam)
	CONNECTION_POINT_ENTRY(IID_IPoint2dEvents)
END_CONNECTION_POINT_MAP()

};

#endif //__UBEAM_H_
