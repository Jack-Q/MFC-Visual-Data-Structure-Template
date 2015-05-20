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
    m_AnimationController.EnableAnimationTimerEventHandler();
    m_AnimationController.EnablePriorityComparisonHandler(UI_ANIMATION_PHT_TRIM);
}

CChildView::~CChildView() {
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_CONTEXTMENU()
    ON_WM_LBUTTONDBLCLK()
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

    // 设置动画管理器相关窗口
    m_AnimationController.SetRelatedWnd(this);

	return TRUE;
}

void CChildView::OnPaint() {

	CPaintDC dc(this); // 用于绘制的设备上下文

    //获取窗口
    CRect rect;
    GetClientRect(&rect);

    /*
    * 建立双缓存避免绘制视图时的闪烁现象
    * 
    * 基本原理是在内存中新建一块兼容于当前设备上下文的虚拟设备
    * 然后为虚拟设备设置一块与当前视图区域大小相等的画布（Bitmap）
    * 之后将画布设置为虚拟设备上下文的操作对象
    * 
    * 完成上述初始化操作后对虚拟设备上下文进行绘图操作
    *
    * 最后将虚拟设备上下文通过BitBlt方法以 SRCCOPY 模式传递至当前可见的设备上下文
    */

    // 建立缓存设备上下文
    CDC dcMen;
    dcMen.CreateCompatibleDC(&dc);
    CBitmap bmp;
    bmp.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
    dcMen.SelectObject(bmp);

	Graphics g(dcMen);         // Get GDI+ Interface
    g.SetCompositingQuality(CompositingQualityGammaCorrected);
    g.SetSmoothingMode(SmoothingModeHighQuality);
    g.SetTextRenderingHint(TextRenderingHintAntiAlias);
    //传递绘图接口和视窗大小至当前的模块进行界面UI的绘制
    m_mainFrame->m_selectedModule->Draw(g,rect);

    //将缓存设备上下文输出至视图
    dc.BitBlt(0, 0, rect.Width(), rect.Height(), &dcMen, 0, 0, SRCCOPY);

}




BOOL CChildView::OnEraseBkgnd(CDC* pDC) {
    return TRUE /* CWnd::OnEraseBkgnd(pDC) */;
}


void CChildView::OnContextMenu(CWnd* pWnd, CPoint point) {
    m_mainFrame->m_selectedModule->OnContextMenu(pWnd,point);
}


void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point) {
    // TODO:  在此添加消息处理程序代码和/或调用默认值
    m_mainFrame->m_selectedModule->OnLButtonDblClk(this, point);
    CWnd::OnLButtonDblClk(nFlags, point);
}
