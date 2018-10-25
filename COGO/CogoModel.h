///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry
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

// CogoModel.h : Declaration of the CCogoModel

#ifndef __COGOMODEL_H_
#define __COGOMODEL_H_
#pragma once

#include "resource.h"       // main symbols
#include "COGOCP.h"

/////////////////////////////////////////////////////////////////////////////
// CCogoModel
class ATL_NO_VTABLE CCogoModel : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CCogoModel,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CCogoModel, &CLSID_CogoModel>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CCogoModel,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IConnectionPointContainerImpl<CCogoModel>,
   public ICogoModel,
   public IMeasure,
   public ILocate,
   public IIntersect,
   public IProject,
   public IDivide,
   public ITangent,
   public IStructuredStorage2,
   public IPointCollectionEvents,
   public ILineSegmentCollectionEvents,
   public IProfilePointCollectionEvents,
   public IVertCurveCollectionEvents,
   public IHorzCurveCollectionEvents,
   public IPathCollectionEvents,
   public CProxyDCogoModelEvents< CCogoModel >,
   public IPersistImpl<CCogoModel>
{
public:
	CCogoModel()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

   HRESULT PutRef_Alignments(IPathCollection* alignments);
   HRESULT PutRef_Paths(IPathCollection* paths);
   HRESULT PutRef_HorzCurves(IHorzCurveCollection* horzCurves);
   HRESULT PutRef_Lines(ILineSegmentCollection* lines);
   HRESULT PutRef_Points(IPointCollection* points);
   HRESULT PutRef_ProfilePoints(IProfilePointCollection* profilePoints);
   HRESULT PutRef_VertCurves(IVertCurveCollection* vertCurves);

DECLARE_REGISTRY_RESOURCEID(IDR_COGOMODEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCogoModel)
	COM_INTERFACE_ENTRY(ICogoModel)
	COM_INTERFACE_ENTRY(IMeasure)
	COM_INTERFACE_ENTRY(ILocate)
	COM_INTERFACE_ENTRY(IIntersect)
	COM_INTERFACE_ENTRY(IProject)
	COM_INTERFACE_ENTRY(IDivide)
	COM_INTERFACE_ENTRY(ITangent)
   COM_INTERFACE_ENTRY(IStructuredStorage2)

   COM_INTERFACE_ENTRY(IPointCollectionEvents)

   COM_INTERFACE_ENTRY(ILineSegmentCollectionEvents)

   COM_INTERFACE_ENTRY(IProfilePointCollectionEvents)

   COM_INTERFACE_ENTRY(IVertCurveCollectionEvents)

   COM_INTERFACE_ENTRY(IHorzCurveCollectionEvents)

   COM_INTERFACE_ENTRY(IPathCollectionEvents)

   COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CCogoModel)
   CONNECTION_POINT_ENTRY(IID_ICogoModelEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICogoModel
public:
   STDMETHOD(get_StructuredStorage)(IStructuredStorage2* *pStg);
   STDMETHOD(Clone)(/*[out,retval]*/ ICogoModel* *clone);
   STDMETHOD(get_Engine)(/*[out,retval]*/ICogoEngine** engine);
	STDMETHOD(putref_ProfilePointFactory)(/*[in]*/IProfilePointFactory* factory);
	STDMETHOD(get_ProfilePointFactory)(/*[out,retval]*/IProfilePointFactory** factory);
	STDMETHOD(putref_VertCurveFactory)(/*[in]*/IVertCurveFactory* factory);
	STDMETHOD(get_VertCurveFactory)(/*[out,retval]*/IVertCurveFactory** factory);
	STDMETHOD(putref_HorzCurveFactory)(/*[in]*/IHorzCurveFactory* factory);
	STDMETHOD(get_HorzCurveFactory)(/*[out,retval]*/IHorzCurveFactory** factory);
	STDMETHOD(putref_AlignmentFactory)(/*[in]*/IPathFactory* factory);
	STDMETHOD(get_AlignmentFactory)(/*[out,retval]*/IPathFactory** factory);
	STDMETHOD(putref_PathFactory)(/*[in]*/IPathFactory* factory);
	STDMETHOD(get_PathFactory)(/*[out,retval]*/IPathFactory** factory);
	STDMETHOD(putref_PointFactory)(/*[in]*/IPoint2dFactory* factory);
	STDMETHOD(get_PointFactory)(/*[out,retval]*/IPoint2dFactory** factory);
	STDMETHOD(putref_LineSegmentFactory)(/*[in]*/ILineSegment2dFactory* factory);
	STDMETHOD(get_LineSegmentFactory)(/*[out,retval]*/ILineSegment2dFactory** factory);
   STDMETHOD(get_Tangent)(/*[out, retval]*/ ITangent* *pVal);
   STDMETHOD(get_Divide)(/*[out, retval]*/ IDivide* *pVal);
	STDMETHOD(get_Project)(/*[out, retval]*/ IProject* *pVal);
	STDMETHOD(get_Measure)(/*[out, retval]*/ IMeasure* *pVal);
	STDMETHOD(get_Locate)(/*[out, retval]*/ ILocate* *pVal);
	STDMETHOD(get_Intersect)(/*[out, retval]*/ IIntersect* *pVal);
	STDMETHOD(Clear)();
	STDMETHOD(get_Alignments)(/*[out,retval]*/ IPathCollection* *pVal);
   STDMETHOD(get_Paths)(/*[out,retval]*/ IPathCollection* *pVal);
   STDMETHOD(get_VertCurves)(/*[out, retval]*/ IVertCurveCollection* *pVal);
   STDMETHOD(get_HorzCurves)(/*[out, retval]*/ IHorzCurveCollection* *pVal);
   STDMETHOD(get_ProfilePoints)(/*[out, retval]*/ IProfilePointCollection* *pVal);
   STDMETHOD(get_LineSegments)(/*[out, retval]*/ ILineSegmentCollection* *pVal);
	STDMETHOD(get_Points)(/*[out, retval]*/ IPointCollection* *pVal);

// IMeasure
public:
  	STDMETHOD(Angle)(/*[in]*/ CogoElementKey fromID,/*[in]*/ CogoElementKey vertexID,/*[in]*/ CogoElementKey toID,/*[out,retval]*/ IAngle** angle);
	STDMETHOD(Area)(/*[in]*/ VARIANT keys,/*[out,retval]*/ Float64* area);
	STDMETHOD(Distance)(/*[in]*/ CogoElementKey fromID,/*[in]*/ CogoElementKey toID,/*[out,retval]*/ Float64* dist);
	STDMETHOD(Direction)(/*[in]*/ CogoElementKey fromID,/*[in]*/ CogoElementKey toID,/*[out,retval]*/ IDirection** dir);
   STDMETHOD(Inverse)(/*[in]*/ CogoElementKey fromID,/*[in]*/ CogoElementKey toID,/*[out]*/ Float64* dist,/*[out]*/ IDirection** dir);

// ILocate
public:
   STDMETHOD(ParallelLineSegment)(/*[in]*/ CogoElementKey newLineID,/*[in]*/ CogoElementKey newFromID,/*[in]*/ CogoElementKey newToID,/*[in]*/ CogoElementKey lineID, /*[in]*/ Float64 offset);
   STDMETHOD(ParallelLineByPoints)(/*[in]*/ CogoElementKey newFromID,/*[in]*/ CogoElementKey newToID,/*[in]*/ CogoElementKey fromID,/*[in]*/ CogoElementKey toID, /*[in]*/ Float64 offset);
	STDMETHOD(ByDistAngle)(/*[in]*/ CogoElementKey newID,/*[in]*/ CogoElementKey fromID,/*[in]*/ CogoElementKey toID, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varAngle, /*[in]*/ Float64 offset);
	STDMETHOD(ByDistDefAngle)(/*[in]*/ CogoElementKey newID,/*[in]*/ CogoElementKey fromID,/*[in]*/ CogoElementKey toID, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varDefAngle, /*[in]*/ Float64 offset);
	STDMETHOD(ByDistDir)(/*[in]*/ CogoElementKey newID,/*[in]*/ CogoElementKey fromID, /*[in]*/ Float64 dist, /*[in]*/ VARIANT varDir, /*[in]*/ Float64 offset);
	STDMETHOD(PointOnLine)(/*[in]*/ CogoElementKey newID,/*[in]*/ CogoElementKey fromID, /*[in]*/ CogoElementKey toID, /*[in]*/ Float64 dist, /*[in]*/ Float64 offset);
   STDMETHOD(LinesByPoints)(/*[in]*/CogoElementKey newID,/*[in]*/ CogoElementKey id11, /*[in]*/ CogoElementKey id12, /*[in]*/ Float64 offset1,/*[in]*/ CogoElementKey id21, /*[in]*/ CogoElementKey id22, /*[in]*/ Float64 offset2, /*[out,retval]*/ VARIANT_BOOL* bFound);

// IIntersect
public:
   STDMETHOD(Bearings)(/*[in]*/CogoElementKey newID,/*[in]*/ CogoElementKey id1, /*[in]*/ VARIANT varDir1, /*[in]*/ Float64 offset1,/*[in]*/ CogoElementKey id2, /*[in]*/ VARIANT varDir2, /*[in]*/ Float64 offset2,/*[out,retval]*/ VARIANT_BOOL* bFound);
   STDMETHOD(BearingCircle)(/*[in]*/CogoElementKey newID,/*[in]*/ CogoElementKey id1, /*[in]*/ VARIANT varDir, /*[in]*/ Float64 offset,/*[in]*/ CogoElementKey idc, /*[in]*/ Float64 radius, /*[in]*/ CogoElementKey idNearest, /*[out,retval]*/ VARIANT_BOOL* bFound);
   STDMETHOD(Circles)(/*[in]*/CogoElementKey newID,/*[in]*/ CogoElementKey id1, /*[in]*/ Float64 r1, /*[in]*/ CogoElementKey id2, /*[in]*/ Float64 r2, /*[in]*/ CogoElementKey idNearest, /*[out,retval]*/ VARIANT_BOOL* bFound);
   STDMETHOD(LineByPointsCircle)(/*[in]*/CogoElementKey newID,/*[in]*/ CogoElementKey id1, /*[in]*/ CogoElementKey id2, /*[in]*/ Float64 offset,/*[in]*/ CogoElementKey idc, /*[in]*/ Float64 radius, /*[in]*/ CogoElementKey idNearest, /*[out,retval]*/ VARIANT_BOOL* bFound);
   STDMETHOD(Lines)(/*[in]*/CogoElementKey newID,/*[in]*/CogoElementKey id1,/*[in]*/Float64 offset1,/*[in]*/CogoElementKey id2,/*[in]*/Float64 offset2,/*[out,retval]*/VARIANT_BOOL* bFound);
   STDMETHOD(LineSegmentCircle)(/*[in]*/CogoElementKey newID,/*[in]*/ CogoElementKey lineID, /*[in]*/ Float64 offset,/*[in]*/ CogoElementKey idc, /*[in]*/ Float64 radius, /*[in]*/ CogoElementKey idNearest, /*[out,retval]*/ VARIANT_BOOL* bFound);

// IProject
public:
   STDMETHOD(PointOnCurve)(/*[in]*/CogoElementKey newID,/*[in]*/ CogoElementKey fromID, /*[in]*/CogoElementKey curveID);
   STDMETHOD(PointOnLineByPoints)(/*[in]*/CogoElementKey newID,/*[in]*/ CogoElementKey fromID, /*[in]*/ CogoElementKey startID, /*[in]*/ CogoElementKey endID, /*[in]*/ Float64 offset);
   STDMETHOD(PointOnLineSegment)(/*[in]*/CogoElementKey newID,/*[in]*/ CogoElementKey fromID,/*[in]*/ CogoElementKey lineID, /*[in]*/ Float64 offset);

// IDivide
public:
   STDMETHOD(Arc)(/*[in]*/CogoElementKey firstID,/*[in]*/ CogoElementKey idInc, /*[in]*/ CogoElementKey fromID, /*[in]*/ CogoElementKey HorzexID, /*[in]*/ CogoElementKey toID,/*[in]*/ long nParts);
   STDMETHOD(BetweenPoints)(/*[in]*/CogoElementKey firstID,/*[in]*/ CogoElementKey idInc, /*[in]*/ CogoElementKey fromID, /*[in]*/ CogoElementKey toID,/*[in]*/ long nParts);
   STDMETHOD(LineSegment)(/*[in]*/CogoElementKey firstID,/*[in]*/ CogoElementKey idInc, /*[in]*/ CogoElementKey lineID,/*[in]*/ long nParts);
	STDMETHOD(HorzCurve)(/*[in]*/ CogoElementKey firstID, /*[in]*/ CogoElementKey idInc, /*[in]*/ CogoElementKey curveID, /*[in]*/ long nParts);
   STDMETHOD(Path)(/*[in]*/CogoElementKey firstID,/*[in]*/CogoElementKey idInc,/*[in]*/CogoElementKey pathID,/*[in]*/ long nParts,/*[in]*/ Float64 start,/*[in]*/ Float64 end);

// ITangent
public:
   STDMETHOD(External)(/*[in]*/ CogoElementKey newID1, /*[in]*/ CogoElementKey idCenter1, /*[in]*/ Float64 radius1,/*[in]*/ CogoElementKey newID2,/*[in]*/ CogoElementKey idCenter2, /*[in]*/ Float64 radius2, /*[in]*/ TangentSignType sign);
   STDMETHOD(Cross)(/*[in]*/ CogoElementKey newID1, /*[in]*/ CogoElementKey idCenter1, /*[in]*/ Float64 radius1,/*[in]*/ CogoElementKey newID2,/*[in]*/ CogoElementKey idCenter2, /*[in]*/ Float64 radius2, /*[in]*/ TangentSignType sign);
   STDMETHOD(Point)(/*[in]*/ CogoElementKey newID, /*[in]*/ CogoElementKey idCenter, /*[in]*/ Float64 radius,/*[in]*/ CogoElementKey pointID,/*[in]*/ TangentSignType sign);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave);
   STDMETHOD(Load)(IStructuredLoad2* pLoad);

