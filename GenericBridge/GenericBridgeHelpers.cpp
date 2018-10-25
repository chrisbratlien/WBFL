///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright � 1999-2011  Washington State Department of Transportation
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

#include "StdAfx.h"
#include "GenericBridgeHelpers.h"
#include <MathEx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const long g_AlignmentKey = 0;
const long g_CLBridgeKey  = 1;

HRESULT GB_GetPierGirderPointId(PierIndexType pierIdx,GirderIndexType gdrIdx,PositionType posType,long* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = -1*( (pierIdx+1)*PIER_ID_OFFSET 
               +(gdrIdx+1)*GIRDER_ID_OFFSET
               +(1)*LOCATION_OFFSET
               +(posType)*SIDE_OFFSET
               );

   return S_OK;
}

HRESULT GB_GetBearingGirderPointId(PierIndexType pierIdx,GirderIndexType gdrIdx,PositionType posType,long* pVal)
{
   CHECK_RETVAL(pVal);

   *pVal = -1*( (pierIdx+1)*PIER_ID_OFFSET 
               +(gdrIdx+1)*GIRDER_ID_OFFSET
               +(0)*LOCATION_OFFSET
               +(posType)*SIDE_OFFSET
               );

   return S_OK;
}

HRESULT GB_GetPierAlignmentPointId(PierIndexType pierIdx,long* pVal)
{
   CHECK_RETVAL(pVal);

   (*pVal) = -1*(pierIdx+1)*PIER_ID_OFFSET;

   return S_OK;
}

HRESULT GB_GetPierCLBridgePointId(PierIndexType pierIdx,long* pVal)
{
   CHECK_RETVAL(pVal);

   (*pVal) = -1*(pierIdx+1)*BRIDGE_ID_OFFSET;

   return S_OK;
}

HRESULT GB_GetGirderLineId(SpanIndexType spanIdx,GirderIndexType gdrIdx,long* pVal)
{
   *pVal = -1*( (spanIdx+1)*PIER_ID_OFFSET 
               +(gdrIdx+1)*GIRDER_ID_OFFSET
              );

   return S_OK;
}

// function to deal with fractional and absolute values
Float64 GB_GetFracDistance(Float64 fracLoc, Float64 Length, bool ignoreTooBig)
{
   ATLASSERT(Length>0.0);

   if (fracLoc>=0.0)
   {
      if (ignoreTooBig || IsLE(fracLoc,Length) )
      {
         return fracLoc;
      }
      else
      {
         throw frTooBig;
      }
   }
   else
   {
      if (fracLoc>=-1.0)
      {
         return -fracLoc*Length;
      }
      else
         throw frTooSmall;
   }

   ATLASSERT(0); //can't get here
   return 0.0;
}
