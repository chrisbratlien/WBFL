///////////////////////////////////////////////////////////////////////
// Math - Utility library of mathematical services
// Copyright (C) 1999  Washington State Department of Transportation
//                     Bridge and Structures Office
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

#include <Math\MathLib.h>
#include <Math\LinFunc2d.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************************************************
CLASS
   mathLinFunc2d
****************************************************************************/

////////////////////////// PUBLIC     ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
mathLinFunc2d::mathLinFunc2d() :
mathFunction2d()
{
   m_Slope = 0;
   m_Yintercept = 0;
}

mathLinFunc2d::mathLinFunc2d(Float64 slope,Float64 yIntercept) :
mathFunction2d()
{
   m_Slope = slope;
   m_Yintercept = yIntercept;
}

mathLinFunc2d::mathLinFunc2d(const mathLinFunc2d& rOther) :
mathFunction2d()
{
   MakeCopy(rOther);
}

mathLinFunc2d::~mathLinFunc2d()
{
}

//======================== OPERATORS  =======================================
mathLinFunc2d& mathLinFunc2d::operator= (const mathLinFunc2d& rOther)
{
   if( this != &rOther )
   {
      MakeAssignment(rOther);
   }

   return *this;
}

//======================== OPERATIONS =======================================
Float64 mathLinFunc2d::Evaluate(Float64 x) const
{
   return m_Slope * x + m_Yintercept;
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================
//======================== DEBUG      =======================================
#if defined _DEBUG
bool mathLinFunc2d::AssertValid() const
{
   return mathFunction2d::AssertValid();
}

void mathLinFunc2d::Dump(dbgDumpContext& os) const
{
   mathFunction2d::Dump( os );
}
#endif // _DEBUG

////////////////////////// PROTECTED  ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
void mathLinFunc2d::MakeCopy(const mathLinFunc2d& rOther)
{
   m_Slope      = rOther.m_Slope;
   m_Yintercept = rOther.m_Yintercept;
}

void mathLinFunc2d::MakeAssignment(const mathLinFunc2d& rOther)
{
   //mathFunction2d::MakeAssignment( rOther );
   MakeCopy( rOther );
}

//======================== ACCESS     =======================================
//======================== INQUIRY    =======================================

////////////////////////// PRIVATE    ///////////////////////////////////////

//======================== LIFECYCLE  =======================================
//======================== OPERATORS  =======================================
//======================== OPERATIONS =======================================
//======================== ACCESS     =======================================
//======================== INQUERY    =======================================


