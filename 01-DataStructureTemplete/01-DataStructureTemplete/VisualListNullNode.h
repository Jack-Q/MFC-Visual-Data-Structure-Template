#pragma once
#include "VisualListNodeBase.h"
class VisualListNullNode :
    public VisualListNodeBase {
public:
    VisualListNullNode();
    virtual ~VisualListNullNode();
    virtual void draw(Graphics & g, INT left,INT top,  INT index, Gdiplus::Font &  fntNodeTitle, Gdiplus::Font &  gntNodeContent);
    BOOL HasNext() {
        return FALSE;
    }
};

