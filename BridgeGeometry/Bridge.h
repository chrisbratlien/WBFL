// Bridge.h : Declaration of the CBridge

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"
#include "PierLineCollection.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CBridge

class ATL_NO_VTABLE CBridge :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CBridge, &CLSID_BridgeGeometry>,
	public IBridgeGeometry
{
public:
	CBridge()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BRIDGE)

DECLARE_NOT_AGGREGATABLE(CBridge)

BEGIN_COM_MAP(CBridge)
	COM_INTERFACE_ENTRY(IBridgeGeometry)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      m_BridgeAlignmentID = INVALID_INDEX;

      HRESULT hr = S_OK;
      CComObject<CPierLineCollection>* pPierLines;
      hr = CComObject<CPierLineCollection>::CreateInstance(&pPierLines);
      if ( FAILED(hr) )
         return hr;

      m_PierLines = pPierLines;


      hr = m_LayoutLines.CoCreateInstance(CLSID_PathCollection);
      if ( FAILED(hr) )
         return hr;

      m_AlignmentOffset = 0;

		return S_OK;
	}

	void FinalRelease()
	{
      m_CogoModel.Release();
      m_PierLines.Release();
      m_LayoutLines.Release();
	}

   CComPtr<ICogoModel> m_CogoModel;

   typedef std::map<CogoObjectID,CComPtr<IAlignment>> AlignmentCollection;
   AlignmentCollection m_Alignments;

   CogoObjectID m_BridgeAlignmentID; // ID of the primary bridge alignment

   Float64 m_AlignmentOffset; // distance from the alignment to the bridge reference line (typically the bridge centerline)
                              // positive value locates the bridge line to the left of the bridge alignment

   CComPtr<IPath> m_BridgeLine; // this is the bridge reference line. it is a path that is parallel to the bridge alignemnt
                                // and offset by the alignment offset

   CComPtr<IPathCollection> m_LayoutLines; // geometric layout lines

   CComPtr<IPierLineCollection> m_PierLines; // pier layout lines
   
   typedef std::map<GirderIDType,CComPtr<IGirderLine>> GirderLineCollection;
   GirderLineCollection m_GirderLines;
   
   typedef std::map<GirderIDType,CComPtr<IDiaphragmLine>> DiaphragmLineCollection;
   DiaphragmLineCollection m_DiaphragmLines;

   CComPtr<IDeckBoundary> m_DeckBoundary;

   void ClearGeometry();
   void ClearPierGeometry();
   void ClearGirderGeometry();

   HRESULT UpdateBridgeLine();
   HRESULT UpdatePierGeometry();
   HRESULT UpdateGirderGeometry();
   HRESULT UpdateDiaphragmGeometry();
   HRESULT UpdateDeckBoundaryGeometry();

   HRESULT PierPathIntersect(IPierLine* pPier,IPath* pPath,IPoint2d** ppPoint);

#if defined _DEBUG
   void AssertValid();
#endif

public:
   STDMETHOD(putref_CogoModel)(ICogoModel* pCogoModel);
   STDMETHOD(get_CogoModel)(ICogoModel** pCogoModel);
   STDMETHOD(putref_Alignment)(CogoObjectID ID,IAlignment* pAligment);
   STDMETHOD(get_Alignment)(CogoObjectID ID,IAlignment** pAlignment);
   STDMETHOD(put_BridgeAlignmentID)(CogoObjectID ID);
   STDMETHOD(get_BridgeAlignmentID)(CogoObjectID* ID);
   STDMETHOD(get_BridgeAlignment)(IAlignment** alignment);
   STDMETHOD(put_AlignmentOffset)(Float64 offset);
   STDMETHOD(get_AlignmentOffset)(Float64* offset);
   STDMETHOD(get_BridgeLine)(IPath** path);
   STDMETHOD(CreateLayoutLines)(ILayoutLineFactory* pFactory);
   STDMETHOD(FindLayoutLine)(LineIDType ID,IPath** path);
   STDMETHOD(get_LayoutLineCount)(CollectionIndexType* pVal);
   STDMETHOD(CreatePierLine)(PierIDType ID, CogoObjectID alignmentID,VARIANT station, BSTR orientation, Float64 width, Float64 offset,IPierLine** ppPier);
   STDMETHOD(GetPierLine)(PierIndexType idx, IPierLine** ppPier);
   STDMETHOD(FindPierLine)(PierIDType ID, IPierLine** ppPier);
   STDMETHOD(get_PierLineCount)(PierIndexType* pVal);
   STDMETHOD(CreateGirderLines)(IGirderLineFactory* pFactory);
   STDMETHOD(FindGirderLine)(GirderIDType ID,IGirderLine** ppGirderLine);
   STDMETHOD(get_GirderLineCount)(CollectionIndexType* pVal);
   STDMETHOD(CreateDiaphragmLines)(IDiaphragmLineFactory* pFactory);
   STDMETHOD(FindDiaphragmLine)(LineIDType ID,IDiaphragmLine** ppDiaphragmLine);
   STDMETHOD(get_DiaphragmLineCount)(CollectionIndexType* pVal);
   STDMETHOD(CreateDeckBoundary)(IDeckBoundaryFactory* pFactory);
   STDMETHOD(get_DeckBoundary)(IDeckBoundary** ppDeckBoundary);
   STDMETHOD(UpdateGeometry)();
};

OBJECT_ENTRY_AUTO(__uuidof(BridgeGeometry), CBridge)