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

// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "01-DataStructureTemplete.h"
#include "ChildView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView(CMainFrame *mainFrame) {
    m_mainFrame = mainFrame;
}

CChildView::~CChildView() {
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) {
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	//清除可能的3D边框
	cs.dwExStyle &= ~WS_EX_WINDOWEDGE & ~WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

void CChildView::OnPaint() {

	CPaintDC dc(this); // 用于绘制的设备上下文
	Graphics g(dc);         // Get GDI+ Interface
    g.SetCompositingQuality(CompositingQualityGammaCorrected);
    g.SetSmoothingMode(SmoothingModeHighQuality);
    g.SetTextRenderingHint(TextRenderingHintAntiAlias);
    //获取窗口
    CRect rect;
    GetClientRect(&rect);
    //传递绘图接口和视窗大小至当前的模块进行界面UI的绘制
    m_mainFrame->m_selectedModule->Draw(g,rect);
}


