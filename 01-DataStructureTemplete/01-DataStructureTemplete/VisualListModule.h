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
private:
    // 储存数据成员
    VisualListHeadNode m_listHead;
    VisualListNullNode m_listTail;
    INT_PTR m_listSize;

    // 绘图状态、字体、画笔、颜色等
    Gdiplus::Font m_fntTitle;           // 标题字体字号
    Gdiplus::Font m_fntNodeTitle;       // 节点标题
    Gdiplus::Font m_fntNodeContent;     // 节点内容
    Gdiplus::Font m_fntNullTip;         // 空链表提示


    // 绘图缓存
    Bitmap m_bmpBackground;
    Bitmap m_bmpNodeBase;
    
    // 绘图配置
    const INT DW_NODE_WIDTH = 200; //节点宽度
    const INT DW_NODE_HEIGHT = 70; // 节点高度
    INT m_iDrawWidth = 0;
    INT m_iDrawHeight = 0;
  
    // 绘图操作
    void DrawBackground(Graphics & g, CRect &rect);
    void DrawNullTip(Graphics & g, CRect &rect);
    void DrawNodes(Graphics & g, CRect &rect);
    Point GetNodePosition(INT_PTR index) {
        return Point(m_iDrawWidth, m_iDrawHeight);
    }

    // 绘图检测
    INT_PTR CheckPointOnID(CPoint point);
public:
    // 数据成员获取
    INT_PTR GetSize();
    VisualListNodeBase &GetIndex(INT_PTR index);
    VisualListNodeBase &operator[](INT_PTR index);
    // 数据成员的添加
    INT_PTR InsertNode(INT_PTR position,CString content);
    // 数据成员的删除
    BOOL DeleteAt(INT_PTR index, BOOL Confirmation = TRUE);
    BOOL DeleteAll(BOOL Confirmation = TRUE);
    // 数据成员的修改
    void EditAt(INT_PTR index) {

    }
};

