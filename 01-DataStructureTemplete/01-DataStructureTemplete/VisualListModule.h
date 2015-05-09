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
    
    // 设置选项接口
    void SetLinked(BOOL isLinked);
    BOOL IsLinked();
    void SetDoubled(BOOL isDoubled);
    BOOL IsDoubled();
    void SetIndexed(BOOL isIndexed);
    BOOL IsIndexed();
    void SetStartFromZero(BOOL isStartFromZero);
    BOOL IsStartFromZero();
    
private:
    // 设置选项
    BOOL m_linked = TRUE;
    BOOL m_doubled = TRUE;
    BOOL m_indexed = TRUE;
    BOOL m_startFromZero = TRUE;

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
    const INT DW_TITLE_HEIGHT = 80; // 标题高度
    const INT DW_PRIMARY_PADDING = 10; //默认内边距
    const INT DW_PRIMARY_MARGIN = 10; //默认外边距
    INT m_iDrawWidth = 0;
    INT m_iDrawHeight = 0;

    // 绘图操作
    void DrawBackground(Graphics & g, CRect &rect);
    void DrawNullTip(Graphics & g, CRect &rect);
    void DrawNodes(Graphics & g, CRect &rect);
    GraphicsPath *GetDrawArrow(Point pt, BOOL direction, GraphicsPath *arr);
    Point GetNodePosition(INT_PTR index);
    BOOL IsNodeReversed(INT_PTR index) {
        
    }
    // 绘图检测
    INT_PTR CheckPointOnID(Point point);
public:
    // 数据成员获取
    INT_PTR GetSize();
    VisualListNodeBase &GetIndex(INT_PTR index);
    VisualListNodeBase &operator[](INT_PTR index);
    // 数据成员的添加
    INT_PTR InsertNode(INT_PTR position, CString content);
    // 数据成员的删除
    BOOL DeleteAt(INT_PTR index, BOOL Confirmation = TRUE);
    BOOL DeleteAll(BOOL Confirmation = TRUE);
    // 数据成员的修改
    void EditAt(INT_PTR index, CWnd *parWnd = NULL);
};

