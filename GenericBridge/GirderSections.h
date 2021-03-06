///////////////////////////////////////////////////////////////////////
// GenericBridge - Generic Bridge Modeling Framework
// Copyright � 1999-2020  Washington State Department of Transportation
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

// GirderSections.h 

#ifndef INCLUDED_GIRDERSECTIONS_H_
#define INCLUDED_GIRDERSECTIONS_H_

#include "resource.h"       // main symbols
#include "GirderSectionImpl.h"
#include <xutility>

class CFlangedBeam : 
   public CGirderSectionImpl<CFlangedBeam,&CLSID_FlangedGirderSection,
                             IFlangedGirderSection, &IID_IFlangedGirderSection,
                             IPrecastBeam,&CLSID_PrecastBeam>
{
public:
   DECLARE_REGISTRY_RESOURCEID(IDR_FLANGEDBEAM)
	   
   STDMETHODIMP get_MinWebThickness(Float64* tWeb) override
   {
      CHECK_RETVAL(tWeb);
      Float64 t1,t2;
      m_Beam->get_T1(&t1);
      m_Beam->get_T2(&t2);
      *tWeb = Min(t1,t2);
      return S_OK;
   }

   STDMETHODIMP get_EffectiveWebThickness(Float64* tWeb) override
   {
      return get_MinWebThickness(tWeb);
   }

   STDMETHODIMP get_MinBottomFlangeThickness(Float64* tf) override
   {
      return m_Beam->get_D4(tf); // IBeam
   }

   STDMETHODIMP get_TopFlangeThickness(CollectionIndexType idx,Float64* tFlange) override
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_D1(tFlange);
   }

   STDMETHODIMP get_BottomFlangeThickness(CollectionIndexType idx,Float64* tFlange) override
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_D4(tFlange);
   }

   // IPrestressedGirderSection
public:
   STDMETHODIMP RemoveSacrificalDepth(Float64 sacDepth) override
   {
      ATLASSERT(false); // should never get here... the top flange is not a riding surface
      return S_FALSE;
   }

   STDMETHODIMP get_SplittingZoneDimension(Float64* pSZD) override
   {
      return m_Beam->get_Height(pSZD);
   }

   STDMETHODIMP get_SplittingDirection(SplittingDirection* pSD) override
   {
      CHECK_RETVAL(pSD);
      *pSD = sdVertical;
      return S_OK;
   }
};

