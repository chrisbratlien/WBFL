///////////////////////////////////////////////////////////////////////
// GenericBridgeTools - Tools for manipluating the Generic Bridge Modeling
// Copyright � 1999-2015  Washington State Department of Transportation
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

// BridgeGeometryTool.cpp : Implementation of CBridgeGeometryTool
#include "stdafx.h"
#include "WBFLGenericBridgeTools.h"
#include "BridgeGeometryTool.h"
#include "Helpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

template <class T>
class CSafeObjectUsage
{
public:
   CSafeObjectUsage(T* pObject)
   {
      // if this exception fires, the internal object you are trying to use
      // is being used for another purpose
      m_pObject = pObject;
      ATLASSERT(m_pObject->AddRef() == 2);
   }
   ~CSafeObjectUsage()
   {
      // if this exception fires, the internal object you are using is messed up
      ATLASSERT(m_pObject->Release() == 1);
      m_pObject = 0;
   }

private:
   T* m_pObject;
};

#define USE_LINE(_line_) CSafeObjectUsage<ILine2d> _safety_##_line_ (_line_)
#define USE_LINESEGMENT(_line_) CSafeObjectUsage<ILineSegment2d> _safety_##_line_ (_line_)

/////////////////////////////////////////////////////////////////////////////
// CBridgeGeometryTool
HRESULT CBridgeGeometryTool::FinalConstruct()
{
   HRESULT hr = m_CogoEngine.CoCreateInstance(CLSID_CogoEngine);
   if ( FAILED(hr) ) 
   {
      return hr;
   }

   hr = m_GeomUtil.CoCreateInstance(CLSID_GeomUtil);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = m_Line1.CoCreateInstance(CLSID_Line2d);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = m_Line2.CoCreateInstance(CLSID_Line2d);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = m_LineSegment1.CoCreateInstance(CLSID_LineSegment2d);
   if ( FAILED(hr) )
   {
      return hr;
   }

   hr = m_LineSegment2.CoCreateInstance(CLSID_LineSegment2d);
   if ( FAILED(hr) )
   {
      return hr;
   }

   return S_OK;
}

void CBridgeGeometryTool::FinalRelease()
{
}

STDMETHODIMP CBridgeGeometryTool::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IBridgeGeometryTool
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
      {
			return S_OK;
      }
	}
	return S_FALSE;
}

STDMETHODIMP CBridgeGeometryTool::PointBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID, Float64 Xg, IPoint2d** point)
{
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISegment> segment;
   Float64 Xs;
   SegmentIndexType segIdx;
   ssmbr->GetDistanceFromStartOfSegment(Xg,&Xs,&segIdx,&segment);
   ATLASSERT(segment);

   return PointBySegment(bridge,ssMbrID,segIdx,Xs,point);
}

STDMETHODIMP CBridgeGeometryTool::PointBySegment(IGenericBridge* bridge,GirderIDType ssMbrID, SegmentIndexType segIdx, Float64 Xs, IPoint2d** point)
{
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISegment> segment;
   ssmbr->get_Segment(segIdx,&segment);

   CComPtr<IGirderLine> girderLine;
   segment->get_GirderLine(&girderLine);

   CComPtr<IPoint2d> p1, p2;
   girderLine->get_EndPoint(etStart,&p1);
   girderLine->get_EndPoint(etEnd,  &p2);
   
   Float64 brgOffset,endDist;
   girderLine->get_BearingOffset(etStart,&brgOffset);
   girderLine->get_EndDistance(etStart,&endDist);

   CComPtr<ILocate2> locate;
   m_CogoEngine->get_Locate(&locate);

   Float64 Xsp = Xs - (brgOffset-endDist);

   locate->PointOnLine(p1,p2,Xsp,0.00,point);

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::StationAndOffsetBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID, Float64 Xg, IStation** station, Float64* offset)
{
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISegment> segment;
   Float64 Xs;
   SegmentIndexType segIdx;
   HRESULT hr = ssmbr->GetDistanceFromStartOfSegment(Xg,&Xs,&segIdx,&segment);
   ATLASSERT(SUCCEEDED(hr));
   ATLASSERT(segment);

   return StationAndOffsetBySegment(bridge,ssMbrID,segIdx,Xs,station,offset);
}

