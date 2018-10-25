///////////////////////////////////////////////////////////////////////
// LBAM - Longitindal Bridge Analysis Model
// Copyright � 1999-2014  Washington State Department of Transportation
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

// TemporarySupport.h : Declaration of the CTemporarySupport

#ifndef __TEMPORARYSUPPORT_H_
#define __TEMPORARYSUPPORT_H_

#include "resource.h"       // main symbols
#include "Segments.h"
#include "SupportCP.h"
#include "LoadModifierHelper.h"

/////////////////////////////////////////////////////////////////////////////
// CTemporarySupport
class ATL_NO_VTABLE CTemporarySupport : 
//   public CComRefCountTracer<CTemporarySupport,CComObjectRootEx<CComSingleThreadModel> >,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTemporarySupport, &CLSID_TemporarySupport>,
	public ISupportErrorInfo,
   public IPersistImpl<CTemporarySupport>,
	public IStructuredStorage2,
	public IConnectionPointContainerImpl<CTemporarySupport>,
   public CSegmentsOwner,
	public ITemporarySupport,
	public CProxyDTemporarySupportEvents< CTemporarySupport >,
	public ISegmentItemEvents,
   public IObjectSafetyImpl<CTemporarySupport,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IDistributionFactorEvents
{
public:
	CTemporarySupport();

DECLARE_REGISTRY_RESOURCEID(IDR_TEMPORARYSUPPORT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTemporarySupport)
	COM_INTERFACE_ENTRY(ITemporarySupport)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
   COM_INTERFACE_ENTRY(ISegmentItemEvents)
   COM_INTERFACE_ENTRY(IDistributionFactorEvents)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTemporarySupport)
CONNECTION_POINT_ENTRY(IID_ITemporarySupportEvents)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITemporarySupport
public:
   STDMETHOD(get_OmitReaction)(VARIANT_BOOL* pbOmit);
   STDMETHOD(put_OmitReaction)(VARIANT_BOOL bOmit);
	STDMETHOD(get_TopRelease)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_TopRelease)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_DistributionFactor)(/*[out, retval]*/ IDistributionFactor* *pVal);
	STDMETHOD(putref_DistributionFactor)(/*[in]*/ IDistributionFactor* newVal);
	STDMETHOD(GetLoadModifier)(/*[in]*/ LoadCombinationType type, /*[out]*/ Float64 *minVal, /*[out]*/ Float64 *maxVal);
	STDMETHOD(SetLoadModifier)(/*[in]*/ LoadCombinationType type, /*[in]*/ Float64 minVal, /*[in]*/ Float64 maxVal);
	STDMETHOD(get_ID)(/*[out, retval]*/ SupportIDType *pVal);
	STDMETHOD(put_ID)(/*[in]*/ SupportIDType newVal);
	STDMETHOD(RemoveStage)(/*[in]*/BSTR stage);
	STDMETHOD(get_IsSymmetrical)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IsSymmetrical)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(Clone)(/*[out,retval]*/ITemporarySupport** clone);
	STDMETHOD(GetMemberSegments)(/*[in]*/BSTR stage, /*[out,retval]*/IFilteredSegmentCollection** segments);
	STDMETHOD(GetSegmentsForStage)(/*[in]*/BSTR stage, /*[out,retval]*/IFilteredSegmentCollection** segments);
	STDMETHOD(GetSegmentForMemberLocation)(/*[in]*/BSTR stage, /*[in]*/Float64 location, ISegmentItem** ppLeftSegi, ISegmentItem** ppRightSegi);
	STDMETHOD(ReverseSegments)(/*[in]*/BSTR stage);
	STDMETHOD(RemoveSegment)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType relPosition);
	STDMETHOD(CopySegmentTo)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType fromRelPosition, /*[in]*/SegmentIndexType toRelPosition);
	STDMETHOD(MoveSegmentTo)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType fromRelPosition, /*[in]*/SegmentIndexType toRelPosition);
	STDMETHOD(InsertSegment)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType relPosition, /*[in]*/ISegment*);
	STDMETHOD(AddSegment)(/*[in]*/BSTR stage, /*[in]*/ISegment*);
	STDMETHOD(get_Segment)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType relPosition, /*[out, retval]*/ ISegment* *pVal);
	STDMETHOD(putref_Segment)(/*[in]*/BSTR stage, /*[in]*/SegmentIndexType relPosition, /*[in]*/ ISegment* newVal);
	STDMETHOD(get_SegmentCount)(/*[in]*/BSTR stage, /*[out, retval]*/ SegmentIndexType *pVal);
	STDMETHOD(get_SegmentLength)(/*[in]*/BSTR stage, /*[out, retval]*/ Float64 *pVal);
	STDMETHOD(get_BoundaryCondition)(/*[out, retval]*/ BoundaryConditionType *pVal);
	STDMETHOD(put_BoundaryCondition)(/*[in]*/ BoundaryConditionType newVal);
	STDMETHOD(get_Length)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Length)(/*[in]*/ Float64 newVal);
	STDMETHOD(get_BottomOffset)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_BottomOffset)(/*[in]*/ Float64 newVal);
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval);  
	STDMETHOD(get__EnumElements)(/*[out, retval]*/ IEnumSegmentItem* *pVal);
	STDMETHOD(get_StageRemoved)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_StageRemoved)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Location)(/*[out, retval]*/ Float64 *pVal);
	STDMETHOD(put_Location)(/*[in]*/ Float64 newVal);

   // CSegmentsOwner
   virtual HRESULT SetUpConnection(ISegmentItem* pCp, DWORD* pcookie);
   virtual void BreakConnection(ISegmentItem* pCp, DWORD cookie);
   virtual void OnSegmentsChanged(CSegments* psegments, BSTR stage, ChangeType change);
   virtual Float64 Length() { return m_Length;}

   // IStructuredStorage2
	STDMETHOD(Load)(IStructuredLoad2 * Load);
	STDMETHOD(Save)(IStructuredSave2 * Save);

   // _ISegmentItemEvents
   STDMETHOD(OnSegmentItemChanged)(/*[in]*/ISegmentItem* SegmentItem, BSTR stage, /*[in]*/ChangeType type);

   // IDistributionFactorEvents
   STDMETHOD(OnDistributionFactorChanged)(IDistributionFactor* factor);

   // implementation
   HRESULT FinalConstruct();
   void FinalRelease();

   MemberType GetMemberType()
   {
      return mtTemporarySupport;
   }

   CSegments* m_pSegments;
   Float64 m_Length;
   Float64 m_BottomOffset;
   Float64 m_Location;
   SupportIDType m_ID;
   VARIANT_BOOL m_IsSymmetrical;
   BoundaryConditionType m_BoundaryCondition;
   CComBSTR m_StageRemoved;
   VARIANT_BOOL m_TopRelease;
   VARIANT_BOOL m_bOmitReaction;


   CLoadModifierHelper m_LoadModifierHelper;

   CComPtr<IDistributionFactor>     m_DistributionFactor;
   DWORD                            m_DistributionFactorCookie;
};

#endif //__TEMPORARYSUPPORT_H_
