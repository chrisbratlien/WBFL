///////////////////////////////////////////////////////////////////////
// Stability
// Copyright � 1999-2016  Washington State Department of Transportation
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

#include <Stability\StabilityExp.h>
#include <Stability\Results.h>

/*****************************************************************************
CLASS 
   stbLiftingSectionResults

DESCRIPTION
   Encapsulates the lifting analysis results at a section


COPYRIGHT
   Copyright � 1997-2016
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class STABILITYCLASS stbLiftingSectionResult
{
public:
   stbLiftingSectionResult();

   Float64 X;   // location of section
   Float64 Mg;  // moment due to girder weight
   Float64 Mw;  // transverse moment due to wind

   Float64 fps[2]; // top/bottom stress due to prestressing
   Float64 fcable[2]; // top/bottom stress due to inclined lift cable without impact
   Float64 fg[2]; // top/bottom stress due to girder weight without impact
   Float64 fw[4]; // corner stresses due to wind towards the left

   // Array indicies are [IMPACT_xxx][wind direction LEFT/RIGHT][corner TOP_LEFT,TOP_RIGHT,BOTTOM_LEFT,BOTTOM_RIGHT]
   Float64 fDirect[3][2][4]; // stress due to direct loads (girder self weight, wind, CF, and ps)
   Float64 fTilt[3][2][4];   // stress due to equilibrium rotation of girder caused by girder self weight
   Float64 f[3][2][4];       // stress at a corner (fDirect + fTilt)
   Float64 fMin[2][3][2];    // min stress [face][impact][wind]
   Float64 fMax[2][3][2];    // max stress [face][impact][wind]
   Float64 Mcr[3][2][4];        // cracking moment
   Float64 ThetaCrack[3][2][4]; // rotation angle causing cracking
   IndexType CrackedFlange[3][2]; // indicates the flange and corner that is cracked (TOP_LEFT, etc)
   Float64 FScr[3][2]; // factor of safety against cracking

   // parameters related to laterial moment due to axial force of inclined cables
   Float64 OffsetFactor; // cg offset factor at this section
   Float64 eh[3][2]; // eccentricity of axial force of inclined cables from roll axis at this location
   Float64 Mh[3][2]; // lateral moment due to axial force of inclined cables

   bool bSectionHasRebar[2]; // true if there is sufficient bonded reinforcement at this section to use the higher allowable tension limit (array index is TOP/BOTTOM)
};

/*****************************************************************************
CLASS 
   stbLiftingResults

DESCRIPTION
   Encapsulates the analysis results for lifting stability analysis


COPYRIGHT
   Copyright � 1997-2016
   Washington State Department Of Transportation
   All Rights Reserved
*****************************************************************************/

class STABILITYCLASS stbLiftingResults : public stbResults
{
public:
   stbLiftingResults();

   bool bIsStable[3]; // if false, the girder is not stable for lifting... it will just roll over. 
                      // if the girder is not stable, the analysis results below are not valid

   Float64 Pcrit; // critical compression load
   Float64 Plift; // axial force due to inclination of lift cables for the no-impact case
   Float64 dLift; // deflection due to lifting cable force for the no-impact case
   Float64 emag[3];  // lateral deflection magnification factor (array index in one of the IMPACT_xxx constants)

   Float64 ThetaEq[3][2];    // tilt angle at equilibrium

   std::vector<stbLiftingSectionResult> vSectionResults; // analysis results for each analysis point in the stability problem object

   Float64 MaxStress;                     // maximum stress (most tensile value)
   IndexType MaxStressAnalysisPointIndex; // analysis poiint index associated with the maximum girder stress
   IndexType MaxStressImpactDirection;    // impact direction associated with the maximum girder stress
   IndexType MaxStressWindDirection;      // wind direction associated with the maximum girder stress
   IndexType MaxStressCorner;             // corner where the maximum girder stress occurs

   Float64 MinStress;                     // minimum stress (most compressive value)
   IndexType MinStressAnalysisPointIndex; // analysis poiint index associated with the minimum girder stress
   IndexType MinStressImpactDirection;    // impact direction associated with the minimum girder stress
   IndexType MinStressWindDirection;      // wind direction associated with the minimum girder stress
   IndexType MinStressCorner;             // corner where the minimum girder stress occurs

   Float64 MinFScr;                  // minimum factor of safety against cracking
   IndexType FScrAnalysisPointIndex; // analysis point index associated with the minimum factor of safety against cracking
   IndexType FScrImpactDirection;    // impact direction associated with the minimum factor of safety against cracking
   IndexType FScrWindDirection;      // wind direction associated with the minimum factor of safety against cracking
   IndexType FScrCorner;             // corner associated with the minimum factor of safety against cracking

   // Array indicies [IMPACT_xxx][wind direction, LEFT/RIGHT]
   Float64 ThetaMax[3][2];     // maximum tilt angle of the cracked section
   Float64 FsFailure[3][2];    // factor of safety against failure computed using direct equation
   Float64 AdjFsFailure[3][2]; // adjusted FS against failure (if FSfailure < FScr then FSfailure = FScr)

   Float64 MinFsFailure;         // minimum factor of safety against failure
   Float64 MinAdjFsFailure;      // corrosponding adjusted minimum factor of safety against failure
   IndexType FSfImpactDirection; // impact direction associated with the minimum factor of safety against cracking
   IndexType FSfWindDirection;   // wind direction associated with the minimum factor of safety against cracking
};