///////////////////////////////////////////////////////////////////////
// Material - Analytical and Product modeling of civil engineering materials
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

#include <Lrfd\LrfdLib.h>
#include <Lrfd\LRFDConcrete.h>
#include <Lrfd\VersionMgr.h>
#include <Units\SysUnits.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

lrfdLRFDConcrete::lrfdLRFDConcrete(LPCTSTR name) :
matConcreteBase(name),
m_StartTime(0),
m_StepTime(0),
m_EcK1(1.0),
m_EcK2(1.0),
m_CreepK1(1.0),
m_CreepK2(1.0),
m_ShrinkageK1(1.0),
m_ShrinkageK2(1.0)
{
}

lrfdLRFDConcrete::lrfdLRFDConcrete(const lrfdLRFDConcrete& rOther) :
matConcreteBase(rOther),
m_StartTime(rOther.m_StartTime),
m_StepTime(rOther.m_StepTime),
m_EcK1(rOther.m_EcK1),
m_EcK2(rOther.m_EcK2),
m_CreepK1(rOther.m_CreepK1),
m_CreepK2(rOther.m_CreepK2),
m_ShrinkageK1(rOther.m_ShrinkageK1),
m_ShrinkageK2(rOther.m_ShrinkageK2),
m_InitialConcrete(rOther.m_InitialConcrete),
m_FinalConcrete(rOther.m_FinalConcrete)
{
}

lrfdLRFDConcrete::~lrfdLRFDConcrete()
{
}

void lrfdLRFDConcrete::SetConcreteModels(const matConcreteEx& initial,const matConcreteEx& final)
{
   m_InitialConcrete = initial;
   m_FinalConcrete   = final;

   SetType((matConcreteBase::Type)m_FinalConcrete.GetType());
   SetStrengthDensity(m_FinalConcrete.GetDensity());
   SetWeightDensity(m_FinalConcrete.GetDensityForWeight());
   HasAggSplittingStrength(m_FinalConcrete.HasAggSplittingStrength());
   SetAggSplittingStrength(m_FinalConcrete.GetAggSplittingStrength());
   SetMaxAggregateSize(m_FinalConcrete.GetMaxAggregateSize());
}

const matConcreteEx& lrfdLRFDConcrete::GetInitialConcreteModel() const
{
   return m_InitialConcrete;
}

const matConcreteEx& lrfdLRFDConcrete::GetFinalConcreteModel() const
{
   return m_FinalConcrete;
}

void lrfdLRFDConcrete::SetEcCorrectionFactors(Float64 K1,Float64 K2)
{
   m_EcK1 = K1;
   m_EcK2 = K2;
}

void lrfdLRFDConcrete::GetEcCorrectionFactors(Float64* pK1,Float64* pK2) const
{
   *pK1 = m_EcK1;
   *pK2 = m_EcK2;
}

void lrfdLRFDConcrete::SetCreepCorrectionFactors(Float64 K1,Float64 K2)
{
   m_CreepK1 = K1;
   m_CreepK2 = K2;
}

void lrfdLRFDConcrete::GetCreepCorrectionFactors(Float64* pK1,Float64* pK2) const
{
   *pK1 = m_CreepK1;
   *pK2 = m_CreepK2;
}

void lrfdLRFDConcrete::SetShrinkageCorrectionFactors(Float64 K1,Float64 K2)
{
   m_ShrinkageK1 = K1;
   m_ShrinkageK2 = K2;
}

void lrfdLRFDConcrete::GetShrinkageCorrectionFactors(Float64* pK1,Float64* pK2) const
{
   *pK1 = m_ShrinkageK1;
   *pK2 = m_ShrinkageK2;
}

void lrfdLRFDConcrete::SetStartTime(Float64 t)
{
   m_StartTime = t;
}

Float64 lrfdLRFDConcrete::GetStartTime() const
{
   return m_StartTime;
}

void lrfdLRFDConcrete::SetStepTime(Float64 t)
{
   m_StepTime = t;
}

Float64 lrfdLRFDConcrete::GetStepTime() const
{
   return m_StepTime;
}

Float64 lrfdLRFDConcrete::GetFc(Float64 t) const
{
   if ( t < m_StartTime )
   {
      return 0;
   }

   if ( t < m_StepTime )
   {
      return m_InitialConcrete.GetFc();
   }
   else
   {
      return m_FinalConcrete.GetFc();
   }
}

