#include "stdafx.h"
#include "VisualListModule.h"
#include "01-DataStructureTemplete.h"
#include "VisualListNodeEditor.h"

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

void VisualListModule::EditAt(INT_PTR index, CWnd *parWnd /*= NULL*/) {
    VisualListNodeEditor editor(GetIndex(index), parWnd);
    editor.DoModal();
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
    //point������Ϊ��Ļ���꣬��ת��Ϊ�����������м���
    CRect rect;
    pWnd->GetWindowRect(&rect);
    INT_PTR index = CheckPointOnID(Point(point.x - rect.left, point.y - rect.top));

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
            DeleteAt(index);
            pWnd->Invalidate();
            break;
        case ID_LIST_NODE_EDITVALUE:
            //�༭��ǰ�ڵ�
            EditAt(index, pWnd);
            pWnd->Invalidate();
            break;
        default:
            //δѡ����Ч����
            break;
    }
}

void VisualListModule::OnLButtonDblClk(CWnd* pWnd, CPoint point) {
    INT_PTR index = CheckPointOnID(Point(point.x, point.y));
    if (index >= 0 && index < m_listSize) {
        EditAt(index, pWnd);
        pWnd->Invalidate();
    }
}

void VisualListModule::SetLinked(BOOL isLinked) {
    //if (m_linked = isLinked) {
    //    return;
    //}
    m_linked = isLinked;
}

