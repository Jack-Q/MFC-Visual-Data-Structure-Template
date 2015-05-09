// MainFrm.h : CMainFrame ��Ľӿ�
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

// ����
public:

// ����
public:
    friend CChildView;

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
    CMFCRibbonStatusBar  m_wndStatusBar;
    CMFCCaptionBar    m_wndCaptionBar;
	CChildView    m_wndView;
// ���ɵ���Ϣӳ�亯��
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


