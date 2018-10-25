// BasicLiveLoadDataSetBuilder.h: interface for the BasicLiveLoadDataSetBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASICLIVELOADDATASETBUILDER_H__851938D5_0209_4F35_B735_36FB5049D1B5__INCLUDED_)
#define AFX_BASICLIVELOADDATASETBUILDER_H__851938D5_0209_4F35_B735_36FB5049D1B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataSetBuilder.h"
#include "ReactionReportBuilder.h"
#include "DataSetUtils.h"

class BasicLiveLoadDataSetBuilder : public iDataSetBuilder, public iReactionReportBuilder
{
public:
	BasicLiveLoadDataSetBuilder(LiveLoadModelType llmType, long llIndex, 
                               llResponseType respType, ILBAMModel* model, 
                               IBasicVehicularResponse* pResponse);

	virtual ~BasicLiveLoadDataSetBuilder();

   // iDataSetBuilder
   virtual void BuildDataSets(ILongArray* poilist, IDblArray* loclist, BSTR currStg,
                             CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                             COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);

   virtual long ColorDemand(BSTR currStg, CLBAMViewerDoc::ResponseType curr_rt)
   {
      return 1;
   }

   virtual CString GetDescription();

   // iReactionReportBuilder
   virtual void BuildReactionReport(ILongArray* supportlist, BSTR currStg,
                                    CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                                    std::ostream& pos);


   // indicate whether a truck placement is assocatiated with data set
   virtual bool HasTruckPlacement();
   virtual void GetTruckInfo(LiveLoadModelType* modelType, long* vehicleIndex, ILiveLoadConfiguration** placement);

private:
   void BuildForceDataSets(ILongArray* poilist, IDblArray* loclist, BSTR currStg,
                           CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                           COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);

   void BuildStressDataSets(ILongArray* poilist, IDblArray* loclist, BSTR currStg,
                            CLBAMViewerDoc::ResponseType curr_rt, ResultsSummationType summ_type,
                            COLORREF color, std::vector<iGraphXyDataProvider*>* dataSets);


	BasicLiveLoadDataSetBuilder();

   void InitializePlacement();

   LiveLoadModelType                m_LlmType;
   long                             m_LlIndex;
   CComPtr<ILBAMModel>              m_Model;
   CComPtr<IBasicVehicularResponse> m_Response;
   CComPtr<ILiveLoadConfiguration>  m_Placement;
   llResponseType                   m_RespType;
   bool                             m_IsTruck;
};

#endif // !defined(AFX_BASICLIVELOADDATASETBUILDER_H__851938D5_0209_4F35_B735_36FB5049D1B5__INCLUDED_)
