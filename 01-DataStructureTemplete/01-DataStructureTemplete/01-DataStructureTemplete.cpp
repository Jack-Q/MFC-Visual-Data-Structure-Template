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

// 01-DataStructureTemplete.cpp : 定义应用程序的类行为。
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


// CMy01DataStructureTempleteApp 构造

CMy01DataStructureTempleteApp::CMy01DataStructureTempleteApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO:  将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("QiaoBo.DataStructureTemplete.main.1.0"));

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CMy01DataStructureTempleteApp 对象

CMy01DataStructureTempleteApp theApp;


// CMy01DataStructureTempleteApp 初始化

BOOL CMy01DataStructureTempleteApp::InitInstance()
{
    //初始化GDI+
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_USEREX_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("QiaoBo"));


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 若要创建主窗口，此代码将创建新的框架窗口
	// 对象，然后将其设置为应用程序的主窗口对象
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 创建并加载框架及其资源
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);





	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CMy01DataStructureTempleteApp::ExitInstance()
{
	//TODO:  处理可能已添加的附加资源
	AfxOleTerm(FALSE);
    //释放GDI+资源
    GdiplusShutdown(m_gdiplusToken);
	return CWinAppEx::ExitInstance();
}

// CMy01DataStructureTempleteApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
    ~CAboutDlg();
// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

    // TODO:  在此添加额外的初始化
    m_FontList.CreatePointFont(100, _T("Microsoft Yahei UI"));
    m_information_list.SetFont(&m_FontList, 0);
    CString str;
    COleDateTime time;
    time.ParseDateTime(_T(__DATE__)_T(" ")_T(__TIME__));
    time.Format(_T(""));
    str.Format(_T("\n版本：1.0\n")
        _T("完成日期：%s\n")
        _T("编译时间：%s\n")
        _T("制作：乔波\n")
        _T("学号：2141601066\n")
        _T("班级：软件44"), time.Format(L"%Y-%m-%d"), time.Format(L"%Y-%m-%d %H:%M:%S"));
    m_information_list.SetWindowTextW(str);

    m_FontTitle.CreatePointFont(180, _T("Microsoft Yahei UI"));
    m_StaticTitle.SetFont(&m_FontTitle, 0);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CMy01DataStructureTempleteApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

// CMy01DataStructureTempleteApp 自定义加载/保存方法

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

// CMy01DataStructureTempleteApp 消息处理程序


void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point) {
    // TODO:  在此添加消息处理程序代码和/或调用默认值
    CDialogEx::OnOK();
    CDialogEx::OnLButtonDown(nFlags, point);
}
