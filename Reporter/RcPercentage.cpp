///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
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

#include <Reporter\ReporterLib.h>
#include <Reporter\RcPercentage.h>
#include <Reporter\RcVisitor.h>
#include <sstream>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptRcPercentage
****************************************************************************/



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rptRcPercentage::rptRcPercentage() :
rptRcScalar()
{
}

rptRcPercentage::rptRcPercentage(Float64 value) :
rptRcScalar(value)
{
}

rptRcPercentage::rptRcPercentage(const rptRcPercentage& rOther) :
rptRcScalar(rOther)
{
}

rptRcPercentage::~rptRcPercentage()
{
}

//======================== OPERATIONS =======================================
void rptRcPercentage::Accept( rptRcVisitor& rVisitor )
{
   rVisitor.VisitRcPercentage( this );
}

rptReportContent* rptRcPercentage::CreateClone() const
{
   return new rptRcPercentage( *this );
}

std::_tstring rptRcPercentage::AsString() const
{
   sysNumericFormatTool fmt(m_Format,m_Width,m_Precision);
   return fmt.AsString( GetValue()*100 ) + _T(" %");
}

//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool rptRcPercentage::AssertValid() const
{
   //return rptReportContent::AssertValid();
   return true;
}

void rptRcPercentage::Dump(dbgDumpContext& os) const
{
   //rptReportContent::Dump( os );
   os << "rptRcPercentage : Value = " << m_Value << endl;
}
#endif // _DEBUG


