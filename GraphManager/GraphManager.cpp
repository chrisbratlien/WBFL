///////////////////////////////////////////////////////////////////////
// GraphManager - Manages graph definitions
// Copyright � 1999-2013  Washington State Department of Transportation
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

// GraphManager.cpp: implementation of the CGraphManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <GraphManager\GraphManager.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphManager::CGraphManager()
{
}

CGraphManager::~CGraphManager()
{
}

void CGraphManager::ClearAll()
{
   m_GraphBuilders.clear();
}

void CGraphManager::AddGraphBuilder(CGraphBuilder* pGraphBuilder)
{
   std::_tstring strName = pGraphBuilder->GetName();
   boost::shared_ptr<CGraphBuilder> p(pGraphBuilder);
   m_GraphBuilders.insert( std::make_pair( strName, p ) );
}

void CGraphManager::AddGraphBuilder(boost::shared_ptr<CGraphBuilder>& pGraphBuilder)
{
   std::_tstring strName = pGraphBuilder->GetName();
   m_GraphBuilders.insert( std::make_pair( strName, pGraphBuilder ) );
}

CollectionIndexType CGraphManager::GetGraphBuilderCount() const
{
   return m_GraphBuilders.size();
}

boost::shared_ptr<CGraphBuilder> CGraphManager::GetGraphBuilder(LPCTSTR strGraphName)
{
   return GetGraphBuilder(std::_tstring(strGraphName));
}

boost::shared_ptr<CGraphBuilder> CGraphManager::GetGraphBuilder(CollectionIndexType index)
{
   GraphBuilderContainer::iterator iter = m_GraphBuilders.begin();
   for ( CollectionIndexType i = 0; i < index; i++, iter++ )
   {}

   return iter->second;
}

boost::shared_ptr<CGraphBuilder> CGraphManager::GetGraphBuilder(const std::_tstring& strGraphName)
{
   GraphBuilderContainer::iterator found = m_GraphBuilders.find(strGraphName);
   if ( found == m_GraphBuilders.end() )
      return boost::shared_ptr<CGraphBuilder>();

   return (*found).second;
}

boost::shared_ptr<CGraphBuilder> CGraphManager::RemoveGraphBuilder(LPCTSTR strGraphName)
{
   return RemoveGraphBuilder(std::_tstring(strGraphName));
}

boost::shared_ptr<CGraphBuilder> CGraphManager::RemoveGraphBuilder(const std::_tstring& strGraphName)
{
   GraphBuilderContainer::iterator found = m_GraphBuilders.find(strGraphName);
   if ( found == m_GraphBuilders.end() )
      return boost::shared_ptr<CGraphBuilder>();

   boost::shared_ptr<CGraphBuilder> graphBuilder = (*found).second;

   m_GraphBuilders.erase(found);

   return graphBuilder;
}

std::vector<std::_tstring> CGraphManager::GetGraphNames() const
{
   std::vector<std::_tstring> names;
   GraphBuilderContainer::const_iterator iter(m_GraphBuilders.begin());
   GraphBuilderContainer::const_iterator end(m_GraphBuilders.end());
   for ( ; iter != end; iter++ )
   {
      names.push_back( (*iter).first );
   }

   return names;
}

const CBitmap* CGraphManager::GetMenuBitmap(LPCTSTR strGraphName)
{
   return GetMenuBitmap(std::_tstring(strGraphName));
}

const CBitmap* CGraphManager::GetMenuBitmap(const std::_tstring& strGraphName)
{
   boost::shared_ptr<CGraphBuilder> pGraphBuilder = GetGraphBuilder(strGraphName);
   ATLASSERT( pGraphBuilder != NULL ); // graph builder not found

   return pGraphBuilder->GetMenuBitmap();
}