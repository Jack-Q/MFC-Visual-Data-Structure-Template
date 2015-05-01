#pragma once
#include "VisualModuleBase.h"
class VisualListModule :
    public VisualModuleBase {
public:
    VisualListModule();
    virtual ~VisualListModule();
    virtual void draw(Graphics &g, CRect &rect);
    void OnShow();
};

