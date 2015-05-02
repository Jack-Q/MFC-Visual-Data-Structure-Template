#include "stdafx.h"
#include "VisualListModule.h"
#include "01-DataStructureTemplete.h"


VisualListModule::VisualListModule()
    :m_bmpBackground(400, 300),
    m_bmpNodeBase(150, 50),
    // 初始化链表绘图状态、字体、画笔、颜色等
    m_fntTitle(_T("Microsoft Yahei UI"), 30),
    m_fntNodeTitle(_T("Microsoft Yahei UI"), 15),
    m_fntNodeContent(_T("Microsoft Yahei UI"), 15),
    m_fntNullTip(_T("Microsoft Yahei UI"), 40) {
    // 初始化链表数据
    m_listSize = 0;
    m_listHead.SetNext(&m_listTail);
    m_listTail.SetPrev(&m_listHead);
}


VisualListModule::~VisualListModule() {

}

INT_PTR VisualListModule::InsertNode(INT_PTR position, CString content) {
    VisualListNodeBase *prev, *next, *cur;
    if (position == 0) {
        prev = &m_listHead;
    }
    else {
        prev = &(*this)[position - 1];
    }
    next = prev->GetNext();

    cur = new VisualListNode();
    cur->SetNext(next);
    prev->SetNext(cur);
    cur->SetPrev(prev);
    next->SetPrev(prev);

    cur->SetContent(content);

    m_listSize++;

    return position;
}

BOOL VisualListModule::DeleteAt(INT_PTR index, BOOL Confirmation /*= TRUE*/) {
    VisualListNodeBase &cur = GetIndex(index);
    if (Confirmation) {
        CString str;
        str.Format(_T("确定要删除节点%d(内容为%s)吗？"), index, cur.GetContent());
        if (AfxMessageBox(str, MB_OKCANCEL | MB_ICONWARNING) == IDCANCEL) {
            // 用户取消了操作。
            return FALSE;
        }
    }
    cur.GetNext()->SetPrev(cur.GetPrev());
    cur.GetPrev()->SetNext(cur.GetNext());
    m_listSize--;
    delete &cur;
    return TRUE;
}

BOOL VisualListModule::DeleteAll(BOOL Confirmation /*= TRUE*/) {
    if (Confirmation) {
        if (AfxMessageBox(_T("确定要删除所有节点吗？"), MB_OKCANCEL | MB_ICONWARNING) == IDCANCEL) {
            // 用户取消了操作。
            return FALSE;
        }
    }
    while (m_listSize) {
        DeleteAt(0, FALSE);
    }
    return TRUE;
}

void VisualListModule::Draw(Graphics &g, CRect &rect) {
    DrawBackground(g, rect);
    if (m_listSize == 0) {
        DrawNullTip(g, rect);
        return;
    }
    DrawNodes(g, rect);
}


void VisualListModule::OnShow() {

}

void VisualListModule::OnContextMenu(CWnd* pWnd, CPoint point) {
    INT_PTR index = CheckPointOnID(point);

    // 当前光标未位于任一节点上
    if (index == -2) {
        return;
    }

    // 当前光标位于起始节点上
    if (index == -1) {
        return;
    }

    // 当前光标位于终止节点上
    if (index == m_listSize) {
        return;
    }

    // 当前光标位于普通节点上

    CMenu cMenu;
    cMenu.LoadMenuW(IDR_LIST_NODE_CONTEXT);
    UINT action = theApp.GetContextMenuManager()->TrackPopupMenu(cMenu, point.x, point.y, pWnd);
    if (!action) {
        return;
    }
    switch (action) {
        case ID_LIST_NODE_DELETE:
            //删除当前节点
            break;
        case ID_LIST_NODE_EDITVALUE:
            //编辑当前节点
            break;
        default:
            //未选择有效操作
            break;
    }
}

// 获取当前链表的节点数量
INT_PTR VisualListModule::GetSize() {
    return m_listSize;
}

VisualListNodeBase & VisualListModule::GetIndex(INT_PTR index) {
    return this->operator[](index);
}

// 通过下表操作符获取指定的节点
VisualListNodeBase & VisualListModule::operator[](INT_PTR index) {
    ASSERT(index >= 0 && index <= m_listSize);
    VisualListNodeBase *node = &m_listHead;
    for (INT_PTR i = 0; i <= index; i++) {
        ASSERT(node->HasNext());
        node = node->GetNext();
    }
    return *node;
}


void VisualListModule::DrawBackground(Graphics & g, CRect &rect) {
    g.Clear(Color(240, 245, 250));
    g.DrawString(_T("链表"), 2, &m_fntTitle, PointF(20.0, 10.0), &SolidBrush(Color(0, 50, 220)));
    g.DrawLine(&Pen(&LinearGradientBrush(Point(0, 0), Point(400, 0), Color(255, 50, 130, 220), Color(0, 30, 220, 200)), 4.0F), Point(0, 75), Point(400, 75));
}

void VisualListModule::DrawNullTip(Graphics & g, CRect &rect) {
    INT width = rect.Width();
    INT height = rect.Height();
    Pen pen(&SolidBrush(Color(220, 180, 40)), 10);
    Point points[5] = {
        Point(width / 2 - 200, height / 2),
        Point(width / 2, height / 2 - 120),
        Point(width / 2 + 200, height / 2),
        Point(width / 2, height / 2 + 120),
        Point(width / 2 - 200, height / 2)
    };
    g.DrawRectangle(&pen, Rect(width / 2 - 200, height / 2 - 120, 400, 240));
    // g.DrawCurve(&pen, points, 5);
    CString tip = _T("请在上方的选项\n 卡中输入数据");
    g.DrawString(tip.GetString(), tip.GetLength(), &m_fntNullTip, PointF(width / 2.0 - 200, height / 2.0 - 80), &SolidBrush(Color(255, 210, 30)));

}

void VisualListModule::DrawNodes(Graphics & g, CRect &rect) {
    VisualListNodeBase *node = &m_listHead;
    m_iDrawHeight = rect.Height();
    m_iDrawWidth = rect.Width();

    int i = 1;
    Point ptCur, ptPre, ptNxt;
    // 绘制起始节点
    //TODO: Continue Here
    ptPre = GetNodePosition(-1);
    node->draw(g, ptPre.Y, ptPre.X, 0, m_fntNodeTitle, m_fntNodeContent);
    node = node->GetNext();

    // 绘制中间结点
    while (node->HasNext()) {
        // 绘制当前节点
        g.DrawRectangle(&Pen(&SolidBrush(Color(0, 0, 0)), 2), DW_NODE_WIDTH*1.1*i, DW_NODE_HEIGHT + 300, DW_NODE_WIDTH, DW_NODE_HEIGHT);
        node->draw(g, DW_NODE_HEIGHT + 200, DW_NODE_WIDTH*1.1*i, i - 1, m_fntNodeTitle, m_fntNodeContent);
        i++;
        node = node->GetNext();
        // 绘制前一节点与当前节点
    }

    // 绘制终止节点
    node->draw(g, DW_NODE_HEIGHT + 200, DW_NODE_WIDTH*1.1*i, 0, m_fntNodeTitle, m_fntNodeContent);
}

INT_PTR VisualListModule::CheckPointOnID(CPoint point) {
    return -2;
}

