#include "stdafx.h"
#pragma once
class VisualModuleBase/*:public CWnd*/ {
public:
    VisualModuleBase();
    virtual ~VisualModuleBase();
    //Draw the view
    virtual void Draw(Graphics &g, CRect &rect) = 0;
public:
    virtual BOOL CheckClose();
    virtual void OnClose();
    virtual void OnShow() = 0;
    virtual void OnContextMenu(CWnd* pWnd, CPoint point) {
    }
    virtual void OnLButtonDblClk(CWnd* pWnd, CPoint point) {
    }
};

