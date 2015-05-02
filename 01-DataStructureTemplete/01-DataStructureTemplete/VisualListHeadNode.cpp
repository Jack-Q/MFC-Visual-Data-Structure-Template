#include "stdafx.h"
#include "VisualListHeadNode.h"


VisualListHeadNode::VisualListHeadNode() {
}


VisualListHeadNode::~VisualListHeadNode() {
}

void VisualListHeadNode::draw(Graphics & g, INT top, INT left, INT index, Gdiplus::Font  & fntNodeTitle, Gdiplus::Font  & fntNodeContent) {
    //Outer box
    Rect nodebox(left + 5, top + 5, DW_NODE_WIDTH - 10, DW_NODE_HEIGHT - 10);
    LinearGradientBrush linearBrush(nodebox, Color(50, 160, 160, 160), Color(80, 160, 160, 160), 45);
    g.FillRectangle(&linearBrush, nodebox);

    //Inner box
    Rect innerbox(left + 10, top + 10, DW_NODE_WIDTH - 20, DW_NODE_HEIGHT - 20);
    LinearGradientBrush innerLinearBrush(innerbox, Color(60, 30, 110, 220), Color(80, 30, 110, 220), 45);
    g.FillRectangle(&innerLinearBrush, innerbox);

    //Content Text
    CString str;
    str.Format(_T("Á´±íÆðÊ¼"));
    g.DrawString(str, str.GetLength(), &fntNodeContent, PointF(left + 20.0, top + 25.0), &SolidBrush(Color(20, 50, 80)));
}