Float64 lrfdLRFDConcrete::GetEc(Float64 t) const
{
   if ( t < m_StartTime )
   {
      return 0;
   }

   Float64 Ec;
   if ( t < m_StepTime )
   {
      Ec = m_InitialConcrete.GetE();
   }
   else
   {
      Ec = m_FinalConcrete.GetE();
   }

   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims )
   {
      Ec *= m_EcK1*m_EcK2;
   }

   return Ec;
}

Float64 lrfdLRFDConcrete::GetShearFr(Float64 t) const
{
   if ( t < m_StartTime )
   {
      return 0;
   }

   if ( t < m_StepTime )
   {
      return m_InitialConcrete.GetShearFr();
   }
   else
   {
      return m_FinalConcrete.GetShearFr();
   }
}

Float64 lrfdLRFDConcrete::GetFlexureFr(Float64 t) const
{
   if ( t < m_StartTime )
   {
      return 0;
   }

   if ( t < m_StepTime )
   {
      return m_InitialConcrete.GetFlexureFr();
   }
   else
   {
      return m_FinalConcrete.GetFlexureFr();
   }
}

Float64 lrfdLRFDConcrete::GetFreeShrinkageStrain(Float64 t) const
{
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims )
   {
      return GetFreeShrinkageStrainBefore2005(t);
   }
   else
   {
      return GetFreeShrinkageStrain2005(t);
   }
}

Float64 lrfdLRFDConcrete::GetCreepCoefficient(Float64 t,Float64 tla) const
{
   if ( lrfdVersionMgr::GetVersion() < lrfdVersionMgr::ThirdEditionWith2005Interims )
   {
      return GetCreepCoefficientBefore2005(t,tla);
   }
   else
   {
      return GetCreepCoefficient2005(t,tla);
   }
}

matConcreteBase* lrfdLRFDConcrete::CreateClone() const
{
   return new lrfdLRFDConcrete(*this);
}

Float64 lrfdLRFDConcrete::GetFreeShrinkageStrainBefore2005(Float64 t) const
{
   // age of the concrete at time t (duration of time after casting)
   Float64 concrete_age = GetAge(t);
   if ( concrete_age < 0 )
   {
      return 0;
   }

   // duration of time after initial curing (time since curing stopped, this is when shrinkage begins)
   Float64 shrinkage_time = concrete_age - m_CureTime; // same as drying time
   if ( shrinkage_time < 0 )
   {
      // if this occurs, t is in the curing period so no shrinkage occurs
      return 0;
   }

   Float64 ks = 1.0;
   if ( lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI )
   {
      Float64 vs = ::ConvertFromSysUnits(m_VS,unitMeasure::Millimeter);
      Float64 k1 = shrinkage_time/(26.0*exp(0.36*vs) + shrinkage_time);
      Float64 k2 = shrinkage_time/(45.0 + shrinkage_time);
      Float64 k3 = (1064 - 94*vs)/923;
      ks = (k1/k2)*k3;
   }
   else
   {
      Float64 vs = ::ConvertFromSysUnits(m_VS,unitMeasure::Inch);
      Float64 k1 = shrinkage_time/(26.0*exp(0.0142*vs) + shrinkage_time);
      Float64 k2 = shrinkage_time/(45.0 + shrinkage_time);
      Float64 k3 = (1064 - 3.7*vs)/923;
      ks = (k1/k2)*k3;
   }

   Float64 kh = 1.0;
   if ( m_RelativeHumidity < 80.0 )
   {
      kh = (140. - m_RelativeHumidity)/70.;
   }
   else
   {
      kh = 3*(100.0 - m_RelativeHumidity)/70.;
   }
   if ( kh < 0 )
   {
      kh = 0;
   }

   Float64 K = (GetCureMethod() == matConcreteBase::Moist ? 35.0 : 55.0);
   Float64 eshu = (GetCureMethod() == matConcreteBase::Moist ? 0.51e-3 : 0.56e-3);
   Float64 esh = -ks*kh*eshu*(shrinkage_time)/(K + shrinkage_time);
   return esh;
}

