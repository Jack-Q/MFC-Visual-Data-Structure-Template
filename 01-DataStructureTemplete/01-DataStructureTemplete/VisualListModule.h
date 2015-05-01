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
private:
    // �������ݳ�Ա
    VisualListHeadNode m_listHead;
    VisualListNullNode m_listTail;
    INT_PTR m_listSize;
    // ��ͼ״̬�����塢���ʡ���ɫ��
    
    // ��ͼ����
    Bitmap m_bmpBackground;
    Bitmap m_bmpNodeBase;
public:
    // ���ݳ�Ա��ȡ
    INT_PTR GetSize();
    VisualListNodeBase &operator[](INT_PTR index);
    // ��ͼ����
private:
    void DrawBackground(Graphics & g, CRect &rect);
    
};

