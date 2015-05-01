// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "01-DataStructureTemplete.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
    ON_WM_CREATE()
    ON_WM_SETFOCUS()
    ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
    ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
    ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
    ON_COMMAND(ID_GALLERY_DATA_STRUCTURE, &CMainFrame::OnGalleryDataStructure)
    ON_UPDATE_COMMAND_UI(ID_GALLERY_DATA_STRUCTURE, &CMainFrame::OnUpdateGalleryDataStructure)
    ON_COMMAND(ID_LIST_ADD, &CMainFrame::OnListAdd)
    ON_COMMAND(ID_LIST_ADD_POSITION, &CMainFrame::OnListAddPosition)
    ON_COMMAND(ID_LIST_ADD_DATA, &CMainFrame::OnListAddData)
    ON_COMMAND(ID_LIST_DELETE_ALL, &CMainFrame::OnListDeleteAll)
    ON_COMMAND(ID_LIST_EDIT, &CMainFrame::OnListEdit)
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame() 
    : m_mdlDefaultModule(NULL), 
    m_mdlListModule(NULL),
    m_wndView(this)
{
    theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_WINDOWS_7);
    //默认不选择数据结构
    m_selectedDataType = -1;

}

CMainFrame::~CMainFrame() {
    if (m_mdlListModule) {
        delete m_mdlListModule;
    }
    if (m_mdlDefaultModule) {
        delete m_mdlDefaultModule;
    }
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
        return -1;

    BOOL bNameValid;

    // 创建一个视图以占用框架的工作区
    if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL)) {
        TRACE0("未能创建视图窗口\n");
        return -1;
    }

    m_wndRibbonBar.Create(this);
    m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

    //初始化数据结构选择菜单为空选项
    m_gallery = (CMFCRibbonGallery *) m_wndRibbonBar.FindByID(ID_GALLERY_DATA_STRUCTURE);
    m_gallery->SelectItem(-1);
    m_gallery->SetItemToolTip(0, _T("链表"));
    m_gallery->SetItemToolTip(1, _T("队列"));
    m_gallery->SetItemToolTip(2, _T("堆栈"));

    //初始化默认页面控制模板并设置为当前模板
    m_selectedModule = m_mdlDefaultModule = new VisualDefaultModule();

    if (!m_wndStatusBar.Create(this)) {
        TRACE0("未能创建状态栏\n");
        return -1;      // 未能创建
    }

    CString strTitlePane1;
    CString strTitlePane2;
    bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
    ASSERT(bNameValid);
    bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
    ASSERT(bNameValid);
    m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
    m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

    // 启用 Visual Studio 2005 样式停靠窗口行为
    CDockingManager::SetDockingMode(DT_SMART);
    // 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
    EnableAutoHidePanes(CBRS_ALIGN_ANY);

    // 创建标题栏: 
    if (!CreateCaptionBar()) {
        TRACE0("未能创建标题栏\n");
        return -1;      // 未能创建
    }
    // 基于持久值设置视觉管理器和样式
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
    //m_wndRibbonBar.SetWindows7Look(TRUE);

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) {
    if (!CFrameWndEx::PreCreateWindow(cs))
        return FALSE;
    // TODO:  在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式
    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
    cs.lpszClass = AfxRegisterWndClass(0);
    return TRUE;
}

