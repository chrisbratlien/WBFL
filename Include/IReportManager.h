///////////////////////////////////////////////////////////////////////
// ReportManagerAgent - Provides report manager as an Agent
// Copyright � 1999-2020  Washington State Department of Transportation
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

#pragma once

#include <ReportManager\ReportManager.h>


// {61C524E8-7D77-4345-8954-B53539516BEB}
DEFINE_GUID(IID_IReportManager, 
0x61c524e8, 0x7d77, 0x4345, 0x89, 0x54, 0xb5, 0x35, 0x39, 0x51, 0x6b, 0xeb);
interface IReportManager : IUnknown
{
   virtual void AddReportBuilder(CReportBuilder* pRptBuilder) = 0;
   virtual void AddReportBuilder(std::shared_ptr<CReportBuilder>& pReportBuilder) = 0;
   virtual CollectionIndexType GetReportBuilderCount(bool bIncludeHidden = false) const = 0;
   virtual std::shared_ptr<CReportBuilder> GetReportBuilder(LPCTSTR strReportName) = 0;
   virtual std::shared_ptr<CReportBuilder> GetReportBuilder(const std::_tstring& strReportName) = 0;
   virtual std::shared_ptr<CReportBuilder> RemoveReportBuilder(LPCTSTR strReportName) = 0;
   virtual std::shared_ptr<CReportBuilder> RemoveReportBuilder(const std::_tstring& strReportName) = 0;
   virtual std::vector<std::_tstring> GetReportNames(bool bIncludeHidden = false) const = 0;
   virtual CReportDescription GetReportDescription(LPCTSTR strReportName) = 0;
   virtual CReportDescription GetReportDescription(const std::_tstring& strReportName) = 0;
   virtual const CBitmap* GetMenuBitmap(LPCTSTR strReportName) = 0;
   virtual const CBitmap* GetMenuBitmap(const std::_tstring& strReportName) = 0;
   virtual std::shared_ptr<CReportSpecificationBuilder> GetReportSpecificationBuilder(LPCTSTR strReportName) = 0;
   virtual std::shared_ptr<CReportSpecificationBuilder> GetReportSpecificationBuilder(const std::_tstring& strReportName) = 0;
   virtual std::shared_ptr<CReportSpecificationBuilder> GetReportSpecificationBuilder(const CReportDescription& rptDesc) = 0;
   virtual std::shared_ptr<CReportBrowser> CreateReportBrowser(HWND hwndParent, std::shared_ptr<CReportSpecification>& pRptSpec, std::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder) = 0;
   virtual INT_PTR DisplayReportDialog(DWORD flags, std::shared_ptr<CReportSpecification>& pRptSpec, std::shared_ptr<CReportSpecificationBuilder>& pRptSpecBuilder) = 0;
};