Float64 lrfdLRFDConcrete::GetFreeShrinkageStrain2005(Float64 t) const
{
   // age of the concrete at time t (duration of time after casting)
   Float64 concrete_age = GetAge(t);
   if ( concrete_age < 0 )
   {
      return 0;
   }

   // duration of time after initial curing (time since curing stopped, this is when shrinkage begins)
   Float64 shrinkage_time = concrete_age - m_CureTime;
   if ( shrinkage_time < 0 )
   {
      // if this occurs, t is in the curing period so no shrinkage occurs
      return 0;
   }

   Float64 vs = ::ConvertFromSysUnits(m_VS,unitMeasure::Inch);
   Float64 ks = Max(1.0,1.45 - 0.13*vs);

   Float64 khs = (2.0 - 0.014*m_RelativeHumidity);
   
   Float64 fc = ::ConvertFromSysUnits(m_InitialConcrete.GetFc(),unitMeasure::KSI);
   Float64 kf = 5.0/(1.0 + fc);

   Float64 ktd = (shrinkage_time)/(61.0 - 4.0*fc + shrinkage_time);

   Float64 esh = -m_ShrinkageK1*m_ShrinkageK2*ks*khs*kf*ktd*0.48E-3;
   return esh;
}

Float64 lrfdLRFDConcrete::GetCreepCoefficientBefore2005(Float64 t,Float64 tla) const
{
   // age of the concrete at time t (duration of time after casting)
   Float64 concrete_age = GetAge(t);
   if ( concrete_age <= 0 )
   {
      return 0;
   }

   // age of concrete at time when the load is applied
   Float64 age_at_loading = GetAge(tla);
   if ( age_at_loading <= 0 )
   {
      return 0;
   }

   bool bSI = lrfdVersionMgr::GetUnits() == lrfdVersionMgr::SI;
   
   // Check volume to surface ratio
   Float64 vs, fc;
   if ( bSI )
   {
      vs = ::ConvertFromSysUnits( m_VS, unitMeasure::Millimeter );
      fc = ::ConvertFromSysUnits( m_FinalConcrete.GetFc(), unitMeasure::MPa);
   }
   else
   {
      vs = ::ConvertFromSysUnits( m_VS, unitMeasure::Inch );
      fc = ::ConvertFromSysUnits( m_FinalConcrete.GetFc(), unitMeasure::KSI);
   }


   // Compute Kf
   Float64 kf;
   if ( bSI )
   {
      kf = 62.0 / ( 42.0 + fc );
   }
   else
   {
      kf = 1.0 / ( 0.67 + (fc/9.0) );
   }

   // Compute Kc
   Float64 a,b,c;
   Float64 x1, x2;
   Float64 e = pow(10.,1./log(10.));
   if ( bSI )
   {
      x1 = 0.0142;
      x2 = -0.0213;
   }
   else
   {
      x1 = 0.36;
      x2 = -0.54;
   }

   a = concrete_age/(26.0*pow(e,x1*vs)+concrete_age);
   b = concrete_age/(45.0 + concrete_age);
   c = 1.80 + 1.77*pow(e,x2*vs);

   Float64 kc = (a/b)*(c/2.587);

   Float64 Y = 3.5*kc*kf*(1.58 - m_RelativeHumidity/120.)*pow(age_at_loading,-0.118) * (  pow(concrete_age - age_at_loading,0.6)/(10.0 + pow(concrete_age - age_at_loading,0.6) ) );
   return Y;
}

Float64 lrfdLRFDConcrete::GetCreepCoefficient2005(Float64 t,Float64 tla) const
{
   // age of the concrete at time t (duration of time after casting)
   Float64 concrete_age = GetAge(t);
   if ( concrete_age <= 0 )
   {
      return 0;
   }

   // age of concrete at time when the load is applied
   Float64 age_at_loading = GetAge(tla);
   if ( age_at_loading <= 0 )
   {
      return 0;
   }

   // maturity of concrete = age of concrete between time of loading and time being considered
   Float64 maturity = concrete_age - age_at_loading;
   ATLASSERT( 0 <= maturity );
   if ( maturity < 0 )
   {
      return 0;
   }

   Float64 vs = ::ConvertFromSysUnits(m_VS,unitMeasure::Inch);
   Float64 ks = Max(1.0,1.45 - 0.13*vs);

   Float64 khc = (1.56 - 0.008*m_RelativeHumidity);
   
   Float64 fc = ::ConvertFromSysUnits(m_InitialConcrete.GetFc(),unitMeasure::KSI);
   Float64 kf = 5.0/(1.0 + fc);

   Float64 ktd = (maturity)/(61.0 - 4.0*fc + maturity);

   Float64 ti = age_at_loading;
   Float64 Y = 1.9*m_CreepK1*m_CreepK2*ks*khc*kf*ktd*pow(ti,-0.118);
   return Y;
}