STDMETHODIMP CBridgeGeometryTool::StationAndOffsetBySegment(IGenericBridge* bridge,GirderIDType ssMbrID, SegmentIndexType segIdx, Float64 Xs, IStation** station, Float64* offset)
{
   CComPtr<IPoint2d> point;
   PointBySegment(bridge,ssMbrID,segIdx,Xs,&point);

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   alignment->Offset(point,station,offset);

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::GirderPathOffset(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx, VARIANT varStation,Float64* offset)
{
   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   // get point on alignment at station
   CComPtr<IPoint2d> point_on_alignment;
   alignment->LocatePoint(varStation,omtAlongDirection, 0.00,CComVariant(0.00),&point_on_alignment);

   // get the superstructure member
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   // get the segment
   CComPtr<ISegment> segment;
   ssmbr->get_Segment(segIdx,&segment);

   // the the girder line
   CComPtr<IGirderLine> girderLine;
   segment->get_GirderLine(&girderLine);

   // Create a line that represents the girder path
   CComPtr<IPoint2d> p1, p2;
   girderLine->get_PierPoint(etStart,&p1);
   girderLine->get_PierPoint(etEnd,  &p2);

   CComPtr<ILine2d> line;
   line.CoCreateInstance(CLSID_Line2d);
   line->ThroughPoints(p1,p2);

   // Going to use the geometric utility object
   CComPtr<IGeomUtil2d> geom_util;
   geom_util.CoCreateInstance(CLSID_GeomUtil);
   ATLASSERT(geom_util != NULL);

   // Find the shortest distance from the point on the alignment to the
   // line representing the girder path. If the alignment point is on the right
   // of the girder path, offset will be > 0. This means the girder path is
   // offset to the left of the alignment so the offset that we want has the opposite
   // sign.
   geom_util->ShortestDistanceToPoint(line,point_on_alignment,offset);
   (*offset) *= -1;

   return S_OK;
}

#pragma Reminder("UPDATE: Remove Obsolete Code")
//
//STDMETHODIMP CBridgeGeometryTool::GirderLineBearing(IGenericBridge* bridge,SpanIndexType spanIdx,GirderIndexType gdrIdx,IDirection** direction)
//{
//   ATLASSERT(false); // re-implement
//   return S_OK;
//   //CComPtr<ICogoInfo> cogoinfo;
//   //bridge->get_CogoInfo(&cogoinfo);
//
//   //CogoObjectID startID, endID;
//   //cogoinfo->get_PierGirderIntersectionPointID(spanIdx,   gdrIdx, qcbAfter,  &startID);
//   //cogoinfo->get_PierGirderIntersectionPointID(spanIdx+1, gdrIdx, qcbBefore, &endID);
//
//   //CComPtr<ICogoModel> cogomodel;
//   //bridge->get_CogoModel(&cogomodel);
//
//   //CComPtr<IPointCollection> points;
//   //cogomodel->get_Points(&points);
//
//   //CComPtr<IPoint2d> p1, p2;
//   //points->get_Item(startID,&p1);
//   //points->get_Item(endID,  &p2);
//
//   //CComPtr<IMeasure2> measure;
//   //m_CogoEngine->get_Measure(&measure);
//
//   //return measure->Direction(p1,p2,direction);
//}
//
//STDMETHODIMP CBridgeGeometryTool::GirderLinePoint(IGenericBridge* bridge,Float64 distFromStartOfBridge,GirderIndexType gdrIdx,SpanIndexType* spanIdx,Float64* distFromStartOfSpan)
//{
//   //// Determine the span and the distance along that span which correspond to a 
//   //// distance from the start of the bridge and a girder line
//   //CComPtr<IPierCollection> piers;
//   //bridge->get_Piers(&piers);
//
//   //CComPtr<IEnumPiers> enum_piers;
//   //piers->get__EnumPiers(&enum_piers);
//
//   //CComPtr<IPier> pier;
//   //enum_piers->Next(1,&pier,NULL);
//
//   //CComPtr<IStation> objStartStation;
//   //pier->get_Station(&objStartStation);
//   //Float64 start_station;
//   //objStartStation->get_Value(&start_station);
//
//   //Float64 cut_station = start_station + distFromStartOfBridge;
//
//   //PierIndexType nPiers;
//   //piers->get_Count(&nPiers);
//   //SpanIndexType nSpans = SpanIndexType(nPiers - 1);
//
//   //// Find the span that contains this station
//   //SpanIndexType spanIndex = 0;
//   //if ( cut_station < start_station )
//   //{
//   //   // before start of bridge
//   //   spanIndex = 0;
//   //}
//   //else
//   //{
//   //   Float64 end_station;
//   //   pier.Release();
//   //   while ( enum_piers->Next(1,&pier,NULL) != S_FALSE )
//   //   {
//   //      CComPtr<IStation> station;
//   //      pier->get_Station(&station);
//   //      station->get_Value(&end_station);
//
//   //      if ( InRange(start_station,cut_station,end_station) )
//   //      {
//   //         // we found the span
//   //         break;
//   //      }
//
//   //      // next pier... try again
//   //      spanIndex++;
//   //      start_station = end_station;
//   //      pier.Release();
//   //   }
//
//   //   // don't go beyond the end of the bridge
//   //   if ( nSpans <= spanIndex )
//   //   {
//   //      spanIndex = nSpans-1;
//   //   }
//   //}
//
//   //// Get the start and end points of the girder line in this span
////   CComPtr<ISpanCollection> spans;
////   bridge->get_Spans(&spans);
////   CComPtr<ISpan> objSpan;
////   spans->get_Item(spanIndex,&objSpan);
////   GirderIndexType nGirders;
////   objSpan->get_GirderCount(&nGirders);
////   if ( gdrIdx == INVALID_INDEX )
////   {
////      // this means use the right-most girder
////      gdrIdx = nGirders - 1;
////   }
////
////   if ( nGirders <= gdrIdx )
////   {
////      *spanIdx = INVALID_INDEX;
////      *distFromStartOfSpan = 0;
////      return S_FALSE;
////   }
//
//   //CComPtr<ICogoInfo> cogoinfo;
//   //bridge->get_CogoInfo(&cogoinfo);
//   //CogoObjectID startPointID, endPointID;
//   //PierIndexType prevPierIdx = spanIndex;
//   //PierIndexType nextPierIdx = prevPierIdx+1;
//   //cogoinfo->get_PierGirderIntersectionPointID(prevPierIdx, gdrIdx, qcbAfter,  &startPointID);
//   //cogoinfo->get_PierGirderIntersectionPointID(nextPierIdx, gdrIdx, qcbBefore, &endPointID);
//
//   //CComPtr<ICogoModel> cogomodel;
//   //bridge->get_CogoModel(&cogomodel);
//
//   //CComPtr<IPointCollection> points;
//   //cogomodel->get_Points(&points);
//
//   //CComPtr<IPoint2d> startPoint,endPoint;
//   //points->get_Item(startPointID, &startPoint);
//   //points->get_Item(endPointID,   &endPoint  );
//
//   //// Create a point on the alignment at the cut station
//   //CComPtr<IAlignment> alignment;
//   //GetAlignment(bridge,&alignment);
//
//   //CComPtr<IPoint2d> cut_point;
//   //alignment->LocatePoint(CComVariant(cut_station),omtAlongDirection, 0.00,CComVariant(0.00),&cut_point);
//
//   //// Intersect the normal at the cut point with the girder line
//   //CComPtr<IDirection> normal;
//   //alignment->Normal(CComVariant(cut_station),&normal);
//
//   //CComPtr<IDirection> gdrBearing;
//   //GirderLineBearing(bridge,spanIndex,gdrIdx,&gdrBearing);
//
//   //CComQIPtr<IIntersect2> intersect(m_CogoEngine);
//
//   //CComPtr<IPoint2d> intersect_point;
//   //intersect->Bearings(cut_point,CComVariant(normal),0.00,startPoint,CComVariant(gdrBearing),0.00,&intersect_point);
//
//   //// Determine if the intersect_point actually falls in this span
//   //CComQIPtr<IMeasure2> measure(m_CogoEngine);
//
//   //Float64 girder_distance, cut_distance;
//   //measure->Distance(startPoint,endPoint,&girder_distance);
//   //measure->Distance(startPoint,intersect_point,&cut_distance);
//
//   //// if the cut is right at the end of the girder, this cleans up the "noise"
//   //if ( IsEqual(girder_distance,cut_distance) )
//   //   cut_distance = girder_distance;
//
//   //Float64 angle = 0;
//   //// if cut_distance is zero, intersect_point is at the same
//   //// location as startPoint...
//
//   //// determine if the cut location is before, in, or after this span
//   //// (if the span is skewed cut locations can be off this span)
//   ////
//   //// cut_distance is always positive so compute the angle from
//   //// end to start to intersection... if the angle is not zero, then
//   //// the intersection is not on the same line as start-end and is not after start
//   //if ( !IsZero(cut_distance) )
//   //{
//   //   CComPtr<IAngle> objAngle;
//   //   measure->Angle(endPoint,startPoint,intersect_point,&objAngle);
//   //   objAngle->get_Value(&angle);
//   //}
//
//   //if ( !IsEqual(angle,0.00) )
//   //{
//   //   // Intersect point occurs in the previous span
//   //   if ( spanIndex == 0 )
//   //   {
//   //      // before start of bridge
//   //      *spanIdx = INVALID_INDEX;
//   //      *distFromStartOfSpan = cut_distance - girder_distance;
//   //      return S_FALSE;
//   //   }
//
//   //   spanIndex--;
//
//   //   cogoinfo->get_PierGirderIntersectionPointID(spanIndex,gdrIdx,qcbAfter,&startPointID);
//
//   //   startPoint.Release();
//   //   points->get_Item(startPointID, &startPoint);
//
//   //   measure->Distance(startPoint,intersect_point,&cut_distance);
//
//   //   *distFromStartOfSpan = cut_distance;
//   //   *spanIdx = spanIndex;
//   //}
//   //else if ( girder_distance < cut_distance )
//   //{
//   //   // Intersect point occurs in next span
//   //   spanIndex++;
//
//   //   if ( nSpans <= spanIndex  )
//   //   {
//   //      // after end of bridge
//   //      *spanIdx = INVALID_INDEX;
//   //      *distFromStartOfSpan = girder_distance - cut_distance;
//   //      return S_FALSE;
//   //   }
//
//   //   cogoinfo->get_PierGirderIntersectionPointID(spanIndex,gdrIdx,qcbAfter,&startPointID);
//
//   //   startPoint.Release();
//   //   points->get_Item(startPointID, &startPoint);
//
//   //   measure->Distance(startPoint,intersect_point,&cut_distance);
//
//   //   *distFromStartOfSpan = cut_distance;
//   //   *spanIdx = spanIndex;
//   //}
//   //else
//   //{
//   //   // Intersect point occurs in this span
//   //   *spanIdx = spanIndex;
//   //   *distFromStartOfSpan = cut_distance;
//   //}
//
//   //return S_OK;
//}

STDMETHODIMP CBridgeGeometryTool::DeckEdgePoint(IGenericBridge* bridge, Float64 station, IDirection* direction,DirectionType side, IPoint2d** point)
{
   // determine slab type and overhang
   CComPtr<IPath> path;
   HRESULT hr = GetDeckEdgePath(bridge,side,&path);
   if ( FAILED(hr) )
   {
      return hr;
   }

   // get the alignment
   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   // locate a point on the alignment at the given station
   CComPtr<IPoint2d> point_on_alignment;
   alignment->LocatePoint(CComVariant(station),omtAlongDirection, 0.00,CComVariant(0.00),&point_on_alignment);

   // Create a line to intersection with the edge of deck
   Float64 angle;
   direction->get_Value(&angle);

   CComPtr<IPoint2d> p;
   CComPtr<IVector2d> vector;

   USE_LINE(m_Line1);
   m_Line1->GetExplicit(&p,&vector);
   vector->put_Direction(angle);

   m_Line1->SetExplicit(point_on_alignment,vector);

   path->Intersect(m_Line1,point_on_alignment,point);

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::DeckEdgePoints(IGenericBridge* bridge,DirectionType side,CollectionIndexType nPoints,IPoint2dCollection** points)
{
   CComPtr<IPoint2dCollection> edge_points;
   edge_points.CoCreateInstance(CLSID_Point2dCollection);

   CComPtr<IPierCollection> piers;
   bridge->get_Piers(&piers);

   PierIndexType nPiers;
   piers->get_Count(&nPiers);

   CComPtr<IPier> first_pier, last_pier;
   piers->get_Item(0,&first_pier);
   piers->get_Item(nPiers - 1,&last_pier);

   CComPtr<IStation> objFirstStation,objLastStation;
   first_pier->get_Station(&objFirstStation);
   last_pier->get_Station(&objLastStation);

   Float64 first_station, last_station;
   objFirstStation->get_Value(&first_station);
   objLastStation->get_Value(&last_station);

   CComPtr<IDirection> objFirstDirection, objLastDirection;
   first_pier->get_Direction(&objFirstDirection);
   last_pier->get_Direction(&objLastDirection); 
   
   Float64 first_direction, last_direction;
   objFirstDirection->get_Value(&first_direction);
   objLastDirection->get_Value(&last_direction);

   // Get station of deck points at first and last piers, projected normal to aligment
   CComPtr<IPoint2d> objFirstPoint, objLastPoint;
   DeckEdgePoint(bridge,first_station,objFirstDirection,side,&objFirstPoint);
   DeckEdgePoint(bridge,last_station, objLastDirection, side,&objLastPoint);

   CComPtr<IAlignment> alignment;
   GetAlignment(bridge,&alignment);

   CComPtr<IStation> objFirst_normal_station, objLast_normal_station;
   Float64 offset;

   alignment->Offset(objFirstPoint,&objFirst_normal_station,&offset);
   alignment->Offset(objLastPoint, &objLast_normal_station, &offset);

   Float64 first_normal_station, last_normal_station;
   objFirst_normal_station->get_Value(&first_normal_station);
   objLast_normal_station->get_Value( &last_normal_station);

   // If there is a skew, the first deck edge can be before the pier station, or after it. 
   // Same for the last deck edge. We must deal with this
   edge_points->Add(objFirstPoint);

   Float64 station_inc = (last_station - first_station)/(nPoints-1);
   Float64 station = first_station;
   Float64 direction = first_direction;
   for ( CollectionIndexType i = 0; i < nPoints; i++, station += station_inc)
   {
      if (station > first_normal_station && station < last_normal_station)
      {
         // Normal at station
         CComPtr<IDirection> objDirection;
         alignment->Normal(CComVariant(station), &objDirection);

         CComPtr<IPoint2d> p;
         DeckEdgePoint(bridge,station,objDirection,side,&p);

         if ( p )
         {
            edge_points->Add(p);
         }
      }
   }

   // add final edge
   edge_points->Add(objLastPoint);

   (*points) = edge_points;
   (*points)->AddRef();

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::DeckOffset(IGenericBridge* bridge,Float64 station,IDirection* direction,DirectionType side,Float64* pOffset)
{
   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   CComPtr<IDirection> objDirection;
   if ( direction == NULL )
   {
      alignment->Normal(CComVariant(station),&objDirection);
   }
   else
   {
      objDirection = direction;
   }

   CComPtr<IPoint2d> pntEdge;
   HRESULT hr = DeckEdgePoint(bridge,station,objDirection,side,&pntEdge);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 offset;
   CComPtr<IStation> objStation;
   alignment->Offset(pntEdge,&objStation,&offset);

#if defined _DEBUG
   Float64 value;
   objStation->get_Value(&value);
   ATLASSERT( IsEqual(value,station,0.0005));
#endif // _DEBUG

   *pOffset = offset;

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::CurbOffset(IGenericBridge* bridge,Float64 station,IDirection* direction,DirectionType side,Float64* pOffset)
{
   Float64 offset;
   HRESULT hr = DeckOffset(bridge,station,direction,side,&offset);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 distFromStartOfBridge = StationToDistance(bridge,station);

   // get connection length of barrier
   CComPtr<ISidewalkBarrier> barrier;
   if ( side == qcbLeft )
   {
      bridge->get_LeftBarrier(&barrier);
   }
   else
   {
      bridge->get_RightBarrier(&barrier);
   }

   Float64 connection_width;
   barrier->get_ExteriorCurbWidth(&connection_width);
   offset += (side == qcbLeft ? connection_width : -connection_width);

   *pOffset = offset;

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::InteriorCurbOffset(IGenericBridge* bridge,Float64 station,IDirection* direction,DirectionType side,Float64* pOffset)
{
   Float64 offset;
   HRESULT hr = DeckOffset(bridge,station,direction,side,&offset);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 distFromStartOfBridge = StationToDistance(bridge,station);

   // get interior connection length of barrier
   CComPtr<ISidewalkBarrier> barrier;
   if ( side == qcbLeft )
   {
      bridge->get_LeftBarrier(&barrier);
   }
   else
   {
      bridge->get_RightBarrier(&barrier);
   }

   Float64 connection_width;
   barrier->get_CurbWidth(&connection_width);
   offset += (side == qcbLeft ? connection_width : -connection_width);

   *pOffset = offset;

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::DeckOverhang(IGenericBridge* bridge,Float64 station,GirderIDType ssMbrID,IDirection* direction,DirectionType side,Float64* pOverhang)
{
   // Computes the offset from the superstructure member identified by "ssMbrID" to the edge of deck
   // on the side of the bridge specified by "side". The offset is measured along a line in
   // the direction specified by "direction" passing throught "station". If "direction" is NULL, the line 
   // is taken to be normal to the alignment at "station"

   //
   // Create a line passing through station in the specified direction
   //

   // Get the alignment
   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   // use a local object so that direction is reference counted
   // if dir is NULL, the alignment normal is not ref counted and it leaks
   CComPtr<IDirection> dir(direction);

   // if dir is NULL, use the normal to the alignment
   if ( dir == NULL )
   {
      alignment->Normal(CComVariant(station),&dir);
   }

   // Get point on alignment at station
   CComPtr<IPoint2d> alignment_point;
   alignment->LocatePoint(CComVariant(station),omtAlongDirection, 0.00,CComVariant(0.00),&alignment_point);

   // Create a line through the alignment point in the direction of "direction"
   // Use the m_Line2 object (it is faster if we don't have to create it every time it is needed)
   USE_LINE(m_Line2);
   Float64 angle;
   dir->get_Value(&angle);
   
   CComPtr<IPoint2d> p;
   CComPtr<IVector2d> v;
   m_Line2->GetExplicit(&p,&v);
   v->put_X(cos(angle));
   v->put_Y(sin(angle));
   m_Line2->SetExplicit(alignment_point,v);

   //
   // Get the intersection point of the line passing through the alignment and the superstructure member
   //

   // get the superstructure member
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   // using a line semgnet
   USE_LINESEGMENT(m_LineSegment1);

   // loop over all the segments until the line defined above intersects with one of the segments
   SegmentIndexType nSegments;
   ssmbr->get_SegmentCount(&nSegments);
   CComPtr<IPoint2d> pntSegment;
   for ( SegmentIndexType segIdx = 0; segIdx < nSegments; segIdx++ )
   {
      CComPtr<ISegment> segment;
      ssmbr->get_Segment(segIdx,&segment);

      CComPtr<IGirderLine> girderLine;
      segment->get_GirderLine(&girderLine);

      CComPtr<IPoint2d> pnt1,pnt2;
      girderLine->get_PierPoint(etStart,&pnt1);
      girderLine->get_PierPoint(etEnd,  &pnt2);

      m_LineSegment1->ThroughPoints(pnt1,pnt2);

      CComPtr<IPoint2d> pntIntersect;
      m_GeomUtil->IntersectLineWithLineSegment(m_Line2,m_LineSegment1,&pntIntersect);
      if ( pntIntersect != NULL )
      {
         // an intersection was found
         pntSegment = pntIntersect;
         break; // get the heck outta of the loop
      }
   }

   if ( pntSegment == NULL )
   {
      // extend the last segment until there is an intersection
      CComPtr<ISegment> segment;
      ssmbr->get_Segment(nSegments-1,&segment);

      CComPtr<IGirderLine> girderLine;
      segment->get_GirderLine(&girderLine);

      CComPtr<IPoint2d> pnt1,pnt2;
      girderLine->get_PierPoint(etStart,&pnt1);
      girderLine->get_PierPoint(etEnd,  &pnt2);

      USE_LINE(m_Line1);
      m_Line1->ThroughPoints(pnt1,pnt2);

      CComPtr<IPoint2d> pntIntersect;
      m_GeomUtil->LineLineIntersect(m_Line2,m_Line1,&pntSegment);
   }

   ATLASSERT(pntSegment != NULL);

   //
   // Get the deck edge point
   //
   CComPtr<IPoint2d> pntEdge;
   HRESULT hr = DeckEdgePoint(bridge,station,dir,side,&pntEdge);
   if ( FAILED(hr) )
   {
      return hr;
   }


   // offset is distance between girder line point and deck point
   Float64 dist;
   m_GeomUtil->Distance(pntSegment,pntEdge,&dist);

   // Distance is always a positive quantity... distance needs to be < 0 if inboard of the girder line
   // create a vector from pntSegment to pntDeck
   Float64 x1,y1;
   Float64 x2,y2;
   pntSegment->Location(&x1,&y1);
   pntEdge->Location(&x2,&y2);

   v->put_X(x2-x1); 
   v->put_Y(y2-y1);

   // get the normal to the girder line (normal goes to the left of the line in this case)
   CComPtr<IPoint2d> pnt1,pnt2;
   m_LineSegment1->get_StartPoint(&pnt1);
   m_LineSegment1->get_EndPoint(&pnt2);

   // changing line 2... line 2 is now the girder line
   m_Line2->ThroughPoints(pnt1,pnt2);
   Float64 c;
   CComPtr<IVector2d> n;
   m_Line2->GetImplicit(&c,&n);

   // compute the dot product of the normal vector and the vector from the girder to the deck point
   Float64 dot;
   n->Dot(v,&dot);

   if ( dot < 0 && side == qcbLeft || 0 < dot && side == qcbRight )
   {
      dist *= -1;
   }

   *pOverhang = dist;
   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::DeckOverhangBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 Xg,IDirection* dir,DirectionType side,Float64* pOverhang)
{
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISegment> segment;
   Float64 Xs;
   SegmentIndexType segIdx;
   ssmbr->GetDistanceFromStartOfSegment(Xg,&Xs,&segIdx,&segment);
   ATLASSERT(segment);

   return DeckOverhangBySegment(bridge,ssMbrID,segIdx,Xs,dir,side,pOverhang);
}

STDMETHODIMP CBridgeGeometryTool::DeckOverhangBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,IDirection* dir,DirectionType side,Float64* pOverhang)
{
   // Computes the distance from the centerline of the superstructure member to the edge of deck along a given direction

   // Get station and offset of point on segment where deck overhang is to be computed
   CComPtr<IStation> objStation;
   Float64 offset;
   HRESULT hr = StationAndOffsetBySegment(bridge,ssMbrID,segIdx,Xs,&objStation,&offset);
   if ( FAILED(hr) )
   {
      return hr;
   }

   Float64 station;
   objStation->get_Value(&station);

   // Get the alignment
   CComPtr<IAlignment> alignment;
   bridge->get_Alignment(&alignment);

   // use a local object so that direction is reference counted
   // if dir is NULL, the alignment normal is not ref counted and it leaks
   CComPtr<IDirection> direction(dir);

   // if direction is NULL, use the normal to the alignment
   if ( direction == NULL )
   {
      alignment->Normal(CComVariant(objStation),&direction);
   }

   // Get point on edge of deck
   CComPtr<IPoint2d> pntDeck;
   hr = DeckEdgePoint(bridge,station,direction,side,&pntDeck);
   if ( FAILED(hr) )
   {
      return hr;
   }

   // Get point on alignment at station
   CComPtr<IPoint2d> alignment_point;
   alignment->LocatePoint(CComVariant(objStation),omtAlongDirection, 0.00,CComVariant(0.00),&alignment_point);

   // Create a line through the alignment point in the direction of "direction"
   // Use the m_Line1 object (it is faster if we don't have to create it every time it is needed)
   USE_LINE(m_Line1);
   Float64 angle;
   direction->get_Value(&angle);
   
   CComPtr<IPoint2d> p;
   CComPtr<IVector2d> v;
   m_Line1->GetExplicit(&p,&v);
   v->put_X(cos(angle));
   v->put_Y(sin(angle));
   m_Line1->SetExplicit(alignment_point,v);


   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISegment> segment;
   ssmbr->get_Segment(segIdx,&segment);

   CComPtr<IGirderLine> girderLine;
   segment->get_GirderLine(&girderLine);

   // get end points of the girder l ine
   CComPtr<IPoint2d> p1, p2;
   girderLine->get_PierPoint(etStart,&p1);
   girderLine->get_PierPoint(etEnd,  &p2);

   // line 2 is a cogo line object that represents the girder line
   USE_LINE(m_Line2);
   m_Line2->ThroughPoints(p1,p2);

   // intersect line from alignment with girder line
   CComPtr<IPoint2d> pntGirder;
   m_GeomUtil->LineLineIntersect(m_Line1,m_Line2,&pntGirder);

   // offset is distance between girder line point and deck point
   Float64 dist;
   m_GeomUtil->Distance(pntGirder,pntDeck,&dist);

   // Distance is always a positive quantity... distance needs to be < 0 if inboard of the girder line
   // create a vector from pntGirder to pntDeck
   Float64 x1,y1;
   Float64 x2,y2;
   pntGirder->Location(&x1,&y1);
   pntDeck->Location(&x2,&y2);

   v->put_X(x2-x1); 
   v->put_Y(y2-y1);

   // get the normal to the girder line (normal goes to the left of the line in this case)
   Float64 c;
   CComPtr<IVector2d> n;
   m_Line2->GetImplicit(&c,&n);

   // compute the dot product of the normal vector and the vector from the girder to the deck point
   Float64 dot;
   n->Dot(v,&dot);

   if ( dot < 0 && side == qcbLeft || 0 < dot && side == qcbRight )
   {
      dist *= -1;
   }

   *pOverhang = dist;
   return S_OK;
}

HRESULT CBridgeGeometryTool::GetDeckEdgePath(IGenericBridge* bridge,DirectionType side,IPath** ppPath)
{
   CComPtr<IBridgeDeck> deck;
   bridge->get_Deck(&deck);

   if ( deck == NULL )
   {
      // no deck...use the traffic barrier path
      CComPtr<ISidewalkBarrier> barrier;
      if ( side == qcbLeft )
      {
         bridge->get_LeftBarrier(&barrier);
      }
      else
      {
         bridge->get_RightBarrier(&barrier);
      }

      return barrier->get_Path(ppPath);
   }


   // Intersection line with path... we want the point to be the one nearest the point on the alignment
   CComPtr<IDeckBoundary> deckBoundary;
   deck->get_DeckBoundary(&deckBoundary);

   // VARIANT_TRUE to get the layout line and not the actual edge path. The actual deck edge path
   // teminates at the ends of the deck.
   deckBoundary->get_EdgePath((SideType)side,VARIANT_TRUE,ppPath); 

   return S_OK;
}

STDMETHODIMP CBridgeGeometryTool::GirderSpacingBySSMbr(IGenericBridge* bridge,GirderIDType ssMbrID,Float64 Xg,GirderIDType otherSSMbrID,Float64* pSpacing)
{
   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);

   CComPtr<ISegment> segment;
   Float64 Xs;
   SegmentIndexType segIdx;
   ssmbr->GetDistanceFromStartOfSegment(Xg,&Xs,&segIdx,&segment);
   ATLASSERT(segment);

   return GirderSpacingBySegment(bridge,ssMbrID,segIdx,Xs,otherSSMbrID,pSpacing);
}

STDMETHODIMP CBridgeGeometryTool::GirderSpacingBySegment(IGenericBridge* bridge,GirderIDType ssMbrID,SegmentIndexType segIdx,Float64 Xs,GirderIDType otherSSMbrID,Float64* pSpacing)
{
   // Computes the perpendicular distance between the superstructure member (ssMbrID) at the a distance along this 
   // superstructure member (distFromStartOfSSMbr) and another superstructure member (otherSSMbrID)

   if ( otherSSMbrID == INVALID_ID )
   {
      *pSpacing = 0;
      return E_FAIL;
   }

   CComPtr<ISuperstructureMember> ssmbr;
   bridge->get_SuperstructureMember(ssMbrID,&ssmbr);
   ATLASSERT(ssmbr); // why? bad ssMbrID?

   CComPtr<ISegment> segment;
   ssmbr->get_Segment(segIdx,&segment);
   ATLASSERT(segment);

   CComPtr<IGirderLine> girderLine; // girderLine for this girder
   segment->get_GirderLine(&girderLine);

   // Get point object for point under consideration
   CComQIPtr<ILocate2> locate(m_CogoEngine);

   // get end points of girder line
   CComPtr<IPoint2d> p1, p2;
   girderLine->get_EndPoint(etStart,&p1);
   girderLine->get_EndPoint(etEnd,  &p2);

   // locate point on girder line where spacing is measured
   CComPtr<IPoint2d> pntOnGirder;
   locate->PointOnLine(p1,p2,Xs,0.00,&pntOnGirder);

   // Use m_Line1 for a line that is perpendicular to the girder line, throught pntOnGirder
   USE_LINE(m_Line1);
   m_Line1->ThroughPoints(p1,p2); // line runs along girderline
   m_Line1->RotateEx(pntOnGirder,PI_OVER_2); // rotate 90 degrees, centered on pntOnGirder

   // Get the girder line for the adjacent girder
   // We don't know which segment the normal line will intersect, so start with the
   // first one and work down the superstructure member
   CComPtr<IGirderLine> otherGirderLine; // girderLine for the girder spacing is measured to
   CComPtr<ISuperstructureMember> otherSSMbr;
   bridge->get_SuperstructureMember(otherSSMbrID,&otherSSMbr);

   SegmentIndexType nSegments;
   otherSSMbr->get_SegmentCount(&nSegments);
   CComPtr<IPoint2d> pntOnOtherGirder;
   for ( SegmentIndexType segIdx = 0; segIdx < nSegments; segIdx++ )
   {
      CComPtr<ISegment> otherSegment;
      otherSSMbr->get_Segment(segIdx,&otherSegment);
      otherSegment->get_GirderLine(&otherGirderLine);

      // Use m_Line2 for second girder line (doesn't really matter which end points we use)
      USE_LINE(m_Line2);
      CComPtr<IPoint2d> p3, p4;
      otherGirderLine->get_PierPoint(etStart,&p3);
      otherGirderLine->get_PierPoint(etEnd,  &p4);
      m_Line2->ThroughPoints(p3,p4);

      // Intersect normal line and other girder line
      if ( m_GeomUtil->LineLineIntersect(m_Line1,m_Line2,&pntOnOtherGirder) == S_OK )
      {
         // point found
         break;
      }
   }

   if ( pntOnOtherGirder == NULL )
   {
      ATLASSERT(false); // point not found, and it should have been???
      return E_FAIL;
   }

   // compute distance to get spacing
   pntOnGirder->DistanceEx(pntOnOtherGirder,pSpacing);

   return S_OK;
}
