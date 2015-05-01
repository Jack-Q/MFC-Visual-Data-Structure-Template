#include "stdafx.h"
#include "VisualDefaultModule.h"
#include "01-DataStructureTemplete.h"


VisualDefaultModule::VisualDefaultModule()
{
}


VisualDefaultModule::~VisualDefaultModule()
{
}

void VisualDefaultModule::Draw(Graphics &g,CRect &rect) {

    CGdiPlusBitmapResource *bitmap = new CGdiPlusBitmapResource();
    bitmap->Load(IDB_WELCOME_BACKGROUND, _T("PNG"));
    g.Clear(Color(240, 245, 250));
    g.DrawImage(bitmap->m_pBitmap, rect.right / 2 - 290, rect.bottom / 2 - 150, 580, 300);
    delete bitmap;
}

void VisualDefaultModule::OnShow() {
}