BOOL VisualListModule::IsLinked() {
    return m_linked;
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

// ���Ʊ��������⣬��ǰ�趨����߶�Ϊ80px
void VisualListModule::DrawBackground(Graphics & g, CRect &rect) {

    g.Clear(Color(240, 245, 250));
    g.DrawString(_T("����"), 2, &m_fntTitle, PointF(20.0, 10.0), &SolidBrush(Color(0, 50, 220)));
    g.DrawLine(
        &Pen(&LinearGradientBrush(Point(0, 0), Point(400, 0), Color(255, 50, 130, 220), Color(0, 30, 220, 200)), 4.0F),
        Point(0, 75),
        Point(400, 75));
    // ���Ʊ������ݲ�Ӧ����80px
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

    int i = -1;
    Point ptCur, ptPre, ptNxt;
    // ������ʼ�ڵ�
    ptCur = GetNodePosition(-1);
    node->draw(g, ptCur.X, ptCur.Y, i, m_fntNodeTitle, m_fntNodeContent);



    // �����м���
    Point ptFrom, ptTo, ptTmp1, ptTmp2, ptTmp3, ptTmp4;
    GraphicsPath path, arrow;

    SolidBrush brushToPrev(Color(220, 50, 255, 30));
    Pen penToPrev(&brushToPrev, 3);
    penToPrev.SetEndCap(LineCapRound);

    SolidBrush brushToNext(Color(220, 255, 120, 0));
    Pen penToNext(&brushToNext, 3);
    penToNext.SetEndCap(LineCapRound);
    do {
        i++;
        node = node->GetNext();
        ptPre = ptCur;
        ptCur = GetNodePosition(i);

        // ���Ƶ�ǰ�ڵ�
        node->draw(g,
            ptCur.X,
            ptCur.Y,
            i, m_fntNodeTitle, m_fntNodeContent);

        // ���Ƶ�ǰ�ڵ�ָ��ǰһ�ڵ�ļ�ͷ
        ptFrom = node->GetPointFromNext(ptCur);
        ptTo = node->GetPrev()->GetPointToPrev(ptPre);
        if (ptFrom.X > ptTo.X) {
            // ���ڵ���ͬһ����
            path.Reset();
            ptTmp1.X = ptFrom.X;
            ptTmp1.Y = ptTo.Y - 0.5*DW_PRIMARY_MARGIN;
            path.AddLine(ptFrom, ptTmp1);
            ptTmp2.X = ptFrom.X - 0.3 * DW_PRIMARY_MARGIN;
            ptTmp2.Y = ptTo.Y - 0.8*DW_PRIMARY_MARGIN;
            ptTmp3.X = ptTmp1.X;
            ptTmp3.Y = ptTmp2.Y;
            path.AddBezier(ptTmp1, ptTmp3, ptTmp3, ptTmp2);
            ptTmp1.X = ptTo.X + 0.3*DW_PRIMARY_MARGIN;
            ptTmp1.Y = ptTmp2.Y;
            path.AddLine(ptTmp2, ptTmp1);
            ptTmp2.X = ptTo.X;
            ptTmp2.Y = ptTo.Y - 0.5*DW_PRIMARY_MARGIN;
            ptTmp3.X = ptTmp2.X;
            ptTmp3.Y = ptTmp1.Y;
            path.AddBezier(ptTmp1, ptTmp3, ptTmp3, ptTmp2);
            path.AddLine(ptTmp2, ptTo);
            g.DrawPath(&penToPrev, &path);
            g.FillPath(&brushToPrev, GetDrawArrow(ptTo, FALSE, &arrow));

        }
        else {
            // �ڵ㷢���˻���
            path.Reset();
            ptTmp1.X = ptFrom.X;
            ptTmp1.Y = ptFrom.Y - 0.3*DW_PRIMARY_MARGIN;
            path.AddLine(ptFrom, ptTmp1);
            ptTmp2.X = ptFrom.X + 0.6 * DW_PRIMARY_MARGIN;
            ptTmp2.Y = ptFrom.Y - 0.9*DW_PRIMARY_MARGIN;
            ptTmp3.X = ptTmp1.X;
            ptTmp3.Y = ptTmp2.Y;
            path.AddBezier(ptTmp1, ptTmp3, ptTmp3, ptTmp2);
            ptTmp1.X = ptTo.X;
            ptTmp1.Y = ptTmp2.Y;
            path.AddLine(ptTmp2, ptTmp1);
            ptTmp2.X = ptTo.X;
            ptTmp2.Y = ptTo.Y;
            ptTmp3.X = ptTmp1.X + 70;
            ptTmp3.Y = ptTmp1.Y;
            ptTmp4.X = ptTmp2.X + 20;
            ptTmp4.Y = ptTmp2.Y - 40;
            path.AddBezier(ptTmp1, ptTmp3, ptTmp4, ptTmp2);
            path.AddLine(ptTmp2, ptTo);
            g.DrawPath(&penToPrev, &path);
            GetDrawArrow(ptTo, FALSE, &arrow);
            Matrix mat;
            mat.RotateAt(26.6, PointF(ptTo.X, ptTo.Y));
            arrow.Transform(&mat);
            g.FillPath(&brushToPrev, &arrow);
        }

        // ����ǰһ�ڵ�ָ��ǰ�ڵ�ļ�ͷ
        ptFrom = node->GetPrev()->GetPointToNext(ptPre);
        ptTo = node->GetPointFromPrev(ptCur);
        if (ptFrom.X < ptTo.X) {
            // ���ڵ���ͬһ����
            path.Reset();
            ptTmp1.X = ptFrom.X;
            ptTmp1.Y = ptTo.Y + 0.5*DW_PRIMARY_MARGIN;
            path.AddLine(ptFrom, ptTmp1);
            ptTmp2.X = ptFrom.X + 0.3 * DW_PRIMARY_MARGIN;
            ptTmp2.Y = ptTo.Y + 0.8*DW_PRIMARY_MARGIN;
            ptTmp3.X = ptTmp1.X;
            ptTmp3.Y = ptTmp2.Y;
            path.AddBezier(ptTmp1, ptTmp3, ptTmp3, ptTmp2);
            ptTmp1.X = ptTo.X - 0.3*DW_PRIMARY_MARGIN;
            ptTmp1.Y = ptTmp2.Y;
            path.AddLine(ptTmp2, ptTmp1);
            ptTmp2.X = ptTo.X;
            ptTmp2.Y = ptTo.Y + 0.5*DW_PRIMARY_MARGIN;
            ptTmp3.X = ptTmp2.X;
            ptTmp3.Y = ptTmp1.Y;
            path.AddBezier(ptTmp1, ptTmp3, ptTmp3, ptTmp2);
            path.AddLine(ptTmp2, ptTo);
            g.DrawPath(&penToNext, &path);
            g.FillPath(&brushToNext, GetDrawArrow(ptTo, TRUE, &arrow));
        }
        else {
            path.Reset();
            ptTmp1.X = ptFrom.X;
            ptTmp1.Y = ptFrom.Y + 0.7*DW_PRIMARY_MARGIN;
            path.AddLine(ptFrom, ptTmp1);
            ptTmp2.X = ptFrom.X - 0.6 * DW_PRIMARY_MARGIN;
            ptTmp2.Y = ptFrom.Y + 1.3*DW_PRIMARY_MARGIN;
            ptTmp3.X = ptTmp1.X;
            ptTmp3.Y = ptTmp2.Y;
            path.AddBezier(ptTmp1, ptTmp3, ptTmp3, ptTmp2);
            ptTmp1.X = ptTo.X;
            ptTmp1.Y = ptTmp2.Y;
            path.AddLine(ptTmp2, ptTmp1);
            ptTmp2.X = ptTo.X;
            ptTmp2.Y = ptTo.Y;
            ptTmp3.X = ptTmp1.X - 70;
            ptTmp3.Y = ptTmp1.Y;
            ptTmp4.X = ptTmp2.X - 20;
            ptTmp4.Y = ptTmp2.Y + 40;
            path.AddBezier(ptTmp1, ptTmp3, ptTmp4, ptTmp2);
            path.AddLine(ptTmp2, ptTo);
            g.DrawPath(&penToNext, &path);
            GetDrawArrow(ptTo, TRUE, &arrow);
            Matrix mat;
            mat.RotateAt(26.6, PointF(ptTo.X, ptTo.Y));
            arrow.Transform(&mat);
            g.FillPath(&brushToNext, &arrow);
        }

    } while (node->HasNext());
}

GraphicsPath * VisualListModule::GetDrawArrow(Point pt, BOOL direction, GraphicsPath *arr) {
    GraphicsPath &arrow = *arr;
    Point p, q;
    arrow.Reset();
    if (direction) {
        // Direction up
        pt.Y -= 5;
        p.X = pt.X - 0.6 * DW_PRIMARY_MARGIN;
        p.Y = pt.Y + 0.8 * DW_PRIMARY_MARGIN;
        arrow.AddLine(pt, p);
        q.X = pt.X;
        q.Y = pt.Y + 0.5 * DW_PRIMARY_MARGIN;
        arrow.AddLine(p, q);
        p.X = pt.X + 0.6 * DW_PRIMARY_MARGIN;
        p.Y = pt.Y + 0.8 * DW_PRIMARY_MARGIN;
        arrow.AddLine(q, p);
        arrow.AddLine(p, pt);

    }
    else {
        // Direction down
        pt.Y += 5;
        p.X = pt.X - 0.6 * DW_PRIMARY_MARGIN;
        p.Y = pt.Y - 0.8 * DW_PRIMARY_MARGIN;
        arrow.AddLine(pt, p);
        q.X = pt.X;
        q.Y = pt.Y - 0.5 * DW_PRIMARY_MARGIN;
        arrow.AddLine(p, q);
        p.X = pt.X + 0.6 * DW_PRIMARY_MARGIN;
        p.Y = pt.Y - 0.8 * DW_PRIMARY_MARGIN;
        arrow.AddLine(q, p);
        arrow.AddLine(p, pt);
    }
    return &arrow;
}

Point VisualListModule::GetNodePosition(INT_PTR index) {
    // index ��ȡֵӦΪ-1��listsize������-1λ��ʼ�ڵ�
    // listSizeΪ��ֹ�ڵ� 
    INT_PTR count = m_listSize + 2;
    INT countPerLine =
        (m_iDrawWidth + 2 * DW_PRIMARY_MARGIN - 2 * DW_PRIMARY_PADDING)
        / (DW_NODE_WIDTH + 2 * DW_PRIMARY_MARGIN);
    INT lines = (count + countPerLine - 1) / countPerLine; // ����ȡ��
    INT cliX = (m_iDrawWidth - countPerLine * (DW_NODE_WIDTH + DW_PRIMARY_MARGIN * 2)
        + 2 * DW_PRIMARY_MARGIN) / 2;
    INT cliY = DW_TITLE_HEIGHT + (m_iDrawHeight - DW_TITLE_HEIGHT
        - lines * (DW_NODE_HEIGHT + DW_PRIMARY_MARGIN * 2)
        + 2 * DW_PRIMARY_MARGIN) / 2;
    index += 1;
    INT lc = count % countPerLine;
    if (index + lc >= count) {
        cliX = (m_iDrawWidth - lc * (DW_NODE_WIDTH + DW_PRIMARY_MARGIN * 2)
            + 2 * DW_PRIMARY_MARGIN) / 2;
    }
    if (m_linked) {
        if (index / countPerLine % 2) {
            //Reverse
            if (index + lc >= count) {

                return Point(cliX + (lc - 1 - index % countPerLine) * (DW_NODE_WIDTH + DW_PRIMARY_MARGIN * 2),
                    cliY + (index / countPerLine) * (DW_NODE_HEIGHT + DW_PRIMARY_MARGIN * 2));
            }
            return Point(cliX + (countPerLine - 1 - index % countPerLine) * (DW_NODE_WIDTH + DW_PRIMARY_MARGIN * 2),
                cliY + (index / countPerLine) * (DW_NODE_HEIGHT + DW_PRIMARY_MARGIN * 2));
        }
        else {
            return Point(cliX + (index % countPerLine) * (DW_NODE_WIDTH + DW_PRIMARY_MARGIN * 2),
                cliY + (index / countPerLine) * (DW_NODE_HEIGHT + DW_PRIMARY_MARGIN * 2));

        }
    }
    else {
        // No reverse
        return Point(cliX + (index % countPerLine) * (DW_NODE_WIDTH + DW_PRIMARY_MARGIN * 2),
            cliY + (index / countPerLine) * (DW_NODE_HEIGHT + DW_PRIMARY_MARGIN * 2));
    }

}

INT_PTR VisualListModule::CheckPointOnID(Point point) {
    //return -2;
    for (INT_PTR i = -1; i <= m_listSize; i++) {
        Point p = GetNodePosition(i);
        if (point.X >= p.X && point.X <= p.X + DW_NODE_WIDTH
            && point.Y >= p.Y && point.Y <= p.Y + DW_NODE_HEIGHT) {
            return i;
        }
    }
    return -2;
}
