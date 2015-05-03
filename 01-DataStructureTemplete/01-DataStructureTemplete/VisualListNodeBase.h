#pragma once
class VisualListNodeBase {
public:
    VisualListNodeBase();
    virtual ~VisualListNodeBase();
    inline virtual void SetContent(CString content) {
    }
    inline virtual CString GetContent() {
        return _T("");
    };
protected:
    VisualListNodeBase *m_nodePrev;
    VisualListNodeBase *m_nodeNext;
public:

    // 绘图配置
    const INT DW_NODE_WIDTH = 200; //节点宽度
    const INT DW_NODE_HEIGHT = 70; // 节点高度

    // 获取前一个节点
    VisualListNodeBase * GetPrev();
    // 获取后一个节点
    VisualListNodeBase * GetNext();

    // 检查之前是否还有节点
    virtual BOOL HasPrev();
    // 检查之后是否还有节点
    virtual BOOL HasNext();

    // 更新指向前一节点的指针
    VisualListNodeBase *SetPrev(VisualListNodeBase *prev);
    // 更新指向后一节点的指针
    VisualListNodeBase *SetNext(VisualListNodeBase *next);

    // 执行绘图操作
    virtual void draw(Graphics & g, INT left, INT top, INT index, Gdiplus::Font  & fntNodeTitle, Gdiplus::Font &  fntNodeContent) = 0;

    // 获取指针位点
    virtual Point GetPointFromPrev(Point original, BOOL reversed = FALSE) {
        if (reversed) {
            return GetPointToPrev(original);
        }
        original.X += DW_NODE_WIDTH * 0.1F;
        original.Y += DW_NODE_HEIGHT* 0.95F;
        return original;
    }
    virtual Point GetPointToPrev(Point original , BOOL reversed = FALSE) {
        if (reversed) {
            return GetPointFromPrev(original);
        }
        original.X += DW_NODE_WIDTH * 0.9F;
        original.Y += DW_NODE_HEIGHT * 0.1F;
        return original;
    }
    virtual Point GetPointFromNext(Point original, BOOL reversed = FALSE) {
        if (reversed) {
            return GetPointToNext(original);
        }
        original.X += DW_NODE_WIDTH * 0.05F;
        original.Y += DW_NODE_HEIGHT* 0.05F;
        return original;
    }

    virtual Point GetPointToNext(Point original, BOOL reversed = FALSE) {
        if (reversed) {
            return GetPointFromNext(original);
        }
        original.X += DW_NODE_WIDTH * 0.9F;
        original.Y += DW_NODE_HEIGHT* 0.95F;
        return original;
    }
};