BOOL CMainFrame::CreateCaptionBar() {
    if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE)) {
        TRACE0("未能创建标题栏\n");
        return FALSE;
    }

    BOOL bNameValid;

    CString strTemp, strTemp2;

    /*bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
    ASSERT(bNameValid);
    m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
    bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
    ASSERT(bNameValid);
    m_wndCaptionBar.SetButtonToolTip(strTemp);*/

    bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
    ASSERT(bNameValid);
    m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

    m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
    bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
    ASSERT(bNameValid);
    bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
    ASSERT(bNameValid);
    m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);

    return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const {
    CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const {
    CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/) {
    // 将焦点前移到视图窗口
    m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) {
    // 让视图第一次尝试该命令
    if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
        return TRUE;

    // 否则，执行默认处理
    return CFrameWndEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnViewCaptionBar() {
    m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
    RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI) {
    pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}

void CMainFrame::OnOptions() {
    CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
    ASSERT(pOptionsDlg != NULL);

    pOptionsDlg->DoModal();
    delete pOptionsDlg;
}



void CMainFrame::OnGalleryDataStructure() {
    // 数据结构类型切换，如果切换被终止，则更新GalleryButton为先前选项
    if (OnDataStructureChange(m_gallery->GetSelectedItem())) {
        m_selectedDataType = m_gallery->GetSelectedItem();
    }
    else {
        m_gallery->SelectItem(m_selectedDataType);
    }
    m_wndRibbonBar.RecalcLayout();
}


void CMainFrame::OnUpdateGalleryDataStructure(CCmdUI *pCmdUI) {
}

BOOL CMainFrame::OnDataStructureChange(int p_iItemToChange) {
    //若切换至相同的模块，则直接返回TRUE
    if (p_iItemToChange == m_selectedDataType) {
        return TRUE;
    }
    //切换前先检查是否可以切换
    if (!m_selectedModule->CheckClose()) {
        return FALSE;
    }

    VisualModuleBase *newModule = NULL;

    //开启新模块
    switch (p_iItemToChange) {
        case 0://Link List
            m_wndRibbonBar.HideAllContextCategories();
            m_wndRibbonBar.ShowContextCategories(ID_LINK_LIST_CONTEXT, TRUE);
            m_wndRibbonBar.ActivateContextCategory(ID_LINK_LIST_CONTEXT);
            if (!m_mdlListModule) {
                m_mdlListModule = new VisualListModule();
            }
            newModule = m_mdlListModule;
            break;
        case 1://Queue
            AfxMessageBox(_T("队列模块尚未完成"));
            //m_wndRibbonBar.HideAllContextCategories();
            //m_wndRibbonBar.ShowContextCategories(ID_QUEUE_CONTEXT, TRUE);
            //m_wndRibbonBar.ActivateContextCategory(ID_QUEUE_CONTEXT);
            //newModule = ?
            break;
        case 2://Stack
            AfxMessageBox(_T("堆栈模块尚未完成"));
            //m_wndRibbonBar.HideAllContextCategories();
            //m_wndRibbonBar.ShowContextCategories(ID_STACK_CONTEXT, TRUE);
            //m_wndRibbonBar.ActivateContextCategory(ID_STACK_CONTEXT);
            //newModule = ?
            break;
        default:
            if (!m_mdlDefaultModule) {
                m_mdlDefaultModule = new VisualDefaultModule();
            }
            m_wndRibbonBar.HideAllContextCategories();
            newModule = m_mdlDefaultModule;
    }

    //关闭原有模块，并开启新模块
    if (newModule) {
        m_selectedModule->OnClose();
        m_selectedModule = newModule;
        m_selectedModule->OnShow();
        Invalidate();
    }
    else {
        return FALSE;
    }

    return TRUE;
}


//////////////////////////////////////////////////////////////////////////
// 链表选项卡事件处理

// 设置将要插入链表数据的位置输入框
void CMainFrame::OnListAddPosition() {
    CMFCRibbonEdit *edit = (CMFCRibbonEdit *) m_wndRibbonBar.FindByID(ID_LIST_ADD_POSITION);
    AfxMessageBox(edit->GetEditText() + _T(" Entered "));
}

// 设置将插入链表数据输入框
void CMainFrame::OnListAddData() {
    CMFCRibbonEdit *edit = (CMFCRibbonEdit *) m_wndRibbonBar.FindByID(ID_LIST_ADD_DATA);
    AfxMessageBox(edit->GetEditText() + _T(" Entered "));
}

// 添加数据按钮
void CMainFrame::OnListAdd() {
    AfxMessageBox(_T("List Add Item"));
}

// 删除全部数据按钮
void CMainFrame::OnListDeleteAll() {
    AfxMessageBox(_T("Delete All Items"));
}

// 编辑数据按钮
void CMainFrame::OnListEdit() {
    AfxMessageBox(_T("Edit Item"));
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 队列选项卡时间处理

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 堆栈选项卡时间处理

//////////////////////////////////////////////////////////////////////////



