#include "stdafx.h"
#include "VisualListModule.h"
#include "01-DataStructureTemplete.h"


VisualListModule::VisualListModule()
    :m_bmpBackground(400, 300),
    m_bmpNodeBase(150, 50)
{
    m_listSize = 0;
    m_listHead.SetNext(&m_listTail);
    m_listTail.SetPrev(&m_listHead);
}


VisualListModule::~VisualListModule() {
}

void VisualListModule::Draw(Graphics &g, CRect &rect) {
    DrawBackground(g, rect);
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
    g.DrawString(_T("首元素"), 3, &Gdiplus::Font(_T("Microsoft Yahei"), 12), PointF(left + 25.0, top + 8.0), &SolidBrush(Color(20, 50, 80)));

}

// 获取当前链表的节点数量
INT_PTR VisualListModule::GetSize() {
    return m_listSize;
}

// 通过下表操作符获取指定的节点
VisualListNodeBase & VisualListModule::operator[](INT_PTR index) {
    return m_listHead;
}


void VisualListModule::DrawBackground(Graphics & g, CRect &rect) {
    g.Clear(Color(240, 245, 250));
    g.DrawString(_T("链表"), 2, &Gdiplus::Font(_T("Microsoft Yahei UI"), 30), PointF(20.0, 10.0), &SolidBrush(Color(0, 50, 220)));
    g.DrawLine(&Pen(&LinearGradientBrush(Point(0, 0), Point(400, 0), Color(255, 50, 130, 220), Color(0, 30, 220, 200)), 4.0F), Point(0, 75), Point(400, 75));
}
