#pragma once
#include "VisualListNodeBase.h"
class VisualListNullNode :
    public VisualListNodeBase {
public:
    VisualListNullNode();
    virtual ~VisualListNullNode();
    virtual void draw(Graphics & g, INT top, INT left, INT index, Gdiplus::Font &  fntNodeTitle, Gdiplus::Font &  gntNodeContent);
    BOOL HasNext() {
        return FALSE;
    }
};

