///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright � 1999-2014  Washington State Department of Transportation
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

// Tendon.h : Declaration of the CTendon

#ifndef __TENDON_H_
#define __TENDON_H_

#include "resource.h"       // main symbols
#include <WBFLComCollections.h>
//#include "GenericBridgeCP.h"

class CTendon;
typedef CComVectorCollection<ITendon,ITendonSegment,IEnumTendonSegments,&IID_IEnumTendonSegments,CollectionIndexType> TendonSegmentColl;
typedef CPersistentCollection<CTendon,TendonSegmentColl, CollectionIndexType> PersistentTendonSegmentCollection;

/////////////////////////////////////////////////////////////////////////////
// CTendon
class ATL_NO_VTABLE CTendon : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CTendon,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CTendon, &CLSID_Tendon>,
	public ISupportErrorInfo,
	//public ITendon,
   public PersistentTendonSegmentCollection,
//   public CProxyDTendonEvents< CTendon >,
//   public ITendonPointContainerImpl<CTendon>,
   public IObjectSafetyImpl<CTendon,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:
   CTendon()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_TENDON)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTendon)
	COM_INTERFACE_ENTRY(ITendon)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY_CHAIN(PersistentTendonSegmentCollection)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTendon)
//	CONNECTION_POINT_ENTRY(IID_ITendonEvents)
END_CONNECTION_POINT_MAP()

private:
   Float64 m_OD; // outside diameter
   Float64 m_ID; // inside diamter
   StrandIndexType m_StrandCount;
   CComPtr<IPrestressingStrand> m_Material;
   JackingEndType m_JackingEnd;

   bool GetTendonSegment(Float64 z,ITendonSegment** segment);

   ISuperstructureMember* m_pSSMbr; // weak references

#if defined _DEBUG
   virtual HRESULT OnBeforeAdd( StoredType* pVal);
#endif

   // ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITendon
public:
   STDMETHOD(AddSegment)(/*[in]*/ ITendonSegment* segment);
	STDMETHOD(get_Segment)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ITendonSegment** segment);
	STDMETHOD(get_Count)(/*[out,retval]*/CollectionIndexType* count);
	STDMETHOD(RemoveSegment)(/*[in]*/ CollectionIndexType index);
	STDMETHOD(ClearSegments)();
	STDMETHOD(get_OutsideDiameter)(/*[out,retval]*/Float64* size);
	STDMETHOD(put_OutsideDiameter)(/*[in]*/Float64 size);
	STDMETHOD(get_InsideDiameter)(/*[out,retval]*/Float64* size);
	STDMETHOD(put_InsideDiameter)(/*[in]*/Float64 size);
	STDMETHOD(get_InsideDuctArea)(/*[out,retval]*/Float64* Apt);
	STDMETHOD(get_TendonArea)(/*[out,retval]*/Float64* Apt);
	STDMETHOD(get_StrandCount)(/*[out,retval]*/StrandIndexType* count);
	STDMETHOD(put_StrandCount)(/*[in]*/StrandIndexType count);
	STDMETHOD(get_Material)(/*[out,retval]*/IPrestressingStrand** material);
	STDMETHOD(putref_Material)(/*[in]*/IPrestressingStrand* material);
   STDMETHOD(get_MinimumRadiusOfCurvature)(/*[out,retval]*/Float64* pMinRadiusOfCurvature);
   STDMETHOD(get_CG)(/*[in]*/ Float64 z,/*[in]*/ TendonMeasure measure,/*[out,retval]*/IPoint3d** cg);
	STDMETHOD(get_Slope)(/*[in]*/ Float64 z,/*[in]*/ TendonMeasure measure,/*[out,retval]*/IVector3d** slope);
	STDMETHOD(get_Length)(/*[out,retval]*/Float64* length);
   STDMETHOD(get_Start)(IPoint3d** start);
	STDMETHOD(get_End)(IPoint3d** end);
   STDMETHOD(get_Centerline)(/*[in]*/ TendonMeasure measure,/*[out,retval]*/IPoint3dCollection** ppPoints);
   STDMETHOD(get_JackingEnd)(/*[out,retval]*/JackingEndType* type);
   STDMETHOD(put_JackingEnd)(/*[in]*/JackingEndType type);
   STDMETHOD(putref_SuperstructureMember)(/*[in]*/ISuperstructureMember* pMbr);
   STDMETHOD(get_SuperstructureMember)(/*[out,retval]*/ISuperstructureMember** ppMbr);


// IStructuredStorage2
public:
	STDMETHOD(Load)(/*[in]*/ IStructuredLoad2* load);
	STDMETHOD(Save)(/*[in]*/ IStructuredSave2* save);
};

#endif //__TENDON_H_
