///////////////////////////////////////////////////////////////////////
// ReportManager - Manages report definitions
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

// ReportSpecification.h: interface for the CReportSpecification class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTSPECIFICATION_H__7EF33026_9D78_49D4_A226_4681AD3B514C__INCLUDED_)
#define AFX_REPORTSPECIFICATION_H__7EF33026_9D78_49D4_A226_4681AD3B514C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ReportManager\ReportManagerExp.h>
#include <ReportManager\ReportDescription.h> // for CChapterInfo

class REPORTMANAGERCLASS CReportSpecification  
{
public:
	CReportSpecification(const char* strReportName);
	virtual ~CReportSpecification();

   // report name = "Details Report"
   std::string GetReportName() const;

   // report title = "Details Report for Span 1, Girder A"
   // default returns the report name
   virtual std::string GetReportTitle() const;

   void AddChapter(const char* strName,const char* strKey,Uint16 level);
   std::vector<CChapterInfo> GetChapterInfo() const;

   virtual HRESULT Validate() const;

private:
   std::string m_ReportName;
   std::vector<CChapterInfo> m_Chapters; /// chapter info for the chapters that are used in the report and the level at which to report
};

#endif // !defined(AFX_REPORTSPECIFICATION_H__7EF33026_9D78_49D4_A226_4681AD3B514C__INCLUDED_)
