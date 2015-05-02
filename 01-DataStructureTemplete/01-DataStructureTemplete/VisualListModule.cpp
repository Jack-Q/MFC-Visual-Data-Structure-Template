#include "stdafx.h"
#include "VisualListModule.h"
#include "01-DataStructureTemplete.h"


VisualListModule::VisualListModule()
    :m_bmpBackground(400, 300),
    m_bmpNodeBase(150, 50),
    // ��ʼ�������ͼ״̬�����塢���ʡ���ɫ��
    m_fntTitle(_T("Microsoft Yahei UI"), 30),
    m_fntNodeTitle(_T("Microsoft Yahei UI"), 15),
    m_fntNodeContent(_T("Microsoft Yahei UI"), 15),
    m_fntNullTip(_T("Microsoft Yahei UI"), 40) {
    // ��ʼ����������
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
        str.Format(_T("ȷ��Ҫɾ���ڵ�%d(����Ϊ%s)��"), index, cur.GetContent());
        if (AfxMessageBox(str, MB_OKCANCEL | MB_ICONWARNING) == IDCANCEL) {
            // �û�ȡ���˲�����
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
        if (AfxMessageBox(_T("ȷ��Ҫɾ�����нڵ���"), MB_OKCANCEL | MB_ICONWARNING) == IDCANCEL) {
            // �û�ȡ���˲�����
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

    // ��ǰ���δλ����һ�ڵ���
    if (index == -2) {
        return;
    }

    // ��ǰ���λ����ʼ�ڵ���
    if (index == -1) {
        return;
    }

    // ��ǰ���λ����ֹ�ڵ���
    if (index == m_listSize) {
        return;
    }

    // ��ǰ���λ����ͨ�ڵ���

    CMenu cMenu;
    cMenu.LoadMenuW(IDR_LIST_NODE_CONTEXT);
    UINT action = theApp.GetContextMenuManager()->TrackPopupMenu(cMenu, point.x, point.y, pWnd);
    if (!action) {
        return;
    }
    switch (action) {
        case ID_LIST_NODE_DELETE:
            //ɾ����ǰ�ڵ�
            break;
        case ID_LIST_NODE_EDITVALUE:
            //�༭��ǰ�ڵ�
            break;
        default:
            //δѡ����Ч����
            break;
    }
}

// ��ȡ��ǰ����Ľڵ�����
INT_PTR VisualListModule::GetSize() {
    return m_listSize;
}

VisualListNodeBase & VisualListModule::GetIndex(INT_PTR index) {
    return this->operator[](index);
}

// ͨ���±��������ȡָ���Ľڵ�
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
    g.DrawString(_T("����"), 2, &m_fntTitle, PointF(20.0, 10.0), &SolidBrush(Color(0, 50, 220)));
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
    CString tip = _T("�����Ϸ���ѡ��\n ������������");
    g.DrawString(tip.GetString(), tip.GetLength(), &m_fntNullTip, PointF(width / 2.0 - 200, height / 2.0 - 80), &SolidBrush(Color(255, 210, 30)));

}

void VisualListModule::DrawNodes(Graphics & g, CRect &rect) {
    VisualListNodeBase *node = &m_listHead;
    m_iDrawHeight = rect.Height();
    m_iDrawWidth = rect.Width();

    int i = 1;
    Point ptCur, ptPre, ptNxt;
    // ������ʼ�ڵ�
    //TODO: Continue Here
    ptPre = GetNodePosition(-1);
    node->draw(g, ptPre.Y, ptPre.X, 0, m_fntNodeTitle, m_fntNodeContent);
    node = node->GetNext();

    // �����м���
    while (node->HasNext()) {
        // ���Ƶ�ǰ�ڵ�
        g.DrawRectangle(&Pen(&SolidBrush(Color(0, 0, 0)), 2), DW_NODE_WIDTH*1.1*i, DW_NODE_HEIGHT + 300, DW_NODE_WIDTH, DW_NODE_HEIGHT);
        node->draw(g, DW_NODE_HEIGHT + 200, DW_NODE_WIDTH*1.1*i, i - 1, m_fntNodeTitle, m_fntNodeContent);
        i++;
        node = node->GetNext();
        // ����ǰһ�ڵ��뵱ǰ�ڵ�
    }

    // ������ֹ�ڵ�
    node->draw(g, DW_NODE_HEIGHT + 200, DW_NODE_WIDTH*1.1*i, 0, m_fntNodeTitle, m_fntNodeContent);
}

INT_PTR VisualListModule::CheckPointOnID(CPoint point) {
    return -2;
}

