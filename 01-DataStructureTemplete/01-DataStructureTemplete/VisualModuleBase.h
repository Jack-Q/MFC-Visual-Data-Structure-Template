#pragma once
class VisualModuleBase/*:public CWnd*/ {
public:
    VisualModuleBase();
    virtual ~VisualModuleBase();
    //Draw the view
    virtual void Draw(Graphics &g, CRect &rect) = 0;
protected:
    CAnimationController m_AnimationController;
public:
    virtual BOOL CheckClose();
    virtual void OnClose();
    virtual void OnShow() = 0;
};

