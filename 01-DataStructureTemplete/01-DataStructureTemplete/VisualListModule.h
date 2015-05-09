#pragma once
#include "VisualModuleBase.h"
#include "VisualListHeadNode.h"
#include "VisualListNode.h"
#include "VisualListNullNode.h"

class VisualListModule :
    public VisualModuleBase {
public:
    VisualListModule();
    ~VisualListModule();
    void Draw(Graphics &g, CRect &rect);
    void OnShow();
    void OnContextMenu(CWnd* pWnd, CPoint point);
    void OnLButtonDblClk(CWnd* pWnd, CPoint point);
    
    // ����ѡ��ӿ�
    void SetLinked(BOOL isLinked);
    BOOL IsLinked();
    void SetDoubled(BOOL isDoubled);
    BOOL IsDoubled();
    void SetIndexed(BOOL isIndexed);
    BOOL IsIndexed();
    void SetStartFromZero(BOOL isStartFromZero);
    BOOL IsStartFromZero();
    
private:
    // ����ѡ��
    BOOL m_linked = TRUE;
    BOOL m_doubled = TRUE;
    BOOL m_indexed = TRUE;
    BOOL m_startFromZero = TRUE;

    // �������ݳ�Ա
    VisualListHeadNode m_listHead;
    VisualListNullNode m_listTail;
    INT_PTR m_listSize;

    // ��ͼ״̬�����塢���ʡ���ɫ��
    Gdiplus::Font m_fntTitle;           // ���������ֺ�
    Gdiplus::Font m_fntNodeTitle;       // �ڵ����
    Gdiplus::Font m_fntNodeContent;     // �ڵ�����
    Gdiplus::Font m_fntNullTip;         // ��������ʾ


    // ��ͼ����
    Bitmap m_bmpBackground;
    Bitmap m_bmpNodeBase;

    // ��ͼ����
    const INT DW_NODE_WIDTH = 200; //�ڵ���
    const INT DW_NODE_HEIGHT = 70; // �ڵ�߶�
    const INT DW_TITLE_HEIGHT = 80; // ����߶�
    const INT DW_PRIMARY_PADDING = 10; //Ĭ���ڱ߾�
    const INT DW_PRIMARY_MARGIN = 10; //Ĭ����߾�
    INT m_iDrawWidth = 0;
    INT m_iDrawHeight = 0;

    // ��ͼ����
    void DrawBackground(Graphics & g, CRect &rect);
    void DrawNullTip(Graphics & g, CRect &rect);
    void DrawNodes(Graphics & g, CRect &rect);
    GraphicsPath *GetDrawArrow(Point pt, BOOL direction, GraphicsPath *arr);
    Point GetNodePosition(INT_PTR index);
    BOOL IsNodeReversed(INT_PTR index) {
        
    }
    // ��ͼ���
    INT_PTR CheckPointOnID(Point point);
public:
    // ���ݳ�Ա��ȡ
    INT_PTR GetSize();
    VisualListNodeBase &GetIndex(INT_PTR index);
    VisualListNodeBase &operator[](INT_PTR index);
    // ���ݳ�Ա�����
    INT_PTR InsertNode(INT_PTR position, CString content);
    // ���ݳ�Ա��ɾ��
    BOOL DeleteAt(INT_PTR index, BOOL Confirmation = TRUE);
    BOOL DeleteAll(BOOL Confirmation = TRUE);
    // ���ݳ�Ա���޸�
    void EditAt(INT_PTR index, CWnd *parWnd = NULL);
};

