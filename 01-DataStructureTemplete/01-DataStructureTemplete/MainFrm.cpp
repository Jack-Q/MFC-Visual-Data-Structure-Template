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
    // ����ѡ�������
    ON_COMMAND(ID_LIST_ADD, &CMainFrame::OnListAdd)
    ON_COMMAND(ID_LIST_ADD_POSITION, &CMainFrame::OnListAddPosition)
    ON_COMMAND(ID_LIST_ADD_DATA, &CMainFrame::OnListAddData)
    ON_COMMAND(ID_LIST_DELETE_ALL, &CMainFrame::OnListDeleteAll)
    ON_COMMAND(ID_LIST_EDIT, &CMainFrame::OnListEdit)
    ON_COMMAND(ID_LIST_CLOSE, &CMainFrame::OnListClose)
    ON_COMMAND(ID_LIST_LINKED, &CMainFrame::OnListLinked)
    ON_UPDATE_COMMAND_UI(ID_LIST_LINKED, &CMainFrame::OnUpdateListLinked)
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame()
    : m_mdlDefaultModule(NULL),
    m_mdlListModule(NULL),
    m_wndView(this) {
    theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_WINDOWS_7);
    //Ĭ�ϲ�ѡ�����ݽṹ
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

    // ����һ����ͼ��ռ�ÿ�ܵĹ�����
    if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL)) {
        TRACE0("δ�ܴ�����ͼ����\n");
        return -1;
    }

    m_wndRibbonBar.Create(this);
    m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

    //��ʼ�����ݽṹѡ��˵�Ϊ��ѡ��
    m_gallery = (CMFCRibbonGallery *) m_wndRibbonBar.FindByID(ID_GALLERY_DATA_STRUCTURE);
    m_gallery->SelectItem(-1);
    m_gallery->SetItemToolTip(0, _T("����"));
    m_gallery->SetItemToolTip(1, _T("����"));
    m_gallery->SetItemToolTip(2, _T("��ջ"));

    //��ʼ��Ĭ��ҳ�����ģ�岢����Ϊ��ǰģ��
    m_selectedModule = m_mdlDefaultModule = new VisualDefaultModule();

    if (!m_wndStatusBar.Create(this)) {
        TRACE0("δ�ܴ���״̬��\n");
        return -1;      // δ�ܴ���
    }

    CString strTitlePane1;
    CString strTitlePane2;
    bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
    ASSERT(bNameValid);
    bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
    ASSERT(bNameValid);
    m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
    m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

    // ���� Visual Studio 2005 ��ʽͣ��������Ϊ
    CDockingManager::SetDockingMode(DT_SMART);
    // ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
    EnableAutoHidePanes(CBRS_ALIGN_ANY);

    // ����������: 
    if (!CreateCaptionBar()) {
        TRACE0("δ�ܴ���������\n");
        return -1;      // δ�ܴ���
    }
    // ���ڳ־�ֵ�����Ӿ�����������ʽ
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
    //m_wndRibbonBar.SetWindows7Look(TRUE);

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) {
    if (!CFrameWndEx::PreCreateWindow(cs))
        return FALSE;
    // TODO:  �ڴ˴�ͨ���޸�
    //  CREATESTRUCT cs ���޸Ĵ��������ʽ
    cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
    cs.lpszClass = AfxRegisterWndClass(0);
    return TRUE;
}

