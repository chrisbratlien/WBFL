///////////////////////////////////////////////////////////////////////
// RCCapacity - Reinforced Concrete Capacity Analysis Library
// Copyright � 2003  Washington State Department of Transportation
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

// GeneralSection.h : Declaration of the CGeneralSection

#ifndef __GeneralSection_H_
#define __GeneralSection_H_

#include "resource.h"       // main symbols
#include <WBFLUnitServer.h>
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CGeneralSection
class ATL_NO_VTABLE CGeneralSection : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGeneralSection, &CLSID_GeneralSection>,
	public ISupportErrorInfo,
	public IGeneralSection,
   public IStructuredStorage2
{
public:
	CGeneralSection()
	{
	}

   HRESULT FinalConstruct();
   void FinalRelease();

DECLARE_REGISTRY_RESOURCEID(IDR_GENERALSECTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGeneralSection)
	COM_INTERFACE_ENTRY(IGeneralSection)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
   COM_INTERFACE_ENTRY(IStructuredStorage2)
END_COM_MAP()


private:
   struct SectionItem
   {
      CComPtr<IShape> shape;
      CComPtr<IStressStrain> fgMaterial;
      CComPtr<IStressStrain> bgMaterial;
      Float64 ei; // initial strain
      Float64 Le; // elongation length
      SectionItem() : ei(0), Le(1.0)
      {}
      SectionItem(IShape* pShape,IStressStrain* pFG,IStressStrain* pBG,Float64 ei,Float64 le) : shape(pShape), fgMaterial(pFG), bgMaterial(pBG), ei(ei), Le(le)
      {}
   };

   std::vector<SectionItem> m_SectionItems;

// ISupportsErrorInfo
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) override;

// IGeneralSection
public:
   STDMETHOD(AddShape)(/*[in]*/IShape* pShape,/*[in]*/IStressStrain* pfgMaterial,/*[in]*/IStressStrain* pbgMaterial,/*[in]*/Float64 ei,/*[in]*/Float64 Le) override;
   STDMETHOD(get_ShapeCount)(/*[out,retval]*/CollectionIndexType* nShapes) override;
   STDMETHOD(get_Shape)(/*[in]*/CollectionIndexType shapeIdx,/*[out,retval]*/IShape** pShape) override;
   STDMETHOD(putref_Shape)(/*[in]*/CollectionIndexType shapeIdx,/*[in]*/IShape* pShape) override;
   STDMETHOD(get_ForegroundMaterial)(/*[in]*/CollectionIndexType shapeIdx,/*[out,retval]*/IStressStrain** pMaterial) override;
   STDMETHOD(putref_ForegroundMaterial)(/*[in]*/CollectionIndexType shapeIdx,/*[in]*/IStressStrain* pMaterial) override;
   STDMETHOD(get_BackgroundMaterial)(/*[in]*/CollectionIndexType shapeIdx,/*[out,retval]*/IStressStrain** pMaterial) override;
   STDMETHOD(putref_BackgroundMaterial)(/*[in]*/CollectionIndexType shapeIdx,/*[in]*/IStressStrain* pMaterial) override;
   STDMETHOD(get_InitialStrain)(/*[in]*/CollectionIndexType shapeIdx,/*[out,retval]*/Float64* ei) override;
   STDMETHOD(put_InitialStrain)(/*[in]*/CollectionIndexType shapeIdx,/*[in]*/Float64 ei) override;
   STDMETHOD(get_ElongationLength)(/*[in]*/CollectionIndexType shapeIdx, /*[out, retval]*/Float64* Le);
   STDMETHOD(put_ElongationLength)(/*[in]*/CollectionIndexType shapeIdx, /*[in]*/Float64 Le);

// IStructuredStorage2
public:
   STDMETHOD(Save)(IStructuredSave2* pSave) override;
   STDMETHOD(Load)(IStructuredLoad2* pLoad) override;
};

#endif //__GeneralSection_H_