class CBulbTeeSection;
typedef CGirderSectionImpl<CBulbTeeSection, &CLSID_BulbTeeSection, IBulbTeeSection, &IID_IBulbTeeSection, IBulbTee2, &CLSID_BulbTee2> CBulbTeeSectionBase;
class CBulbTeeSection : 
   public CBulbTeeSectionBase,
   public IAsymmetricSection,
   public IFlangePoints
{
BEGIN_COM_MAP(CBulbTeeSection)
   COM_INTERFACE_ENTRY(IAsymmetricSection)
   COM_INTERFACE_ENTRY(IJointedSection)
   COM_INTERFACE_ENTRY(IFlangePoints)
   COM_INTERFACE_ENTRY_CHAIN(CBulbTeeSectionBase)
END_COM_MAP()

protected:
   CComPtr<IShape> m_LeftJoint, m_RightJoint;

public:
   DECLARE_REGISTRY_RESOURCEID(IDR_BULBTEE)

// IGirderSection
   STDMETHODIMP get_WorkPoint(IPoint2d** ppWorkPoint)
   {
      CComQIPtr<IXYPosition> position(m_Beam);
      CComPtr<IPoint2d> pntHookPoint; // hook point is at bottom center of shape (not bottom center of bounding box)
      position->get_LocatorPoint(lpHookPoint, &pntHookPoint);

      // compute the location of the top center point without rotation
      // this is just the hook point offset vertically by the height of the beam shape
      Float64 Hmin, H, Hmax;
      GetHeight(&Hmin, &H, &Hmax);

      CComPtr<IPoint2d> pntUnRotatedTopCenter;
      pntHookPoint->Clone(&pntUnRotatedTopCenter);
      pntUnRotatedTopCenter->Offset(0, H);

      // the unrotated top center is also the unrotated work point
      pntUnRotatedTopCenter->Clone(ppWorkPoint);

      // apply the rotation to the work point
      (*ppWorkPoint)->RotateEx(pntHookPoint, m_Rotation);

      return S_OK;
   }

// IAsymmetricSection
   STDMETHODIMP GetTopWidth(Float64* pLeft, Float64* pRight) override
   {
      CHECK_RETVAL(pLeft);
      CHECK_RETVAL(pRight);
      m_Beam->get_W5(pLeft);
      m_Beam->get_W6(pRight);
      return S_OK;
   }

   STDMETHODIMP GetHeight(Float64* pHmin, Float64* pHcl, Float64* pHmax) override
   {
      CHECK_RETVAL(pHmin);
      CHECK_RETVAL(pHcl);
      CHECK_RETVAL(pHmax);

      m_Beam->get_MinHeight(pHmin);
      m_Beam->get_CLHeight(pHcl);
      m_Beam->get_MaxHeight(pHmax);

      return S_OK;
   }

// IJointedSection
public:
   STDMETHODIMP SetJointShapes(IShape* pLeftJoint, IShape* pRightJoint) override
   {
      m_LeftJoint = pLeftJoint;
      m_RightJoint = pRightJoint;
      return S_OK;
   }

   STDMETHODIMP GetJointShapes(IShape** ppLeftJoint, IShape** ppRightJoint) override
   {
      CHECK_RETOBJ(ppLeftJoint);
      CHECK_RETOBJ(ppRightJoint);

      if (m_LeftJoint)
      {
         m_LeftJoint->Clone(ppLeftJoint);
      }

      if (m_RightJoint)
      {
         m_RightJoint->Clone(ppRightJoint);
      }

      return S_OK;
   }

// IFlangePoints
public:
   STDMETHODIMP GetTopFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppTopCentral, IPoint2d** ppRightTop, IPoint2d** ppRightBottom) override
   {
      return m_Beam->GetTopFlangePoints(ppLeftTop, ppLeftBottom, ppTopCentral, ppRightTop, ppRightBottom);
   }

   STDMETHODIMP GetBottomFlangePoints(IPoint2d** ppLeftTop, IPoint2d** ppLeftBottom, IPoint2d** ppRightTop, IPoint2d** ppRightBottom) override
   {
      return m_Beam->GetBottomFlangePoints(ppLeftTop, ppLeftBottom, ppRightTop, ppRightBottom);
   }

   STDMETHODIMP GetStressPoints(StressPointType spType, IPoint2dCollection** ppPoints) override
   {
      CHECK_RETOBJ(ppPoints);
      CComPtr<IPoint2dCollection> points;
      points.CoCreateInstance(CLSID_Point2dCollection);

      if (spType == spTop)
      {
         CComPtr<IPoint2d> leftTop, leftBottom, topCentral, rightTop, rightBottom;
         m_Beam->GetTopFlangePoints(&leftTop, &leftBottom, &topCentral, &rightTop, &rightBottom);
         points->Add(leftTop);
         points->Add(topCentral);
         points->Add(rightTop);
      }
      else
      {
         CComPtr<IPoint2d> leftTop, leftBottom, rightTop, rightBottom;
         m_Beam->GetBottomFlangePoints(&leftTop, &leftBottom, &rightTop, &rightBottom);

         //                |   |
         //         +------+   +-------+
         //         |                  |
         //         |   Bot Flange     |
         // leftTop |                  | rightTop
         //         \------------------/  <-------------- chamfer
         //       leftBottom          rightBottom
         //         |       Wbf        |
         //         |<---------------->|

         // we want to use the fictitious corner at the projection of the vertical face
         // of the bottom flange and the bottom of the bottom flange (engineers will typically
         // hand check stresses using (+/-Wbf/2,Yb) so the chamfers are ignored

         Float64 x, y, dummy;
         leftTop->Location(&x, &dummy); // left side at top of chamfer
         leftBottom->Location(&dummy, &y); // left side, at right edge of chamfer

         CComPtr<IPoint2d> pntLeft(leftTop);
         pntLeft->Move(x, y);
         points->Add(pntLeft);

         rightTop->Location(&x, &dummy); // right side at top of chamfer
         rightBottom->Location(&dummy, &y); // right side at left edge of chamfer

         CComPtr<IPoint2d> pntRight(rightTop);
         pntRight->Move(x, y);
         points->Add(pntRight);
      }

      return points.CopyTo(ppPoints);
   }

   STDMETHODIMP IgnoreBiaxialBending(BOOL* pIgnoreBiaxial) override
   {
      CHECK_RETVAL(pIgnoreBiaxial);
      *pIgnoreBiaxial = false;
      return S_OK;
   }


   STDMETHODIMP get_OverallHeight(Float64* height) override
   {
      return m_Beam->get_MaxHeight(height);
   }

   STDMETHODIMP get_NominalHeight(Float64* height) override
   {
      // for bulb-tee girders, use the CL Web height as the nomainl girder height
      return m_Beam->get_CLHeight(height);
   }

   STDMETHODIMP get_MinWebThickness(Float64* tWeb) override
   {
      CHECK_RETVAL(tWeb);
      Float64 t1,t2;
      m_Beam->get_T1(&t1);
      m_Beam->get_T2(&t2);
      *tWeb = Min(t1,t2);
      return S_OK;
   }

	STDMETHODIMP get_MatingSurfaceWidth(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* wMatingSurface) override
   {
      // total width is the width of our mating surface profile
      CComPtr<IPoint2dCollection> points;
      get_MatingSurfaceProfile(idx, bGirderOnly, &points);

      IndexType npts;
      points->get_Count(&npts);
      CComPtr<IPoint2d> ps, pe;
      points->get_Item(0, &ps);
      points->get_Item(npts-1, &pe);

      Float64 xs, xe;
      ps->get_X(&xs);
      pe->get_X(&xe);

      *wMatingSurface = xe - xs;

      return S_OK;
   }

   STDMETHODIMP get_MatingSurfaceLocation(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly,Float64* pLocation) override
   {
      // total width is the width of our mating surface profile. Profile can be offset from center on exterior beams
      CComPtr<IPoint2dCollection> points;
      get_MatingSurfaceProfile(idx, bGirderOnly, &points);

      IndexType npts;
      points->get_Count(&npts);
      CComPtr<IPoint2d> ps, pe;
      points->get_Item(0, &ps);
      points->get_Item(npts-1, &pe);

      Float64 xs, xe;
      ps->get_X(&xs);
      pe->get_X(&xe);

      Float64 msglocation = (xs + xe) / 2.0; // in bridge coords

      CComPtr<IPoint2d> topCenter;
      get_LocatorPoint(lpTopCenter, &topCenter);
      Float64 tcloc;
      topCenter->get_X(&tcloc);

      Float64 location = msglocation - tcloc;

      *pLocation = location;


      return S_OK;
   }

   STDMETHODIMP get_MatingSurfaceProfile(MatingSurfaceIndexType idx, VARIANT_BOOL bGirderOnly, IPoint2dCollection** ppProfile) override
   {
      // overide the base class implentation with this
      CHECK_RETOBJ(ppProfile);

      CComPtr<IPoint2d> leftTop, leftBottom, topCentral, rightTop, rightBottom;
      m_Beam->GetTopFlangePoints(&leftTop, &leftBottom, &topCentral, &rightTop, &rightBottom);

      if (bGirderOnly == VARIANT_FALSE)
      {
         if (m_LeftJoint)
         {
            leftTop.Release();
            CComQIPtr<IPolyShape> shape(m_LeftJoint);
            shape->get_Point(0, &leftTop);
         }

         if (m_RightJoint)
         {
            rightTop.Release();
            CComQIPtr<IPolyShape> shape(m_RightJoint);
            shape->get_Point(3, &rightTop);
         }
      }

      CComPtr<IPoint2dCollection> points;
      points.CoCreateInstance(CLSID_Point2dCollection);

      points->Add(leftTop);
      points->Add(topCentral);
      points->Add(rightTop);

      return points.CopyTo(ppProfile);
   }

   STDMETHODIMP get_EffectiveWebThickness(Float64* tWeb) override
   {
      return get_MinWebThickness(tWeb);
   }

   STDMETHODIMP get_MinBottomFlangeThickness(Float64* tf) override
   {
      return m_Beam->get_D4(tf); // IBeam
   }

   STDMETHODIMP get_TopFlangeThickness(CollectionIndexType idx,Float64* tFlange) override
   {
      if (idx != 0)
      {
         return E_INVALIDARG;
      }

      return m_Beam->get_D1(tFlange);
   }

   STDMETHODIMP get_BottomFlangeThickness(CollectionIndexType idx,Float64* tFlange) override
   {
      if (idx != 0)
      {
         return E_INVALIDARG;
      }

      return m_Beam->get_D5(tFlange);
   }


   STDMETHODIMP get_TopFlangeLocation(FlangeIndexType idx, Float64* location) override
   {
      if (idx != 0)
      {
         return E_INVALIDARG;
      }

      // location < 0 means the CL of the flange is to the left of the CL of the beam bounding box
      Float64 w5, w6;
      m_Beam->get_W5(&w5);
      m_Beam->get_W6(&w6);
      *location = 0.5*(w5 - w6);

      return S_OK;
   }

   STDMETHODIMP get_BottomFlangeLocation(FlangeIndexType idx, Float64* location) override
   {
      return get_TopFlangeLocation(idx, location);
   }

   // IPrestressedGirderSection
