#include "stdafx.h"
#include "VisualListModule.h"
#include "01-DataStructureTemplete.h"


VisualListModule::VisualListModule() {
}


VisualListModule::~VisualListModule() {
}

void VisualListModule::draw(Graphics &g, CRect &rect) {
    g.DrawString(_T("Á´±í"), 2, &Gdiplus::Font(_T("Microsoft Yahei UI"), 20), PointF(50.0, 50.0), &SolidBrush(Color(0, 50, 220)));
}


void VisualListModule::OnShow() {
}

// Draw Node Function
void /*CChildView::*/drawNode(Graphics &g, INT top, INT left) {
    //Outer box
    Rect nodebox(left, top, 150, 50);
    LinearGradientBrush linearBrush(nodebox, Color(50, 160, 160, 160), Color(80, 160, 160, 160), 45);
    g.FillRectangle(&linearBrush, nodebox);

    //Inner box
    Rect innerbox(left + 5, top + 5, 140, 40);
    LinearGradientBrush innerLinearBrush(innerbox, Color(60, 30, 110, 220), Color(80, 30, 110, 220), 45);
    g.FillRectangle(&innerLinearBrush, innerbox);

    //Index indecator
    g.FillEllipse(&SolidBrush(Color(80, 220, 190, 70)), left - 5, top - 5, 34, 34);
    g.FillEllipse(&SolidBrush(Color(220, 190, 70)), left - 3, top - 3, 30, 30);

    //Index Text
    g.DrawString(_T("1"), 1, &Gdiplus::Font(_T("Microsoft Yahei"), 15), PointF(left + 3.0, top + 0.0), &SolidBrush(Color(20, 50, 80)));

    //Content Text
    g.DrawString(_T("Ê×ÔªËØ"), 3, &Gdiplus::Font(_T("Microsoft Yahei"), 12), PointF(left + 25.0, top + 8.0), &SolidBrush(Color(20, 50, 80)));

}