// IPointCollectionEvents
public:
   STDMETHOD(OnPointChanged)(/*[in]*/ CogoElementKey key,/*[in]*/ IPoint2d* point);
   STDMETHOD(OnPointAdded)(/*[in]*/ CogoElementKey key,/*[in]*/ IPoint2d* point);
   STDMETHOD(OnPointRemoved)(/*[in]*/ CogoElementKey key);
   STDMETHOD(OnPointsCleared)();

// ILineSegmentCollectionEvents
public:
   STDMETHOD(OnLineSegmentChanged)(/*[in]*/ CogoElementKey key,/*[in]*/ ILineSegment2d* lineSeg);
   STDMETHOD(OnLineSegmentAdded)(/*[in]*/ CogoElementKey key,/*[in]*/ ILineSegment2d* lineSeg);
   STDMETHOD(OnLineSegmentRemoved)(/*[in]*/ CogoElementKey key);
   STDMETHOD(OnLineSegmentsCleared)();

// IProfilePointCollectionEvents
public:
   STDMETHOD(OnProfilePointChanged)(/*[in]*/ CogoElementKey key,/*[in]*/ IProfilePoint* pp);
   STDMETHOD(OnProfilePointAdded)(/*[in]*/ CogoElementKey key,/*[in]*/ IProfilePoint* pp);
   STDMETHOD(OnProfilePointRemoved)(/*[in]*/ CogoElementKey key);
   STDMETHOD(OnProfilePointsCleared)();

