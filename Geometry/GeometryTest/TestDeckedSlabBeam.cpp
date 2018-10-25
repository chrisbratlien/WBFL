///////////////////////////////////////////////////////////////////////
// Geometry - Geometric Modeling Library
// Copyright � 1999-2010  Washington State Department of Transportation
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

// TestDeckedSlabBeam.cpp: implementation of the CTestDeckedSlabBeam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestDeckedSlabBeam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestDeckedSlabBeam::CTestDeckedSlabBeam()
{

}

CTestDeckedSlabBeam::~CTestDeckedSlabBeam()
{

}

void CTestDeckedSlabBeam::Test()
{
   TestIDeckedSlabBeam();
   TestIShape();
   TestIXYPosition();
   TestISupportErrorInfo();
}

void CTestDeckedSlabBeam::TestIDeckedSlabBeam()
{
   CComPtr<IDeckedSlabBeam> beam;
   TRY_TEST( beam.CoCreateInstance(CLSID_DeckedSlabBeam), S_OK );  

   // Verify initialization. All dimensions should be zero.
   // Hook point (bottom center) should be zero.
   Float64 val;
   CComPtr<IPoint2d> pntVal;

   TRY_TEST( beam->get_A(NULL), E_POINTER );
   TRY_TEST( beam->get_A(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_B(NULL), E_POINTER );
   TRY_TEST( beam->get_B(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_C(NULL), E_POINTER );
   TRY_TEST( beam->get_C(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_W(NULL), E_POINTER );
   TRY_TEST( beam->get_W(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_Tt(NULL), E_POINTER );
   TRY_TEST( beam->get_Tt(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_Tb(NULL), E_POINTER );
   TRY_TEST( beam->get_Tb(&val), S_OK );
   TRY_TEST( IsZero(val), true );

   TRY_TEST( beam->get_HookPoint(NULL), E_POINTER );
   TRY_TEST( beam->get_HookPoint(&pntVal), S_OK );
   pntVal->get_X(&val);
   TRY_TEST( IsZero(val), true );
   pntVal->get_Y(&val);
   TRY_TEST( IsZero(val), true );

   // Test properties
   TRY_TEST( beam->put_A(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_A(48.0), S_OK );
   beam->get_A(&val);
   TRY_TEST( IsEqual(val,48.0), true );

   TRY_TEST( beam->put_B(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_B(15.0), S_OK );
   beam->get_B(&val);
   TRY_TEST( IsEqual(val,15.0), true );

   TRY_TEST( beam->put_C(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_C(12.0), S_OK );
   beam->get_C(&val);
   TRY_TEST( IsEqual(val,12.0), true );

   TRY_TEST( beam->put_W(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_W(6.0), S_OK );
   beam->get_W(&val);
   TRY_TEST( IsEqual(val,6.0), true );

   TRY_TEST( beam->put_Tt(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_Tt(8.0), S_OK );
   beam->get_Tt(&val);
   TRY_TEST( IsEqual(val,8.0), true );

   TRY_TEST( beam->put_Tb(-1), GEOMETRY_E_DIMENSION );
   TRY_TEST( beam->put_Tb(7.0), S_OK );
   beam->get_Tb(&val);
   TRY_TEST( IsEqual(val,7.0), true );

   // Test Interface Pointers
   CComPtr<IShape> shape;
   TRY_TEST(beam->get_Shape(NULL), E_POINTER );
   TRY_TEST(beam->get_Shape(&shape), S_OK );
   TRY_TEST(shape != NULL,true );

   CComPtr<IXYPosition> position;
   TRY_TEST(beam->get_XYPosition(NULL), E_POINTER );
   TRY_TEST(beam->get_XYPosition(&position), S_OK );
   TRY_TEST(position != NULL,true );

   CComPtr<IUnknown> punk1;
   CComPtr<IUnknown> punk2;
   CComPtr<IUnknown> punk3;
   beam->QueryInterface(&punk1);
   shape->QueryInterface(&punk2);
   position->QueryInterface(&punk3);
   TRY_TEST( punk1 == punk2, true );
   TRY_TEST( punk1 == punk3, true );
   TRY_TEST( punk2 == punk3, true );
}

void CTestDeckedSlabBeam::TestIShape()
{
   CComPtr<IShape> shape;
   TRY_TEST( shape.CoCreateInstance( CLSID_DeckedSlabBeam ), S_OK );
   CComQIPtr<IDeckedSlabBeam> beam(shape);
   
   // 6DS20
   Float64 A = 77.75;
   TRY_TEST( beam->put_A(A), S_OK );
   TRY_TEST( beam->put_B(9.0), S_OK );
   TRY_TEST( beam->put_C(12.0), S_OK );
   TRY_TEST( beam->put_W(6.0), S_OK );
   TRY_TEST( beam->put_Tt(8.0), S_OK );
   TRY_TEST( beam->put_Tb(7.0), S_OK );
   TRY_TEST( beam->put_F(1.75), S_OK );
   TRY_TEST( beam->put_LeftBlockOut(VARIANT_TRUE), S_OK );
   TRY_TEST( beam->put_RightBlockOut(VARIANT_TRUE), S_OK );

   //
   // Bounding Box
   //
   Float64 val;
   CComPtr<IRect2d> box;
   TRY_TEST( shape->get_BoundingBox(NULL), E_POINTER );
   TRY_TEST( shape->get_BoundingBox(&box), S_OK );
   
   box->get_Left(&val);
   TRY_TEST( IsEqual(val,-A/2.0), true );
   
   box->get_Right(&val);
   TRY_TEST( IsEqual(val, A/2.0), true );

   box->get_Top(&val);
   TRY_TEST( IsEqual(val, 20.0), true );

   box->get_Bottom(&val);
   TRY_TEST( IsEqual(val,  0.0), true );

   //
   // ShapeProperties
   //
   CComPtr<IShapeProperties> props;
   TRY_TEST( shape->get_ShapeProperties(NULL), E_POINTER );
   TRY_TEST( shape->get_ShapeProperties(&props), S_OK );
   Float64 area, ixx, iyy, ixy, cgx, cgy;
   CComPtr<IPoint2d> cg;

   Float64 d_area = 1086.25;
   Float64 d_ixx = 43711.5237997;
   Float64 d_iyy = 460753.3242187;
   Float64 d_cgy = 10.81077867;

   // datum values
   props->get_Area(&area);
   props->get_Ixx(&ixx);
   props->get_Iyy(&iyy);
   props->get_Ixy(&ixy);
   cg.Release();
   props->get_Centroid(&cg);
   TRY_TEST( IsEqual(area,d_area), true );
   TRY_TEST( IsEqual(ixx, d_ixx), true );
   TRY_TEST( IsEqual(iyy, d_iyy), true );
   TRY_TEST( IsEqual(ixy,0.0), true );
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,0.0), true );
   TRY_TEST( IsEqual(cgy,d_cgy), true );
   CoordinateSystemType cst;
   props->get_CoordinateSystem(&cst);
   TRY_TEST( cst, csCentroidal );

   Float64 xleft,xright,ytop,ybottom;
   props->get_Xleft(&xleft);
   props->get_Xright(&xright);
   props->get_Ytop(&ytop);
   props->get_Ybottom(&ybottom);
   TRY_TEST(IsEqual(xleft,A/2.0),true);
   TRY_TEST(IsEqual(xright,A/2.0),true);
   TRY_TEST(IsEqual(ytop,20-d_cgy),true);
   TRY_TEST(IsEqual(ybottom,d_cgy),true);

   //
   // Perimeter
   //
   TRY_TEST( shape->get_Perimeter(NULL), E_POINTER );
   TRY_TEST( shape->get_Perimeter(&val), S_OK );
   TRY_TEST( IsEqual(val,192.378339), true );

   //
   // FurthestDistance
   //
   CComPtr<IPoint2d> p1;
   p1.CoCreateInstance( CLSID_Point2d );

   CComPtr<IPoint2d> p2;
   p2.CoCreateInstance( CLSID_Point2d );

   CComPtr<ILine2d> line;
   line.CoCreateInstance( CLSID_Line2d );

   // Shape on right
   p1->Move(0,50);
   p2->Move(100,50);
   line->ThroughPoints(p1,p2);
   Float64 dist;
   TRY_TEST( shape->FurthestDistance(NULL,&dist), E_INVALIDARG );
   TRY_TEST( shape->FurthestDistance(line,NULL), E_POINTER );
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,50.000), true );

   // shape on left
   p1->Move(0,-50);
   p2->Move(100,-50);
   line->ThroughPoints(p1,p2);
   TRY_TEST( shape->FurthestDistance(line,&dist), S_OK );
   TRY_TEST( IsEqual(dist,-50.0), true );

   // 
   // PolyPoints
   //
   CComPtr<IPoint2dCollection> coll;
   TRY_TEST( shape->get_PolyPoints(NULL), E_POINTER );
   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );

   CollectionIndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 8 );

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   CComPtr<IPoint2d> points[8];
   ULONG fetched;
   Enum->Next(8,&points[0],&fetched);
   TRY_TEST( fetched, 8 );

   Float64 Wb2 = (A-9*2)/2.0;

   Float64 x,y;
   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x, Wb2), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, Wb2), true );
   TRY_TEST( IsEqual(y, 12.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, A/2), true );
   TRY_TEST( IsEqual(y, 12.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, A/2-1.75), true );
   TRY_TEST( IsEqual(y, 20.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-(A/2-1.75)), true );
   TRY_TEST( IsEqual(y,  20.0), true );

   points[5]->get_X(&x);
   points[5]->get_Y(&y);
   TRY_TEST( IsEqual(x, -A/2), true );
   TRY_TEST( IsEqual(y,  12.0), true );

   points[6]->get_X(&x);
   points[6]->get_Y(&y);
   TRY_TEST( IsEqual(x, -Wb2), true );
   TRY_TEST( IsEqual(y,  12.0), true );

   points[7]->get_X(&x);
   points[7]->get_Y(&y);
   TRY_TEST( IsEqual(x, -Wb2), true );
   TRY_TEST( IsEqual(y,   0.0), true );

   //
   // Clone
   //
   CComPtr<IShape> clone;
   TRY_TEST(shape->Clone(NULL), E_POINTER );
   TRY_TEST(shape->Clone(&clone), S_OK);

   CComQIPtr<IDeckedSlabBeam> beamClone(clone);
   TRY_TEST( beamClone != 0, true );

   beamClone->get_A(&val);
   TRY_TEST( IsEqual(val,A), true);

   beamClone->get_B(&val);
   TRY_TEST( IsEqual(val,9.0), true);

   beamClone->get_C(&val);
   TRY_TEST( IsEqual(val,12.0), true);

   beamClone->get_W(&val);
   TRY_TEST( IsEqual(val,6.0), true);

   beamClone->get_Tt(&val);
   TRY_TEST( IsEqual(val,8.0), true);

   beamClone->get_Tb(&val);
   TRY_TEST( IsEqual(val,7.0), true);

   //
   // PointInShape
   //
   VARIANT_BOOL bPointInShape;
   CComPtr<IPoint2d> pnt;
   pnt.CoCreateInstance( CLSID_Point2d );
   pnt->Move(0.0, 1.0);

   TRY_TEST( shape->PointInShape(NULL,&bPointInShape), E_INVALIDARG );
   TRY_TEST( shape->PointInShape(pnt,NULL), E_POINTER );
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_TRUE );

   pnt->Move(500,500);
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_FALSE );

   pnt->Move(0,0); // Point on perimeter
   TRY_TEST( shape->PointInShape(pnt,&bPointInShape), S_OK );
   TRY_TEST( bPointInShape, VARIANT_FALSE );

   //
   // ClipWithLine
   //

   // setup clipping line
   p1->Move(-50,0.50);
   p2->Move( 50,0.50);

   CComPtr<ILine2d> clipLine;
   clipLine.CoCreateInstance( CLSID_Line2d );
   clipLine->ThroughPoints(p1,p2);

   CComPtr<IShape> clip;
   TRY_TEST(shape->ClipWithLine(NULL,&clip), E_INVALIDARG );
   TRY_TEST(shape->ClipWithLine(clipLine,NULL), E_POINTER );
   TRY_TEST(shape->ClipWithLine(clipLine,&clip), S_OK );
   TRY_TEST( clip != 0, true );
   
   // Verify clip by checking points
   coll.Release();
   Enum.Release();
   for ( int i = 0; i < 8; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 5 );

   coll->get__Enum(&Enum);
   Enum->Next(9,&points[0],&fetched);
   TRY_TEST( fetched, 5 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x, Wb2), true );
   TRY_TEST( IsEqual(y,  0.00), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, Wb2), true );
   TRY_TEST( IsEqual(y,  0.50), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-Wb2), true );
   TRY_TEST( IsEqual(y,   0.50), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-Wb2), true );
   TRY_TEST( IsEqual(y,   0.00), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,Wb2), true );
   TRY_TEST( IsEqual(y,  0.00), true );

   // clip in other direction
   p1->Move( 50, 0.50);
   p2->Move(-50, 0.50);

   clipLine->ThroughPoints(p1,p2);

   clip.Release();
   TRY_TEST(shape->ClipWithLine(NULL,&clip), E_INVALIDARG );
   TRY_TEST(shape->ClipWithLine(clipLine,NULL), E_POINTER );
   TRY_TEST(shape->ClipWithLine(clipLine,&clip), S_OK );
   TRY_TEST( clip != 0, true );
   
   coll.Release();
   Enum.Release();
   for ( int i = 0; i < 8; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 8 );

   coll->get__Enum(&Enum);
   Enum->Next(9,&points[0],&fetched);
   TRY_TEST( fetched, 8 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x, Wb2), true );
   TRY_TEST( IsEqual(y,  0.50), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, Wb2), true );
   TRY_TEST( IsEqual(y, 12.00), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, A/2.0), true );
   TRY_TEST( IsEqual(y, 12.00), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, A/2.0-1.75), true );
   TRY_TEST( IsEqual(y, 20.0), true );

   //
   // ClipIn
   //
   clip.Release();

   CComPtr<IRect2d> clipRect;
   clipRect.CoCreateInstance( CLSID_Rect2d );
   clipRect->put_Left(-100);
   clipRect->put_Right(100);
   clipRect->put_Top(11.0);
   clipRect->put_Bottom(1.5);

   TRY_TEST( shape->ClipIn(NULL,&clip), E_INVALIDARG );
   TRY_TEST( shape->ClipIn(clipRect,NULL), E_POINTER );
   TRY_TEST( shape->ClipIn(clipRect,&clip), S_OK );

   // Verify clip by checking points
   coll.Release();
   Enum.Release();
   for ( int i = 0; i < 8; i++)
      points[i].Release();

   TRY_TEST(clip->get_PolyPoints(&coll), S_OK );
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints, 4 );

   ATLTRACE("Trace of Points for DeckedSlabBeam - count = %d \n", cPoints);
   ATLTRACE("  pt         X         Y\n");
   ATLTRACE("---------------------------------\n");
   for (CollectionIndexType ip=0; ip<cPoints; ip++)
   {
      CComPtr<IPoint2d> pnt;
      coll->get_Item(ip, &pnt);
      Float64 x, y;
      pnt->get_X(&x);
      pnt->get_Y(&y);
      ATLTRACE(" %4d  %10f %10f \n", ip, x, y);
   }
   ATLTRACE("---------------------------\n");


   coll->get__Enum(&Enum);
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 4 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x, Wb2), true );
   TRY_TEST( IsEqual(y, 1.5), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, Wb2), true );
   TRY_TEST( IsEqual(y, 11.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-Wb2), true );
   TRY_TEST( IsEqual(y, 11.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, -Wb2), true );
   TRY_TEST( IsEqual(y,   1.5), true );

   // Remove void
   beam->put_VoidCount(0);

   d_area = 1325.0;
   d_ixx = 44545.211236897274;
   d_iyy = 506117.06770833326;
   d_cgy = 10.574591194968553;

   props.Release();
   TRY_TEST( shape->get_ShapeProperties(&props), S_OK );
   props->get_Area(&area);
   props->get_Ixx(&ixx);
   props->get_Iyy(&iyy);
   props->get_Ixy(&ixy);
   TRY_TEST( IsEqual(area,d_area), true );
   TRY_TEST( IsEqual(ixx, d_ixx), true );
   TRY_TEST( IsEqual(iyy, d_iyy), true );
   TRY_TEST( IsEqual(ixy,0.0), true );
   cg.Release();
   props->get_Centroid(&cg);
   cg->get_X(&cgx);
   cg->get_Y(&cgy);
   TRY_TEST( IsEqual(cgx,0.0), true );
   TRY_TEST( IsEqual(cgy,d_cgy), true );
}

