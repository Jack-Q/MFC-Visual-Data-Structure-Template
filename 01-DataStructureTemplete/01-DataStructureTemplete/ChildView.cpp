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

// ChildView.cpp : CChildView ���ʵ��
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



// CChildView ��Ϣ�������

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) {
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	//������ܵ�3D�߿�
	cs.dwExStyle &= ~WS_EX_WINDOWEDGE & ~WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

void CChildView::OnPaint() {

	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	Graphics g(dc);         // Get GDI+ Interface
    g.SetCompositingQuality(CompositingQualityGammaCorrected);
    g.SetSmoothingMode(SmoothingModeHighQuality);
    g.SetTextRenderingHint(TextRenderingHintAntiAlias);
    //��ȡ����
    CRect rect;
    GetClientRect(&rect);
    //���ݻ�ͼ�ӿں��Ӵ���С����ǰ��ģ����н���UI�Ļ���
    m_mainFrame->m_selectedModule->Draw(g,rect);
}


