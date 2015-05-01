#pragma once
#include "VisualModuleBase.h"
class VisualDefaultModule :
	public VisualModuleBase
{
public:
	VisualDefaultModule();
	virtual ~VisualDefaultModule();
    void Draw(Graphics &g, CRect &rect);
    void OnShow();
};

