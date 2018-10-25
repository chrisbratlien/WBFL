///////////////////////////////////////////////////////////////////////
// LBAM Live Loader - Longitindal Bridge Analysis Model
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

// BasicVehicularResponse.h : Declaration of the CBasicVehicularResponse

#ifndef __BASICVEHICULARRESPONSE_H_
#define __BASICVEHICULARRESPONSE_H_

#include "resource.h"       // main symbols
#include "LiveLoaderUtils.h"
#include "ComputeInfluenceLineStrategy.h"
#include "DistributionFactorStrategy.h"
#include "LLApplicabilityStrategy.h"

/////////////////////////////////////////////////////////////////////////////
// CBasicVehicularResponse
class ATL_NO_VTABLE CBasicVehicularResponse : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBasicVehicularResponse, &CLSID_BasicVehicularResponse>,
	public ISupportErrorInfo,
	public IBasicVehicularResponse,
	public IDependOnVehicularAnalysisContext,
   public IObjectSafetyImpl<CBasicVehicularResponse,INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>,
	public ISupportProgressMonitor
{
public:
   CBasicVehicularResponse():
   m_InflStrategy(NULL),
   m_DfStrategy(NULL),
   m_ApplicabilityStrategy(NULL)
	{
	}
 
DECLARE_REGISTRY_RESOURCEID(IDR_BASICVEHICULARRESPONSE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBasicVehicularResponse)
	COM_INTERFACE_ENTRY(IBasicVehicularResponse)
	COM_INTERFACE_ENTRY(IDependOnVehicularAnalysisContext)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(ISupportProgressMonitor)
   COM_INTERFACE_ENTRY(IObjectSafety)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IBasicVehicularResponse
public:
	STDMETHOD(ComputeForces)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage, /*[in]*/ResultsOrientation orientation,
                            /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/ISectionResult3Ds* *results);

	STDMETHOD(ComputeDeflections)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage,
                                /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/ISectionResult3Ds* *results);

	STDMETHOD(ComputeReactions)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage,
                               /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/IResult3Ds* *results);

	STDMETHOD(ComputeSupportDeflections)(/*[in]*/ILongArray* supports, /*[in]*/BSTR stage,
                                        /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/IResult3Ds* *results);

	STDMETHOD(ComputeStresses)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage,
                              /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/ISectionStressResults* *results);
public:
// IDependOnVehicularAnalysisContext
	STDMETHOD(Initialize)(/*[in]*/IUnknown* context);

// ISupportProgressMonitor
	STDMETHOD(InitializeProgressMonitor)(IProgressMonitor * newVal, LONG cookie);

public: // but not COM
   // quick initialization for local clients
   void QuickInitialize(ILiveLoad* liveLoad, IInfluenceLineResponse* influenceLineResponse, 
                        ILiveLoadNegativeMomentRegion* nllmr, IGetDistributionFactors* getDistributionFactors,
                        ISupportLocations* supportLocations, IGetStressPoints* getStressPoints);

private:
	STDMETHOD(ComputeResponse)(/*[in]*/ILongArray* pois, /*[in]*/BSTR stage,
                              /*[in]*/ILiveLoadConfiguration* config, /*[out,retval]*/ISectionResult3Ds* *results);


   void GetStressPoints(long poiID, BSTR stage, IStressPoints* *leftSps, IStressPoints* *rightSps);
   void AssertValid();

   // progress monitoring
   bool CheckForCancel()
   {
      if (m_pProgressMonitor)
      {
         VARIANT_BOOL cncl = VARIANT_FALSE;
         HRESULT hr = m_pProgressMonitor->get_WasCancelled(&cncl);
         ATLASSERT(SUCCEEDED(hr));
         return cncl!=VARIANT_FALSE;
      }
      else
         return false;
   }

   CComPtr<IProgressMonitor>                m_pProgressMonitor;
   long                                     m_ProgressCookie;

   // variables set before call to ComputeResponse to set up strategies
   iComputeInfluenceLineStrategy*     m_InflStrategy;
   iDistributionFactorStrategy*       m_DfStrategy;
   iLLApplicabilityStrategy*          m_ApplicabilityStrategy;

   // needed interfaces from context
   CComPtr<ILiveLoad>                     m_LiveLoad;
   CComPtr<IInfluenceLineResponse>        m_InfluenceLineResponse;
   CComPtr<ILiveLoadNegativeMomentRegion> m_LiveLoadNegativeMomentRegion;
   CComPtr<IGetDistributionFactors>       m_GetDistributionFactors;
   CComPtr<ISupportLocations>             m_SupportLocations;
   CComPtr<IGetStressPoints>              m_GetStressPoints;

};

#endif //__BASICVEHICULARRESPONSE_H_
