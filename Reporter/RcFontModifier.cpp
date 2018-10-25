///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright � 1999-2015  Washington State Department of Transportation
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
#include <Reporter\RcFontModifier.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   rptRcFontModifier
****************************************************************************/



////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
rptRcFontModifier::rptRcFontModifier(rptRiStyle::FontModifier MyFm, StateType MyState):
rptReportContent()
{
   CHECK(MyFm!=rptRiStyle::FMSIZE);

   m_FontModifier = MyFm;
   m_State        = MyState;
}

rptRcFontModifier::rptRcFontModifier(const rptRcFontModifier& rOther) :
rptReportContent(rOther)
{
   MakeCopy(rOther);
}

rptRcFontModifier::~rptRcFontModifier()
{
}

//======================== OPERATORS  =======================================
rptRcFontModifier& rptRcFontModifier::operator= (const rptRcFontModifier& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================

void rptRcFontModifier::MakeCopy(const rptRcFontModifier& rOther)
{
   m_FontModifier = rOther.m_FontModifier;
   m_State        = rOther.m_State;
}


void rptRcFontModifier::MakeAssignment(const rptRcFontModifier& rOther)
{
   rptReportContent::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//
// accept a visitor
//
rptReportContent* rptRcFontModifier::CreateClone() const 
{ 
   return new rptRcFontModifier(*this); 
}

void rptRcFontModifier::Accept( rptRcVisitor& MyVisitor )
{
   MyVisitor.VisitRcFontModifier(this);
}


//======================== ACCESS     =======================================

//
// get/set the font modifier type
//
rptRiStyle::FontModifier rptRcFontModifier::GetFontModifier()
{
   return m_FontModifier;
}

void rptRcFontModifier::SetFontModifier(rptRiStyle::FontModifier MyFont)
{
   m_FontModifier = MyFont;
}

//
// get/set the state flag
//
rptRcFontModifier::StateType rptRcFontModifier::GetState()
{
   return m_State;
}

void rptRcFontModifier::SetState(rptRcFontModifier::StateType MyState)
{
   m_State = MyState;
}

//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================