void CTestDeckedSlabBeam::TestIXYPosition()
{
   CComPtr<IXYPosition> position;
   TRY_TEST( position.CoCreateInstance( CLSID_DeckedSlabBeam), S_OK);

   CComQIPtr<IDeckedSlabBeam> beam(position);
   CComQIPtr<IShape> shape(position);

   CComPtr<IPoint2d> hookPnt;
   hookPnt.CoCreateInstance( CLSID_Point2d );
   hookPnt->Move(0,0);

   // 6DS20
   beam->putref_HookPoint(hookPnt);

   Float64 A = 77.75;
   TRY_TEST( beam->put_A(A), S_OK );
   TRY_TEST( beam->put_B(9.0), S_OK );
   TRY_TEST( beam->put_C(12.0), S_OK );
   TRY_TEST( beam->put_W(6.0), S_OK );
   TRY_TEST( beam->put_Tt(8.0), S_OK );
   TRY_TEST( beam->put_Tb(7.0), S_OK );
   TRY_TEST( beam->put_F(1.75), S_OK );
   TRY_TEST( beam->put_LeftBlockOut(VARIANT_TRUE), S_OK );
   TRY_TEST( beam->put_RightBlockOut(VARIANT_TRUE), S_OK );

   // Get moment of inertia about CG before move
   // These properties should be invariant
   CComPtr<IShapeProperties> props;
   shape->get_ShapeProperties(&props);
   props->put_CoordinateSystem(csCentroidal);
   Float64 Ixx, Iyy;
   props->get_Ixx(&Ixx);
   props->get_Iyy(&Iyy);

   //
   // MoveEx (tests Offset as well)
   //
   CComPtr<IPoint2d> from;
   from.CoCreateInstance( CLSID_Point2d );
   from->Move(0,0);

   CComPtr<IPoint2d> to;
   to.CoCreateInstance( CLSID_Point2d );
   to->Move(100,100);

   TRY_TEST( position->MoveEx(NULL,to), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,NULL), E_INVALIDARG );
   TRY_TEST( position->MoveEx(from,to), S_OK );

   // Check the points
   CComPtr<IPoint2dCollection> coll;
   TRY_TEST( shape->get_PolyPoints(NULL), E_POINTER );
   TRY_TEST( shape->get_PolyPoints(&coll), S_OK );
   CollectionIndexType cPoints;
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,8);

   CComPtr<IEnumPoint2d> Enum;
   coll->get__Enum(&Enum);
   CComPtr<IPoint2d> points[8];
   ULONG fetched;
   Enum->Next(5,&points[0],&fetched);
   TRY_TEST( fetched, 5 );

   Float64 x,y;

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x, 129.875), true );
   TRY_TEST( IsEqual(y,100.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, 129.875), true );
   TRY_TEST( IsEqual(y, 112.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, 138.875), true );
   TRY_TEST( IsEqual(y, 112.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, 137.125), true );
   TRY_TEST( IsEqual(y,120.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x, 62.875), true );
   TRY_TEST( IsEqual(y,120.0), true );

   props.Release();
   shape->get_ShapeProperties(&props);
   Float64 val;
   props->get_Ixx(&val);
   TRY_TEST(IsEqual(Ixx,val),true);
   props->get_Iyy(&val);
   TRY_TEST(IsEqual(Iyy,val),true);

   //
   // OffsetEx
   //

   CComPtr<ISize2d> size;
   size.CoCreateInstance( CLSID_Size2d );
   size->put_Dx(-100);
   size->put_Dy(-100);

   TRY_TEST(position->OffsetEx(NULL), E_INVALIDARG );
   TRY_TEST(position->OffsetEx(size), S_OK);

   // Check the points
   coll.Release();
   Enum.Release();
   for ( int i = 0; i < 5; i++ )
      points[i].Release();
   
   shape->get_PolyPoints(&coll);
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,8);

   coll->get__Enum(&Enum);
   Enum->Next(10,&points[0],&fetched);
   TRY_TEST( fetched, 8 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,29.875), true );
   TRY_TEST( IsEqual(y,  0.0), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x, 29.875), true );
   TRY_TEST( IsEqual(y, 12.0), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x, 38.875), true );
   TRY_TEST( IsEqual(y, 12.0), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x, 37.125), true );
   TRY_TEST( IsEqual(y, 20.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-37.125), true );
   TRY_TEST( IsEqual(y, 20.0), true );

   props.Release();
   shape->get_ShapeProperties(&props);
   props->get_Ixx(&val);
   TRY_TEST(IsEqual(Ixx,val),true);
   props->get_Iyy(&val);
   TRY_TEST(IsEqual(Iyy,val),true);

   //
   // LocatorPoint property
   //
   hookPnt->Move(0,0);
   TRY_TEST( position->put_LocatorPoint(lpBottomLeft,NULL), E_INVALIDARG );
   TRY_TEST( position->get_LocatorPoint(lpBottomLeft,NULL), E_POINTER );

   // BottomLeft
   hookPnt->Move(0,0);
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.000), true );
   TRY_TEST(IsEqual(y,100.000), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,138.875), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // BottomCenter
   hookPnt->Move(0.0,0.0);
   to->Move(100.000,100.000);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.000), true );
   TRY_TEST(IsEqual(y,100.000), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   // BottomRight
   hookPnt->Move(0,0);
   to->Move(100.000,100.000);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpBottomRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpBottomRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.000), true );
   TRY_TEST(IsEqual(y,100.000), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 61.125), true );
   TRY_TEST(IsEqual(y, 100.0), true );

   // CenterLeft
   hookPnt->Move(0,0);
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,138.875), true );
   TRY_TEST(IsEqual(y, 90.0), true );

   // CenterCenter
   hookPnt->Move(0,0);
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y, 90.0), true );

   // CenterRight
   hookPnt->Move(0,0);
   to->Move(100.0,100.0);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpCenterRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpCenterRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 61.125), true );
   TRY_TEST(IsEqual(y, 90.0), true );

   // TopLeft
   hookPnt->Move(0,0);
   to->Move(100.0,100.0);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopLeft, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopLeft, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 138.875), true );
   TRY_TEST(IsEqual(y, 80.0), true );

   // TopCenter
   hookPnt->Move(0,0);
   to->Move(100.0,100.0);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopCenter, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopCenter, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y, 80.0), true );

   // TopRight
   hookPnt->Move(0,0);
   to->Move(100.0,100.0);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpTopRight, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpTopRight, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x, 61.125), true );
   TRY_TEST(IsEqual(y, 80.0), true );

   // HookPoint
   hookPnt->Move(0,0);
   to->Move(100,100);
   from.Release();
   TRY_TEST( position->put_LocatorPoint( lpHookPoint, to ), S_OK );
   TRY_TEST( position->get_LocatorPoint( lpHookPoint, &from ), S_OK );
   from->get_X(&x);
   from->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );
   hookPnt->get_X(&x);
   hookPnt->get_Y(&y);
   TRY_TEST(IsEqual(x,100.0), true );
   TRY_TEST(IsEqual(y,100.0), true );

   //
   // RotateEx (Provides coverage of Rotate)
   //
   hookPnt->Move(0,0);
   CComPtr<IPoint2d> c;
   c.CoCreateInstance( CLSID_Point2d );
   c->put_X(-38.875);
   c->put_Y(0);

   TRY_TEST( position->RotateEx(NULL,M_PI/2), E_INVALIDARG );
   TRY_TEST( position->RotateEx(c,M_PI/2), S_OK );

   // Check the points
   coll.Release();
   Enum.Release();
   for (int i = 0; i < 8; i++ )
      points[i].Release();
   
   shape->get_PolyPoints(&coll);
   coll->get_Count(&cPoints);
   TRY_TEST( cPoints,8);

   coll->get__Enum(&Enum);
   Enum->Next(8,&points[0],&fetched);
   TRY_TEST( fetched, 8 );

   points[0]->get_X(&x);
   points[0]->get_Y(&y);
   TRY_TEST( IsEqual(x,-38.875), true );
   TRY_TEST( IsEqual(y, 68.75), true );

   points[1]->get_X(&x);
   points[1]->get_Y(&y);
   TRY_TEST( IsEqual(x,-50.875), true );
   TRY_TEST( IsEqual(y, 68.75), true );

   points[2]->get_X(&x);
   points[2]->get_Y(&y);
   TRY_TEST( IsEqual(x,-50.875), true );
   TRY_TEST( IsEqual(y, 77.75), true );

   points[3]->get_X(&x);
   points[3]->get_Y(&y);
   TRY_TEST( IsEqual(x,-58.875), true );
   TRY_TEST( IsEqual(y, 76.0), true );

   points[4]->get_X(&x);
   points[4]->get_Y(&y);
   TRY_TEST( IsEqual(x,-58.875), true );
   TRY_TEST( IsEqual(y,  1.75), true );
}

void CTestDeckedSlabBeam::TestISupportErrorInfo()
{
   CComPtr<ISupportErrorInfo> eInfo;
   TRY_TEST( eInfo.CoCreateInstance( CLSID_DeckedSlabBeam ), S_OK );
   TRY_TEST( eInfo != 0, true );

   // Interfaces that should be supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IDeckedSlabBeam ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IShape ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IXYPosition ), S_OK );
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_IStructuredStorage2 ), S_OK );

   // Interface that is not supported
   TRY_TEST( eInfo->InterfaceSupportsErrorInfo( IID_ISupportErrorInfo ), S_FALSE );
}