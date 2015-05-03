#pragma once
class CMainFrame;

// CChildView 窗口

class CChildView : public CWnd {
    // 构造
public:
    CChildView(CMainFrame* mainframe);

    // 特性
public:
    CAnimationController m_AnimationController;
    //void OnChangeAnimationGroups();
    // 重写
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

    // 实现
public:
    virtual ~CChildView();

    // 生成的消息映射函数
protected:
    afx_msg void OnPaint();
    DECLARE_MESSAGE_MAP()
    CMainFrame *m_mainFrame;

public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

