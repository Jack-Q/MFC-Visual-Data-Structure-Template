// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "ChildView.h"
#include "VisualListModule.h"
#include "VisualDefaultModule.h"

class CMainFrame : public CFrameWndEx
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// 特性
public:

// 操作
public:
    friend CChildView;

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
    CMFCRibbonStatusBar  m_wndStatusBar;
    CMFCCaptionBar    m_wndCaptionBar;
	CChildView    m_wndView;
// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnViewCaptionBar();
	afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnOptions();
	DECLARE_MESSAGE_MAP()

	BOOL CreateCaptionBar();
public:
    afx_msg void OnGalleryDataStructure();
    afx_msg void OnUpdateGalleryDataStructure(CCmdUI *pCmdUI);


private:
    CMFCRibbonGallery *m_gallery;
public:
    int m_selectedDataType;
    VisualModuleBase *m_selectedModule;
	BOOL OnDataStructureChange(int p_iItemToChange);
	VisualDefaultModule *m_mdlDefaultModule;
    VisualListModule *m_mdlListModule;

    void OnSetDefaultModule();

    afx_msg void OnListAddPosition();
    afx_msg void OnListAddData();
    afx_msg void OnListAdd();
    afx_msg void OnListDeleteAll();
    afx_msg void OnListEdit();
    afx_msg void OnListClose();
    afx_msg void OnListLinked();
    afx_msg void OnUpdateListLinked(CCmdUI *pCmdUI);
    afx_msg void OnListDouble();
    afx_msg void OnUpdateListDouble(CCmdUI *pCmdUI);
    afx_msg void OnListIndex();
    afx_msg void OnUpdateListIndex(CCmdUI *pCmdUI);
    afx_msg void OnListStzrtZero();
    afx_msg void OnUpdateListStzrtZero(CCmdUI *pCmdUI);
};


