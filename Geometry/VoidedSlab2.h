///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright � 1999-2020  Washington State Department of Transportation
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

// VoidedSlab2.h : Declaration of the CVoidedSlab2
#pragma once
#include "resource.h"       // main symbols
#include "GeometryCP.h"

/////////////////////////////////////////////////////////////////////////////
// CVoidedSlab2
class ATL_NO_VTABLE CVoidedSlab2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVoidedSlab2, &CLSID_VoidedSlab2>,
   public ISupportErrorInfo,
   public IObjectSafetyImpl<CVoidedSlab2,INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public IVoidedSlab2,
	public IShape,
	public ICompositeShape,
   public IXYPosition,
   public IStructuredStorage2,
   public IPersist,
   public IPoint2dEvents,
   public CProxyDPoint2dEvents< CVoidedSlab2 >,
   public IConnectionPointContainerImpl<CVoidedSlab2>
{
public:
	CVoidedSlab2()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_VOIDEDSLAB2)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVoidedSlab2)
	COM_INTERFACE_ENTRY(IVoidedSlab2)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IShape)
   COM_INTERFACE_ENTRY(ICompositeShape)
   COM_INTERFACE_ENTRY(IXYPosition)
   COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(IPoint2dEvents)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CVoidedSlab2)
	CONNECTION_POINT_ENTRY(IID_IPoint2dEvents)
END_CONNECTION_POINT_MAP()

private:
   CComPtr<IPoint2d> m_pHookPoint; // BottomCenter
   CComPtr<ICompositeShape> m_pShape; // Implementation shape
   Float64   m_Rotation;
   Float64   m_W;
   Float64   m_H;
   Float64   m_Dext;
   Float64   m_Dint;
   Float64   m_Sext;
   Float64   m_Sint;
   Float64   m_C1;
   Float64   m_C2;
   Float64   m_C3;
   Float64   m_Hext;
   Float64   m_Hint;
   CollectionIndexType m_VoidCount;

   VARIANT_BOOL m_bLeftBlockOut, m_bRightBlockOut;

   bool   m_Dirty;
   DWORD  m_HookPointCookie;

   HRESULT GetLocatorPoint(LocatorPointType lp,Float64* px,Float64* py);
   HRESULT UpdateShape();
   void MakeDirty() {m_Dirty = true;}

// ISupportErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IVoidedSlab2
public:
   STDMETHOD(put_Height)(/*[in]*/Float64 h) override;
   STDMETHOD(get_Height)(/*[out,retval]*/Float64* h) override;
   STDMETHOD(put_Width)(/*[in]*/Float64 w) override;
   STDMETHOD(get_Width)(/*[out,retval]*/Float64* w) override;
   STDMETHOD(put_C1)(/*[in]*/Float64 c1) override;
   STDMETHOD(get_C1)(/*[out,retval]*/Float64* c1) override;
   STDMETHOD(put_C2)(/*[in]*/Float64 c2) override;
   STDMETHOD(get_C2)(/*[out,retval]*/Float64* c2) override;
   STDMETHOD(put_C3)(/*[in]*/Float64 c3) override;
   STDMETHOD(get_C3)(/*[out,retval]*/Float64* c3) override;
   STDMETHOD(put_LeftBlockOut)(/*[in]*/VARIANT_BOOL bLeftBlockOut) override;
   STDMETHOD(get_LeftBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbLeftBlockOut) override;
   STDMETHOD(put_RightBlockOut)(/*[in]*/VARIANT_BOOL bRightBlockOut) override;
   STDMETHOD(get_RightBlockOut)(/*[out,retval]*/VARIANT_BOOL* pbRightBlockOut) override;
   STDMETHOD(put_ExteriorVoidDiameter)(/*[in]*/Float64 d) override;
   STDMETHOD(get_ExteriorVoidDiameter)(/*[out,retval]*/Float64* d) override;
   STDMETHOD(put_InteriorVoidDiameter)(/*[in]*/Float64 d) override;
   STDMETHOD(get_InteriorVoidDiameter)(/*[out,retval]*/Float64* d) override;
   STDMETHOD(put_ExteriorVoidSpacing)(/*[in]*/Float64 s) override;
   STDMETHOD(get_ExteriorVoidSpacing)(/*[out,retval]*/Float64* s) override;
   STDMETHOD(put_InteriorVoidSpacing)(/*[in]*/Float64 s) override;
   STDMETHOD(get_InteriorVoidSpacing)(/*[out,retval]*/Float64* s) override;
   STDMETHOD(put_ExteriorVoidElevation)(/*[in]*/Float64 h1) override;
   STDMETHOD(get_ExteriorVoidElevation)(/*[out,retval]*/Float64* h1) override;
   STDMETHOD(put_InteriorVoidElevation)(/*[in]*/Float64 h2) override;
   STDMETHOD(get_InteriorVoidElevation)(/*[out,retval]*/Float64* h2) override;
   STDMETHOD(put_VoidCount)(/*[in]*/CollectionIndexType nv) override;
   STDMETHOD(get_VoidCount)(/*[out,retval]*/CollectionIndexType* nv) override;
   STDMETHOD(get_HookPoint)(/*[out,retval]*/IPoint2d** hookPnt) override;
   STDMETHOD(putref_HookPoint)(/*[in]*/ IPoint2d* hookPnt) override;
   STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
   STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
   STDMETHOD(get_StructuredStorage)(/*[out, retval]*/ IStructuredStorage2* *pStg) override;

