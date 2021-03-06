///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
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

// Station.h : Declaration of the CStation

#ifndef __STATION_H_
#define __STATION_H_
#pragma once

#include "resource.h"       // main symbols
#include "COGOCP.h"

/////////////////////////////////////////////////////////////////////////////
// CStation
class ATL_NO_VTABLE CStation : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStation, &CLSID_Station>,
	public ISupportErrorInfo,
   public IObjectSafetyImpl<CStation,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public IStation,
   public IStructuredStorage2,
   public IPersistImpl<CStation>,
   public CProxyDStationEvents< CStation >,
   public IConnectionPointContainerImpl<CStation>
{
public:
	CStation()
	{
      m_ZoneIdx = INVALID_INDEX; // this is a normalized station value
      m_Value = 0.0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STATION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStation)
	COM_INTERFACE_ENTRY(IStation)
	COM_INTERFACE_ENTRY(IStructuredStorage2)
   COM_INTERFACE_ENTRY(IObjectSafety)
   COM_INTERFACE_ENTRY(IPersist)
   COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

   Float64 m_Value;
   ZoneIndexType m_ZoneIdx;

   HRESULT StationToString(int nDigOffset,int nDec,VARIANT_BOOL vbIncludeStationZone,BSTR* strStation);
   HRESULT StringToStation(BSTR strString,int nDigOffset,int nDec);

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IStation
public:
   STDMETHOD(get_StructuredStorage)(/*[out, retval]*/ IStructuredStorage2* *pVal) override;
   STDMETHOD(Clone)(/*[out,retval]*/ IStation* *clone) override;
	STDMETHOD(AsString)(/*[in]*/ UnitModeType unitMode,/*[in]*/ VARIANT_BOOL vbIncludeStationZone, /*[out,retval]*/ BSTR* station) override;
	STDMETHOD(FromString)(/*[in]*/ BSTR station,/*[in]*/ UnitModeType unitMode) override;
	STDMETHOD(get_Value)(/*[out, retval]*/ Float64 *pVal) override;
	STDMETHOD(put_Value)(/*[in]*/ Float64 newVal) override;
   STDMETHOD(get_NormalizedValue)(/*[in]*/IAlignment* pAlignment,/*[out,retval]*/Float64* pValue) override;
   STDMETHOD(Offset)(/*[in]*/Float64 offset) override;
   STDMETHOD(GetStation)(ZoneIndexType* pZoneIdx,Float64* pStation) override;
   STDMETHOD(SetStation)(ZoneIndexType zoneIdx,Float64 station) override;
   STDMETHOD(FromVariant)(/*[in]*/ VARIANT varStation) override;
   STDMETHOD(get_StationZoneIndex)(ZoneIndexType *pVal) override;
	STDMETHOD(put_StationZoneIndex)(ZoneIndexType newVal) override;

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;
public :

BEGIN_CONNECTION_POINT_MAP(CStation)
	CONNECTION_POINT_ENTRY(IID_IStationEvents)
END_CONNECTION_POINT_MAP()

};

#endif //__STATION_H_