public:
   STDMETHODIMP RemoveSacrificalDepth(Float64 sacDepth) override
   {
      Float64 D1;
      m_Beam->get_D1(&D1);
      ATLASSERT(sacDepth < D1);
      D1 -= sacDepth;
      m_Beam->put_D1(D1);

      if (m_LeftJoint)
      {
         CComPtr<IPoint2dCollection> points;
         m_LeftJoint->get_PolyPoints(&points);
         CComPtr<IPoint2d> pntTopLeft, pntTopRight;
         points->get_Item(0, &pntTopLeft);
         points->get_Item(3, &pntTopRight);
         pntTopLeft->Offset(0, -sacDepth);
         pntTopRight->Offset(0, -sacDepth);
      }

      if (m_RightJoint)
      {
         CComPtr<IPoint2dCollection> points;
         m_RightJoint->get_PolyPoints(&points);
         CComPtr<IPoint2d> pntTopLeft, pntTopRight;
         points->get_Item(0, &pntTopLeft);
         points->get_Item(3, &pntTopRight);
         pntTopLeft->Offset(0, -sacDepth);
         pntTopRight->Offset(0, -sacDepth);
      }

      return S_OK;
   }

   STDMETHODIMP get_SplittingZoneDimension(Float64* pSZD) override
   {
      return m_Beam->get_CLHeight(pSZD);
   }

   STDMETHODIMP get_SplittingDirection(SplittingDirection* pSD) override
   {
      CHECK_RETVAL(pSD);
      *pSD = sdVertical;
      return S_OK;
   }
};

