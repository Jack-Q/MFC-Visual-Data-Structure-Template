// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// 01-DataStructureTemplete.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "01-DataStructureTemplete.h"
#include "MainFrm.h"
#include "afxwin.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy01DataStructureTempleteApp

BEGIN_MESSAGE_MAP(CMy01DataStructureTempleteApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMy01DataStructureTempleteApp::OnAppAbout)
END_MESSAGE_MAP()


// CMy01DataStructureTempleteApp ����

CMy01DataStructureTempleteApp::CMy01DataStructureTempleteApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���: 
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO:  ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("QiaoBo.DataStructureTemplete.main.1.0"));

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CMy01DataStructureTempleteApp ����

CMy01DataStructureTempleteApp theApp;


// CMy01DataStructureTempleteApp ��ʼ��

BOOL CMy01DataStructureTempleteApp::InitInstance()
{
    //��ʼ��GDI+
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_USEREX_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("QiaoBo"));


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ��Ҫ���������ڣ��˴��뽫�����µĿ�ܴ���
	// ����Ȼ��������ΪӦ�ó���������ڶ���
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// ���������ؿ�ܼ�����Դ
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);





	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CMy01DataStructureTempleteApp::ExitInstance()
{
	//TODO:  �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);
    //�ͷ�GDI+��Դ
    GdiplusShutdown(m_gdiplusToken);
	return CWinAppEx::ExitInstance();
}

// CMy01DataStructureTempleteApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
    ~CAboutDlg();
// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
    CStatic m_information_list;
    virtual BOOL OnInitDialog();
    CStatic m_StaticTitle;
    CFont m_FontTitle;
    CFont m_FontList;
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD) {
}
CAboutDlg::~CAboutDlg() {
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_INFORMATION_LIST, m_information_list);
    DDX_Control(pDX, IDC_APPLICATION_TITLE, m_StaticTitle);
}


BOOL CAboutDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    m_FontList.CreatePointFont(100, _T("Microsoft Yahei UI"));
    m_information_list.SetFont(&m_FontList, 0);
    CString str;
    COleDateTime time;
    time.ParseDateTime(_T(__DATE__)_T(" ")_T(__TIME__));
    time.Format(_T(""));
    str.Format(_T("\n�汾��1.0\n")
        _T("������ڣ�%s\n")
        _T("����ʱ�䣺%s\n")
        _T("�������ǲ�\n")
        _T("ѧ�ţ�2141601066\n")
        _T("�༶�����44"), time.Format(L"%Y-%m-%d"), time.Format(L"%Y-%m-%d %H:%M:%S"));
    m_information_list.SetWindowTextW(str);

    m_FontTitle.CreatePointFont(180, _T("Microsoft Yahei UI"));
    m_StaticTitle.SetFont(&m_FontTitle, 0);
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣:  OCX ����ҳӦ���� FALSE
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CMy01DataStructureTempleteApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

// CMy01DataStructureTempleteApp �Զ������/���淽��

void CMy01DataStructureTempleteApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CMy01DataStructureTempleteApp::LoadCustomState()
{
}

void CMy01DataStructureTempleteApp::SaveCustomState()
{
}

// CMy01DataStructureTempleteApp ��Ϣ�������


void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point) {
    // TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
    CDialogEx::OnOK();
    CDialogEx::OnLButtonDown(nFlags, point);
}
