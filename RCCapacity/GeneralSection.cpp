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

// GeneralSection.cpp : Implementation of CGeneralSection
#include "stdafx.h"
#include "WBFLRCCapacity.h"
#include "GeneralSection.h"
#include <WBFLGeometry.h>
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneralSection
HRESULT CGeneralSection::FinalConstruct()
{
   return S_OK;
}

void CGeneralSection::FinalRelease()
{
	m_SectionItems.clear();
}


STDMETHODIMP CGeneralSection::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGeneralSection,
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// IGeneralSection
STDMETHODIMP CGeneralSection::AddShape(IShape* pShape,IStressStrain* pfgMaterial,IStressStrain* pbgMaterial,Float64 ei,Float64 Le)
{
   if ( pShape == nullptr )
      return E_INVALIDARG;

   if (IsZero(Le))
      return E_INVALIDARG;

   ATLASSERT(1.0 <= Le); // Le should be 1 for unit or greater...

   m_SectionItems.emplace_back(pShape,pfgMaterial,pbgMaterial,ei,Le);

   return S_OK;
}

STDMETHODIMP CGeneralSection::get_ShapeCount(CollectionIndexType* nShapes)
{
   CHECK_RETVAL(nShapes);
   *nShapes = m_SectionItems.size();
   return S_OK;
}

STDMETHODIMP CGeneralSection::get_Shape(CollectionIndexType shapeIdx,IShape** pShape)
{
   CHECK_RETOBJ(pShape);
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   (*pShape) = m_SectionItems[shapeIdx].shape;
   (*pShape)->AddRef();

   return S_OK;
}

STDMETHODIMP CGeneralSection::putref_Shape(CollectionIndexType shapeIdx,IShape* pShape)
{
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   CHECK_IN(pShape);

   m_SectionItems[shapeIdx].shape.Release();
   m_SectionItems[shapeIdx].shape = pShape;
   
   return S_OK;
}

STDMETHODIMP CGeneralSection::get_ForegroundMaterial(CollectionIndexType shapeIdx,IStressStrain** pMaterial)
{
   CHECK_RETOBJ(pMaterial);
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   (*pMaterial) = m_SectionItems[shapeIdx].fgMaterial;

   if ( *pMaterial )
      (*pMaterial)->AddRef();

   return S_OK;
}

STDMETHODIMP CGeneralSection::putref_ForegroundMaterial(CollectionIndexType shapeIdx,IStressStrain* pMaterial)
{
   CHECK_IN(pMaterial);
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   m_SectionItems[shapeIdx].fgMaterial.Release();
   m_SectionItems[shapeIdx].fgMaterial = pMaterial;

   return S_OK;
}

STDMETHODIMP CGeneralSection::get_BackgroundMaterial(CollectionIndexType shapeIdx,IStressStrain** pMaterial)
{
   CHECK_RETOBJ(pMaterial);
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   (*pMaterial) = m_SectionItems[shapeIdx].bgMaterial;

   if ( *pMaterial )
      (*pMaterial)->AddRef();

   return S_OK;
}

STDMETHODIMP CGeneralSection::putref_BackgroundMaterial(CollectionIndexType shapeIdx,IStressStrain* pMaterial)
{
   CHECK_IN(pMaterial);
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   m_SectionItems[shapeIdx].bgMaterial.Release();
   m_SectionItems[shapeIdx].bgMaterial = pMaterial;

   return S_OK;
}

STDMETHODIMP CGeneralSection::get_InitialStrain(CollectionIndexType shapeIdx,Float64* ei)
{
   CHECK_RETVAL(ei);
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   *ei = m_SectionItems[shapeIdx].ei;

   return S_OK;
}

STDMETHODIMP CGeneralSection::put_InitialStrain(CollectionIndexType shapeIdx,Float64 ei)
{
   if ( m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX )
      return E_INVALIDARG;

   m_SectionItems[shapeIdx].ei = ei;

   return S_OK;
}

