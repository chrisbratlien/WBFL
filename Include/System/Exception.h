///////////////////////////////////////////////////////////////////////
// System - WBFL low level system services
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

#ifndef INCLUDED_SYSTEM_EXCEPTION_H_
#define INCLUDED_SYSTEM_EXCEPTION_H_
#pragma once

#include <string>
#include <System\SysExp.h>


// LOCAL INCLUDES
//

// FORWARD DECLARATIONS
//

// MISCELLANEOUS
//
#undef THROW
#undef THROW_EX
#if defined _DEBUG
// debug bug version breaks with an assert before throwing
#define THROW(ex,code)          {ASSERT(false); throw ex(ex::code, _T(__FILE__), __LINE__ );}
#define THROW_EX(ex,code,extra) {ASSERT(false); throw ex(ex::code,extra,_T(__FILE__),__LINE__);}
#else
#define THROW(ex,code)          {throw ex(ex::code, _T(__FILE__), __LINE__ );}
#define THROW_EX(ex,code,extra) {throw ex(ex::code,extra,_T(__FILE__),__LINE__);}
#endif // _DEBUG

/*****************************************************************************
CLASS 
   sysXBase

   Base class for all WBFL exceptions.


DESCRIPTION
   Base class for all WBFL exceptions.

LOG
   rab : 11.03.1997 : Created file
*****************************************************************************/

class SYSCLASS sysXBase
{
public:
   // GROUP: LIFECYCLE

   //------------------------------------------------------------------------
   // Default constructor.  Supply the file and line number where the 
   // exception occured.
   sysXBase(LPCTSTR file, Int32 line);

   //------------------------------------------------------------------------
   // Copy constructor
   sysXBase(const sysXBase& rOther);

   //------------------------------------------------------------------------
   // Destructor
   virtual ~sysXBase();

   // GROUP: OPERATORS

   // GROUP: OPERATIONS
   // GROUP: ACCESS

   //------------------------------------------------------------------------
   // Throws this exception object.  This throw differs from a standard C++
   // throw in that the object thrown is a clone based on the dynamic type
   // of the object.  The standard C++ throw throws a clone based on an
   // object's static type,  thereby slicing the object and losing specific
   // error information contained within the subclass.
   //
   // All classes derived from sysXBase must implement this method as follows:
   // void myClass::Throw() const { throw *static_cast<const myClass*>(this); }
   virtual void Throw() const = 0;

   //------------------------------------------------------------------------
   // Returns a reason code for the exception.  Concrete classes derived
   // from sysXBase must provide an implementation for this method that
   // returns an enum value as the actual enum type (Recall that enum's
   // can be safely converted to integer values, but not the other way
   // around).
   virtual Int32 GetReason() const = 0;

   //------------------------------------------------------------------------
   // Assigns an error message to pMsg.  The default implementation is to 
   // create a message in the following format:
   //
   // A <exception_type> error, number <reason>, has occured in
   // <filename> at line <line>.
   //
   // Where exception_type is the dynamic type of the exception,
   // reason is the reason code returned by GetReason(),
   // filename is the filename returned by GetFile(),  and
   // line is the line number returned by GetLine().
   virtual void GetErrorMessage(std::_tstring* pMsg) const;

   //------------------------------------------------------------------------
   // Returns the name of the file where the exception was originally thrown.
   // This method will not throw an exception.
   LPCTSTR GetFile() const throw();

   //------------------------------------------------------------------------
   // Returns the line number from where the exceptino was originally thrown.
   // This method will not throw an exception.
   Int32 GetLine() const throw();

   // GROUP: INQUIRY
   // GROUP: DEBUG

protected:
   // GROUP: DATA MEMBERS
   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   //------------------------------------------------------------------------
   // Assignment operator
   sysXBase& operator = (const sysXBase& rOther);

   // GROUP: OPERATIONS
   //------------------------------------------------------------------------
   void MakeCopy(const sysXBase& rOther);

   //------------------------------------------------------------------------
   void MakeAssignment(const sysXBase& rOther);

   // GROUP: ACCESS
   // GROUP: INQUIRY

private:
   // GROUP: DATA MEMBERS
   std::_tstring m_File;
   Int32       m_Line;

   // GROUP: LIFECYCLE
   // GROUP: OPERATORS
   // GROUP: OPERATIONS
   // GROUP: ACCESS
   // GROUP: INQUIRY
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif // INCLUDED_SYSTEM_EXCEPTION_H_