class CNUGirderSection : 
   public CGirderSectionImpl<CNUGirderSection,&CLSID_NUGirderSection,
                             INUGirderSection,&IID_INUGirderSection,
                             INUBeam,&CLSID_NUBeam>
{
public:
   DECLARE_REGISTRY_RESOURCEID(IDR_NUGIRDERSECTION)
	   
   STDMETHODIMP get_MinWebThickness(Float64* tWeb) override
   {
      return m_Beam->get_T(tWeb);
   }
	   
   STDMETHODIMP get_EffectiveWebThickness(Float64* tWeb) override
   {
      return get_MinWebThickness(tWeb);
   }

   STDMETHODIMP get_MinBottomFlangeThickness(Float64* tf) override
   {
      return m_Beam->get_D5(tf); // NUBeam
   } 

   STDMETHODIMP get_TopFlangeThickness(CollectionIndexType idx,Float64* tFlange) override
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_D1(tFlange);
   }

   STDMETHODIMP get_BottomFlangeThickness(CollectionIndexType idx,Float64* tFlange) override
   {
      if ( idx != 0 )
         return E_INVALIDARG;

      return m_Beam->get_D5(tFlange);
   }


// IPrestressedGirderSection
public:
   STDMETHODIMP RemoveSacrificalDepth(Float64 sacDepth) override
   {
      ATLASSERT(false); // should never get here... the top flange is not a riding surface
      return S_FALSE;
   }

   STDMETHODIMP get_SplittingZoneDimension(Float64* pSZD) override
   {
      return m_Beam->get_Height(pSZD);
   }

   STDMETHODIMP get_SplittingDirection(SplittingDirection* pSD) override
   {
      CHECK_RETVAL(pSD);
      *pSD = sdVertical;
      return S_OK;
   }
};

#endif //  INCLUDED_GIRDERSECTIONS_H_