BOOL CMainFrame::CreateCaptionBar() {
    if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE)) {
        TRACE0("δ�ܴ���������\n");
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

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const {
    CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const {
    CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/) {
    // ������ǰ�Ƶ���ͼ����
    m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) {
    // ����ͼ��һ�γ��Ը�����
    if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
        return TRUE;

    // ����ִ��Ĭ�ϴ���
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
    // ���ݽṹ�����л�������л�����ֹ�������GalleryButtonΪ��ǰѡ��
    if (OnDataStructureChange(m_gallery->GetSelectedItem())) {
        m_selectedDataType = m_gallery->GetSelectedItem();
    }
    else {
        m_gallery->SelectItem(m_selectedDataType);
    }
    m_wndRibbonBar.RecalcLayout();
}

void CMainFrame::OnSetDefaultModule() {
    // �ر����ݽṹģ�飬������ʾ��ӭҳ��
    // Ĭ��ҳ���idΪ-1
    if (OnDataStructureChange(-1)) {
        m_selectedDataType = m_gallery->GetSelectedItem();
        m_selectedDataType = -1;
        m_gallery->SelectItem(-1);
        m_wndRibbonBar.RecalcLayout();
    }

}

void CMainFrame::OnUpdateGalleryDataStructure(CCmdUI *pCmdUI) {
}

BOOL CMainFrame::OnDataStructureChange(int p_iItemToChange) {
    //���л�����ͬ��ģ�飬��ֱ�ӷ���TRUE
    if (p_iItemToChange == m_selectedDataType) {
        return TRUE;
    }
    //�л�ǰ�ȼ���Ƿ�����л�
    if (!m_selectedModule->CheckClose()) {
        return FALSE;
    }

    VisualModuleBase *newModule = NULL;

    //������ģ��
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
            AfxMessageBox(_T("����ģ����δ���"));
            //m_wndRibbonBar.HideAllContextCategories();
            //m_wndRibbonBar.ShowContextCategories(ID_QUEUE_CONTEXT, TRUE);
            //m_wndRibbonBar.ActivateContextCategory(ID_QUEUE_CONTEXT);
            //newModule = ?
            break;
        case 2://Stack
            AfxMessageBox(_T("��ջģ����δ���"));
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

    //�ر�ԭ��ģ�飬��������ģ��
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
// ����ѡ��¼�����

// ���ý�Ҫ�����������ݵ�λ�������
void CMainFrame::OnListAddPosition() {
    // CMFCRibbonEdit *edit = (CMFCRibbonEdit *) m_wndRibbonBar.FindByID(ID_LIST_ADD_POSITION);
    // AfxMessageBox(edit->GetEditText() + _T(" Entered "));
}

// ���ý������������������
void CMainFrame::OnListAddData() {
    // CMFCRibbonEdit *edit = (CMFCRibbonEdit *) m_wndRibbonBar.FindByID(ID_LIST_ADD_DATA);
    // AfxMessageBox(edit->GetEditText() + _T(" Entered "));
}

// ������ݰ�ť
void CMainFrame::OnListAdd() {
    CMFCRibbonEdit *editPosition = (CMFCRibbonEdit *) m_wndRibbonBar.FindByID(ID_LIST_ADD_POSITION);
    CMFCRibbonEdit *editData = (CMFCRibbonEdit *) m_wndRibbonBar.FindByID(ID_LIST_ADD_DATA);

    INT_PTR position = _ttoi(editPosition->GetEditText());
    CString data = editData->GetEditText();

    INT_PTR size = m_mdlListModule->GetSize();
    if (position >= 0 && position <= size) {
        if (m_mdlListModule->InsertNode(position, data) != -1) {
            AfxMessageBox(_T("�ڵ����ɹ�"), MB_ICONINFORMATION);
            Invalidate();
        }
        else {
            AfxMessageBox(_T("�ڵ����ʧ��"), MB_ICONSTOP);
        }
    }
    else {
        if (size) {
            CString prompt;
            prompt.Format(_T("�޷���ָ����λ�ò���ڵ㣬��ǰ��������%d��Ԫ�أ��ڵ�λ�õ�ȡֵӦΪ0-%d"), size, size);
            AfxMessageBox(prompt);
        }
        else {
            AfxMessageBox(_T("��ǰ������û��Ԫ�أ��ڵ�λ�õ�ȡֵֻ��Ϊ0��"));
            editPosition->SetEditText(_T("0"));
        }
    }

}

// ɾ��ȫ�����ݰ�ť
void CMainFrame::OnListDeleteAll() {
    m_mdlListModule->DeleteAll();
    Invalidate();
}

// �༭���ݰ�ť
void CMainFrame::OnListEdit() {
    if (AfxMessageBox(_T("Edit Item")) != IDCANCEL) {
        Invalidate();
    }
}

// �ر�����ģʽ
void CMainFrame::OnListClose() {
    OnSetDefaultModule();
}

// �ı��������з�ʽ
void CMainFrame::OnListLinked() {
    m_mdlListModule->SetLinked(!m_mdlListModule->IsLinked());
    m_wndRibbonBar.GetParent()->Invalidate();
}

void CMainFrame::OnUpdateListLinked(CCmdUI *pCmdUI) {
    pCmdUI->SetCheck(m_mdlListModule->IsLinked());
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// ����ѡ�ʱ�䴦��

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// ��ջѡ�ʱ�䴦��

//////////////////////////////////////////////////////////////////////////




