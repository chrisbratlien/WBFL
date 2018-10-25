///////////////////////////////////////////////////////////////////////
// COGO - Coordinate Geometry Library
// Copyright � 1999-2012  Washington State Department of Transportation
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

// PathCollection.h : Declaration of the CPathCollection

#ifndef __PATHCOLLECTION_H_
#define __PATHCOLLECTION_H_
#pragma once

#include "resource.h"       // main symbols
#include "Collections.h"
#include "COGOCP.h"

class CPathCollection;
typedef PersistentKeyedCollection<CPathCollection,IPathCollection,&IID_IPathCollection,CogoElementKey,IPath> PathCollectionImpl;

/////////////////////////////////////////////////////////////////////////////
// CPathCollection
class ATL_NO_VTABLE CPathCollection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//   public CComRefCountTracer<CPathCollection,CComObjectRootEx<CComSingleThreadModel> >,
	public CComCoClass<CPathCollection, &CLSID_PathCollection>,
	public IConnectionPointContainerImpl<CPathCollection>,
   public PathCollectionImpl,
   public IPathEvents,
	public CProxyDPathCollectionEvents< CPathCollection >
{
public:
   CPathCollection() :
      m_bstrCollectionName("Paths"),
      m_bstrItemName("Path")
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_PATHCOLLECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPathCollection)
	COM_INTERFACE_ENTRY(IPathEvents)

	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

   COM_INTERFACE_ENTRY_CHAIN(PathCollectionImpl)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPathCollection)
CONNECTION_POINT_ENTRY(IID_IPathCollectionEvents)
END_CONNECTION_POINT_MAP()

virtual void SetCollectionName(BSTR bstrCollectionName) { m_bstrCollectionName = bstrCollectionName; }
   virtual void SetItemName(BSTR bstrItemName) { m_bstrItemName = bstrItemName; }
   virtual CComBSTR GetCollectionName() { return m_bstrCollectionName; }
   virtual CComBSTR GetItemName() { return m_bstrItemName; }

// IPathCollection
public:
//   STDMETHOD(get_StructuredStorage)(/*[out,retval]*/IStructuredStorage2* *pStg);
   STDMETHOD(Clone)(/*[out,retval]*/ IPathCollection* *clone);
   STDMETHOD(get__EnumPaths)(/*[out,retval]*/ IEnumPaths** ppenum);
	STDMETHOD(get_Factory)(/*[out,retval]*/IPathFactory** factory);
	STDMETHOD(putref_Factory)(/*[in]*/IPathFactory* factory);
//   STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown** retval);  
   STDMETHOD(get_Item)(/*[in]*/ CogoElementKey key, /*[out, retval]*/ IPath* *pVal);
   STDMETHOD(putref_Item)(/*[in]*/ CogoElementKey key, /*[in]*/ IPath* pVal);
   STDMETHOD(get_Count)(/*[out, retval]*/ CollectionIndexType *pVal);
   STDMETHOD(AddEx)(/*[in]*/ CogoElementKey key,/*[in]*/ IPath* newVal);
   STDMETHOD(Add)(/*[in]*/ CogoElementKey key,/*[out,retval]*/ IPath* *Path);
   STDMETHOD(Remove)(/*[in]*/ CogoElementKey key);
   STDMETHOD(Clear)();
   STDMETHOD(FindKey)(/*[in]*/ IPath* Path,/*[out,retval]*/CogoElementKey* key);
   STDMETHOD(get__EnumKeys)(/*[out,retval]*/ IEnumKeys** ppenum);
//	STDMETHOD(get_Factory)(/*[out,retval]*/IPoint2dFactory** factory);
//	STDMETHOD(putref_Factory)(/*[in]*/IPoint2dFactory* factory);
   STDMETHOD(Key)(/*[in]*/ CollectionIndexType index,/*[out,retval]*/ CogoElementKey* key);

// IPathEvents
	STDMETHOD(OnPathChanged)(IPath * Path)
	{
      CogoElementKey key;
      FindKey(Path,&key);
      Fire_OnPathChanged(this,key,Path);
		return S_OK;
	}
	STDMETHOD(OnProfileChanged)(IProfile * profile)
	{
      Fire_OnProfileChanged(this,profile);
		return S_OK;
	}

private:
   HRESULT OnBeforeSave(IStructuredSave2* pSave);
   HRESULT OnBeforeLoad(IStructuredLoad2* pLoad);
   HRESULT PathNotFound(CogoElementKey key);
   HRESULT PathAlreadyDefined(CogoElementKey key);
   HRESULT PathKeyError(CogoElementKey key,UINT nHelpString,HRESULT hRes);

   void Advise(CogoElementKey key,IPath* Path);
   void Unadvise(CogoElementKey key,IPath* Path);
   void UnadviseAll();
   std::map<CogoElementKey,DWORD> m_Cookies;

   CComPtr<IPathFactory> m_Factory;

   CComBSTR m_bstrCollectionName;
   CComBSTR m_bstrItemName;
};

#endif //__PATHCOLLECTION_H_