// IVertCurveCollectionEvents
public:
   STDMETHOD(OnVertCurveChanged)(/*[in]*/ CogoElementKey key,/*[in]*/ IVertCurve* vc);
   STDMETHOD(OnVertCurveAdded)(/*[in]*/ CogoElementKey key,/*[in]*/ IVertCurve* vc);
   STDMETHOD(OnVertCurveRemoved)(/*[in]*/ CogoElementKey key);
   STDMETHOD(OnVertCurvesCleared)();

// IHorzCurveCollectionEvents
public:
   STDMETHOD(OnHorzCurveChanged)(/*[in]*/ CogoElementKey key,/*[in]*/ IHorzCurve* hc);
   STDMETHOD(OnHorzCurveAdded)(/*[in]*/ CogoElementKey key,/*[in]*/ IHorzCurve* hc);
   STDMETHOD(OnHorzCurveRemoved)(/*[in]*/ CogoElementKey key);
   STDMETHOD(OnHorzCurvesCleared)();

// IPathCollectionEvents
public:
   STDMETHOD(OnPathChanged)(/*[in]*/IPathCollection* coll,/*[in]*/CogoElementKey key, /*[in]*/IPath* path);
   STDMETHOD(OnProfileChanged)(/*[in]*/IPathCollection* coll,/*[in]*/ IProfile* profile);
   STDMETHOD(OnPathAdded)(/*[in]*/IPathCollection* coll,/*[in]*/ CogoElementKey key,/*[in]*/ IPath* path);
   STDMETHOD(OnPathRemoved)(/*[in]*/IPathCollection* coll,/*[in]*/ CogoElementKey key);
   STDMETHOD(OnPathsCleared)(/*[in]*/IPathCollection* coll);

private:
   CComPtr<ICogoEngine> m_Engine;

   CComPtr<IPointCollection> m_Points;
   DWORD m_dwPointsCookie;

   CComPtr<ILineSegmentCollection> m_Lines;
   DWORD m_dwLinesCookie;

   CComPtr<IProfilePointCollection> m_ProfilePoints;
   DWORD m_dwProfilePointsCookie;

   CComPtr<IVertCurveCollection> m_VertCurves;
   DWORD m_dwVertCurvesCookie;

   CComPtr<IHorzCurveCollection> m_HorzCurves;
   DWORD m_dwHorzCurvesCookie;

   CComPtr<IPathCollection> m_Alignments;
   DWORD m_dwAlignmentCookie;

   CComPtr<IPathCollection> m_Paths;
   DWORD m_dwPathCookie;
};

#endif //__COGOMODEL_H_