// IShape
	STDMETHOD(FurthestDistance)(/*[in]*/ILine2d* line,/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(get_Perimeter)(/*[out, retval]*/ Float64 *pVal) override;
   STDMETHOD(get_ShapeProperties)(/*[out,retval]*/ IShapeProperties* *pVal) override;
	STDMETHOD(get_BoundingBox)(/*[out, retval]*/ IRect2d* *pVal) override;
	STDMETHOD(get_PolyPoints)(/*[out,retval]*/ IPoint2dCollection** ppPolyPoints) override;
	STDMETHOD(PointInShape)(/*[in]*/ IPoint2d* pPoint,/*[out,retval]*/ VARIANT_BOOL* pbResult) override;
	STDMETHOD(Clone)(/*[out,retval]*/ IShape** pClone) override;
	STDMETHOD(ClipWithLine)(/*[in]*/ ILine2d* pLine,/*[out,retval]*/ IShape** pShape) override;
	STDMETHOD(ClipIn)(/*[in]*/ IRect2d* pRect,/*[out,retval]*/ IShape** pShape) override;

// ICompositeShape
public:
// STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg) override;
//	STDMETHOD(get_XYPosition)(/*[out, retval]*/ IXYPosition* *pVal) override;
//	STDMETHOD(get_Shape)(/*[out, retval]*/ IShape* *pVal) override;
	STDMETHOD(get_Item)(/*[in]*/ CollectionIndexType idx, /*[out, retval]*/ ICompositeShapeItem* *pVal) override;
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown* *pVal) override;
	STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal) override;
	STDMETHOD(Remove)(/*[in]*/ CollectionIndexType idx) override;
   STDMETHOD(Clear)() override;
   STDMETHOD(ReplaceEx)(CollectionIndexType idx,ICompositeShapeItem* pShapeItem) override;
   STDMETHOD(Replace)(CollectionIndexType idx,IShape* pShape) override;
	STDMETHOD(AddShapeEx)(/*[in]*/ ICompositeShapeItem* ShapeItem) override;
   STDMETHOD(AddShape)(/*[in]*/ IShape* shape,/*[in]*/ VARIANT_BOOL bVoid) override;

// IXYPosition
	STDMETHOD(Offset)(/*[in]*/ Float64 dx,/*[in]*/ Float64 dy) override;
	STDMETHOD(OffsetEx)(/*[in]*/ ISize2d* pSize) override;
	STDMETHOD(get_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[out,retval]*/ IPoint2d** point) override;
	STDMETHOD(put_LocatorPoint)(/*[in]*/ LocatorPointType lp, /*[in]*/ IPoint2d* point) override;
	STDMETHOD(MoveEx)(/*[in]*/ IPoint2d* pFrom,/*[in]*/ IPoint2d* pTo) override;
	STDMETHOD(RotateEx)(/*[in]*/ IPoint2d* pPoint,/*[in]*/ Float64 angle) override;
	STDMETHOD(Rotate)(/*[in]*/ Float64 cx,/*[in]*/ Float64 cy,/*[in]*/ Float64 angle) override;

// IPersist
public:
   STDMETHOD(GetClassID)(CLSID* pClassID) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;

// IPoint2dEvents
public:
	STDMETHOD(OnPointChanged)(IPoint2d* point) override;

};
