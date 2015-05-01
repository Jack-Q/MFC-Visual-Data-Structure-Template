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
    // 储存数据成员
    VisualListHeadNode m_listHead;
    VisualListNullNode m_listTail;
    INT_PTR m_listSize;
    // 绘图状态、字体、画笔、颜色等
    
    // 绘图缓存
    Bitmap m_bmpBackground;
    Bitmap m_bmpNodeBase;
public:
    // 数据成员获取
    INT_PTR GetSize();
    VisualListNodeBase &operator[](INT_PTR index);
    // 绘图操作
private:
    void DrawBackground(Graphics & g, CRect &rect);
    
};