STDMETHODIMP CGeneralSection::get_ElongationLength(CollectionIndexType shapeIdx, Float64* Le)
{
   CHECK_RETVAL(Le);

   if (m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX)
      return E_INVALIDARG;

   *Le = m_SectionItems[shapeIdx].Le;

   return S_OK;
}

STDMETHODIMP CGeneralSection::put_ElongationLength(CollectionIndexType shapeIdx, Float64 Le)
{
   if (m_SectionItems.size() <= shapeIdx || shapeIdx == INVALID_INDEX)
      return E_INVALIDARG;

   m_SectionItems[shapeIdx].Le = Le;

   return S_OK;
}

///////////////////////////////////////////////////////////////////
// IStructuredStorage2
STDMETHODIMP CGeneralSection::Save(IStructuredSave2* pSave)
{
   CHECK_IN(pSave);

   pSave->BeginUnit(CComBSTR("GeneralSection"),2.0);

   pSave->put_Property(CComBSTR("SectionItemCount"),CComVariant(m_SectionItems.size()));

   for ( auto& item : m_SectionItems )
   {
      pSave->put_Property(CComBSTR("Shape"),CComVariant(item.shape));
      pSave->put_Property(CComBSTR("FGMaterial"),item.fgMaterial ? CComVariant(item.fgMaterial) : 0);
      pSave->put_Property(CComBSTR("BGMaterial"),item.bgMaterial ? CComVariant(item.bgMaterial) : 0);
      pSave->put_Property(CComBSTR("InitialStrain"), CComVariant(item.ei));
      pSave->put_Property(CComBSTR("ElongationLength"), CComVariant(item.Le)); // added in vesion 2
   }

   pSave->EndUnit();

   return S_OK;
}

STDMETHODIMP CGeneralSection::Load(IStructuredLoad2* pLoad)
{
   CHECK_IN(pLoad);

   CComVariant var;
   pLoad->BeginUnit(CComBSTR("GeneralSection"));

   Float64 version;
   pLoad->get_Version(&version);

   m_SectionItems.clear();

   CollectionIndexType count;
   if ( FAILED(pLoad->get_Property(CComBSTR("SectionItemCount"), &var) ) )
      return STRLOAD_E_INVALIDFORMAT;
   count = var.lVal;

   for ( CollectionIndexType index = 0; index < count; index++ )
   {
      SectionItem item;

      if (FAILED(pLoad->get_Property(CComBSTR("Shape"), &var)))
      {
         return STRLOAD_E_INVALIDFORMAT;
      }
      var.punkVal->QueryInterface(&item.shape);

      if (FAILED(pLoad->get_Property(CComBSTR("FGMaterial"), &var)))
      {
         return STRLOAD_E_INVALIDFORMAT;
      }

      if ( var.punkVal )
      {
         var.punkVal->QueryInterface(&item.fgMaterial);
      }

      if (FAILED(pLoad->get_Property(CComBSTR("BGMaterial"), &var)))
      {
         return STRLOAD_E_INVALIDFORMAT;
      }

      if ( var.punkVal )
      {
         var.punkVal->QueryInterface(&item.bgMaterial);
      }

      if (FAILED(pLoad->get_Property(CComBSTR("InitialStrain"), &var)))
      {
         return STRLOAD_E_INVALIDFORMAT;
      }
      item.ei = var.dblVal;

      if (1 < version)
      {
         // added in version 2

         if (FAILED(pLoad->get_Property(CComBSTR("ElongationLength"), &var)))
         {
            return STRLOAD_E_INVALIDFORMAT;
         }
         item.Le = var.dblVal;
      }

      m_SectionItems.push_back(item);
   }

   VARIANT_BOOL bEnd;
   pLoad->EndUnit(&bEnd);

   ATLASSERT(bEnd == VARIANT_TRUE);

   return S_OK;
}
