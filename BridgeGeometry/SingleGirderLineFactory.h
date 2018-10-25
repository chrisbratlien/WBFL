// SingleGirderLineFactory.h : Declaration of the CSingleGirderLineFactory

#pragma once
#include "resource.h"       // main symbols

#include "WBFLBridgeGeometry.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CSingleGirderLineFactory

class ATL_NO_VTABLE CSingleGirderLineFactory :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSingleGirderLineFactory, &CLSID_SingleGirderLineFactory>,
	public ISingleGirderLineFactory
{
public:
	CSingleGirderLineFactory()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SINGLEGIRDERLINEFACTORY)

BEGIN_COM_MAP(CSingleGirderLineFactory)
	COM_INTERFACE_ENTRY(ISingleGirderLineFactory)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
      return Reset();
	}

	void FinalRelease()
	{
	}

   GirderIDType m_GirderLineID;     // ID of the girder line that will be created
   LineIDType m_LayoutLineID;       // ID of the layout line used to create the girder line
   GirderLineType m_GirderLineType; // Type of girder line that will be created
   PierIDType m_StartPierID;        // ID of the pier where the girder line begins
   PierIDType m_EndPierID;          // ID of the pier where the girder line ends
   MeasurementType m_MeasureType[2];   // Defines if the girder layout line is intersected with
                                    // the centerline of the pier or with the normal to the alignment
                                    // where the pier intersects the alignment
   MeasurementLocation m_MeasureLocation[2]; // Defines if the girder layout line is is intersected with
                                          // the centerline of the pier or the centerline of bearing

public:

   STDMETHOD(get_GirderLineID)(GirderIDType* pVal);
   STDMETHOD(put_GirderLineID)(GirderIDType newVal);
   STDMETHOD(get_LayoutLineID)(LineIDType* pVal);
   STDMETHOD(put_LayoutLineID)(LineIDType newVal);
   STDMETHOD(get_Type)(GirderLineType* pVal);
   STDMETHOD(put_Type)(GirderLineType newVal);
   STDMETHOD(get_StartPierID)(PierIDType* pVal);
   STDMETHOD(put_StartPierID)(PierIDType newVal);
   STDMETHOD(get_EndPierID)(PierIDType* pVal);
   STDMETHOD(put_EndPierID)(PierIDType newVal);
   STDMETHOD(get_StartMeasurementType)(MeasurementType* pVal);
   STDMETHOD(put_StartMeasurementType)(MeasurementType newVal);
   STDMETHOD(get_StartMeasurementLocation)(MeasurementLocation* pVal);
   STDMETHOD(put_StartMeasurementLocation)(MeasurementLocation newVal);
   STDMETHOD(get_EndMeasurementType)(MeasurementType* pVal);
   STDMETHOD(put_EndMeasurementType)(MeasurementType newVal);
   STDMETHOD(get_EndMeasurementLocation)(MeasurementLocation* pVal);
   STDMETHOD(put_EndMeasurementLocation)(MeasurementLocation newVal);

   STDMETHOD(Create)(IBridgeGeometry* pBridge,IUnkArray** ppArrayGirderLines);
   STDMETHOD(Reset)();
};

OBJECT_ENTRY_AUTO(__uuidof(SingleGirderLineFactory), CSingleGirderLineFactory)