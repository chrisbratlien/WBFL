#ifndef INCLUDED_JOINTEVENTS_H_
#define INCLUDED_JOINTEVENTS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JointEvents.h : header file
//

class CFEA2DDoc;

/////////////////////////////////////////////////////////////////////////////
// CJointEvents command target

class CJointEvents : public CCmdTarget
{
public:
	CJointEvents(CFEA2DDoc* pDoc);
   ~CJointEvents();

   DECLARE_INTERFACE_MAP()

   // iDisplayObjectEvents Implementation
   BEGIN_INTERFACE_PART(DisplayObjectEvents,iDisplayObjectEvents)
      STDMETHOD_(void,OnChanged)(iDisplayObject* pDO);
      STDMETHOD_(void,OnDragMoved)(iDisplayObject* pDO,ISize2d* offset);
      STDMETHOD_(bool,OnLButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnLButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnRButtonDblClk)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnRButtonDown)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnLButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnRButtonUp)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnMouseMove)(iDisplayObject* pDO,UINT nFlags,CPoint point);
      STDMETHOD_(bool,OnMouseWheel)(iDisplayObject* pDO,UINT nFlags,short zDelta,CPoint point);
      STDMETHOD_(void,OnMoved)(iDisplayObject* pDO);
      STDMETHOD_(void,OnCopied)(iDisplayObject* pDO);
      STDMETHOD_(bool,OnKeyDown)(iDisplayObject* pDO,UINT nChar, UINT nRepCnt, UINT nFlags);
      STDMETHOD_(bool,OnContextMenu)(iDisplayObject* pDO,CWnd* pWnd,CPoint point);
      STDMETHOD_(void,OnSelect)(iDisplayObject* pDO);
      STDMETHOD_(void,OnUnselect)(iDisplayObject* pDO);
   END_INTERFACE_PART(DisplayObjectEvents)

   // iDragData Implementation
   BEGIN_INTERFACE_PART(DragData,iDragData)
      STDMETHOD_(UINT,Format)();
      STDMETHOD_(BOOL,PrepareForDrag)(iDisplayObject* pDO,iDragDataSink* pSink);
      STDMETHOD_(void,OnDrop)(iDisplayObject* pDO,iDragDataSource* pSource);
   END_INTERFACE_PART(DragData)

public:
   static UINT ms_Format;
   CFEA2DDoc* m_pDoc;

private:
   void EditJoint(IDType jntID);
   void DeleteJoint(IDType jntID);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // INCLUDED_JOINTEVENTS_H_
