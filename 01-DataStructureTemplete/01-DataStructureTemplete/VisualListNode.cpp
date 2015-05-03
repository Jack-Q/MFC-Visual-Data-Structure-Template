#include "stdafx.h"
#include "VisualListNode.h"


VisualListNode::VisualListNode() :m_strContent(_T("")) {
}


VisualListNode::~VisualListNode() {
}

void VisualListNode::draw(Graphics & g, INT left, INT top, INT index, Gdiplus::Font &  fntNodeTitle, Gdiplus::Font & fntNodeContent) {
    //Outer box
    Rect nodebox(left + 5, top + 5, DW_NODE_WIDTH - 10, DW_NODE_HEIGHT - 10);
    LinearGradientBrush linearBrush(nodebox, Color(50, 160, 160, 160), Color(80, 160, 160, 160), 45);
    g.FillRectangle(&linearBrush, nodebox);

    //Inner box
    Rect innerbox(left + 10, top + 10, DW_NODE_WIDTH - 20, DW_NODE_HEIGHT - 20);
    LinearGradientBrush innerLinearBrush(innerbox, Color(60, 30, 110, 220), Color(80, 30, 110, 220), 45);
    g.FillRectangle(&innerLinearBrush, innerbox);

    //Index indicator
    g.FillEllipse(&SolidBrush(Color(80, 220, 190, 70)), left, top, 34, 34);
    g.FillEllipse(&SolidBrush(Color(220, 190, 70)), left + 2, top + 2, 30, 30);

    //Index Text
    CString str;
    str.Format(_T("%d"), index);
    g.DrawString(str, str.GetLength(), &fntNodeTitle, PointF(left + 17.0 - str.GetLength() * 9, top + 4.0), &SolidBrush(Color(20, 50, 80)));

    //Content Text
    // 获取可容纳的最长的字符串
   INT len = 6; PointF p; RectF r;
    if (m_strContent.GetLength() <= 7) {
        str = m_strContent;
    }
    else {
        do {
            g.MeasureString(m_strContent, len++, &fntNodeContent, p, &r);
        } while (len < m_strContent.GetLength() && r.Width < DW_NODE_WIDTH - 85);
        if (len < m_strContent.GetLength()) {
            str.Format(_T("%s..."), m_strContent.Mid(0, len));
        }
        else {
            str = m_strContent;
        }
    }
    g.MeasureString(str, str.GetLength(), &fntNodeContent, p, &r);
    g.DrawString(str, str.GetLength(), &fntNodeContent, PointF(left + 105.0 - r.Width / 2, top + 23.0), &SolidBrush(Color(20, 50, 80)));
}

void VisualListNode::SetContent(CString content) {
    m_strContent = content;

}

CString VisualListNode::GetContent() {
    return m_strContent;
}
