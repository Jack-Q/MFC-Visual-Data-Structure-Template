#pragma once
#include "VisualListNodeBase.h"
class VisualListHeadNode :
    public VisualListNodeBase {
public:
    VisualListHeadNode();
    ~VisualListHeadNode();
    virtual void draw(Graphics & g, INT left,INT top,  INT index, Gdiplus::Font &  fntNodeTitle, Gdiplus::Font &  fntNodeContent);
};

