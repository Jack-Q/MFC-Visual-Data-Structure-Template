#pragma once
class CMainFrame;

// CChildView ����

class CChildView : public CWnd {
    // ����
public:
    CChildView(CMainFrame* mainframe);

    // ����
public:
    CAnimationController m_AnimationController;
    //void OnChangeAnimationGroups();
    // ��д
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

    // ʵ��
public:
    virtual ~CChildView();

    // ���ɵ���Ϣӳ�亯��
protected:
    afx_msg void OnPaint();
    DECLARE_MESSAGE_MAP()
    CMainFrame *m_mainFrame;

public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

