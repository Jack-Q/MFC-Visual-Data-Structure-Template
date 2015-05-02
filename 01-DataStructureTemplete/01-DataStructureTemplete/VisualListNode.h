#pragma once
#include "stdafx.h"
#include "01-DataStructureTemplete.h"
#include "VisualListNodeBase.h"
class VisualListNode :
    public VisualListNodeBase {
public:
    VisualListNode();
    virtual ~VisualListNode();
    virtual void draw(Graphics & g, INT top, INT left, INT index, Gdiplus::Font &  fntNodeTitle, Gdiplus::Font &  fntNodeContent);
    void SetContent(CString content);
    CString GetContent();

private:
    CString m_strContent;
};

