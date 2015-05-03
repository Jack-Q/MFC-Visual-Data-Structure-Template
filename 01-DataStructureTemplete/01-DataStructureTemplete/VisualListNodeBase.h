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

    // ��ͼ����
    const INT DW_NODE_WIDTH = 200; //�ڵ���
    const INT DW_NODE_HEIGHT = 70; // �ڵ�߶�

    // ��ȡǰһ���ڵ�
    VisualListNodeBase * GetPrev();
    // ��ȡ��һ���ڵ�
    VisualListNodeBase * GetNext();

    // ���֮ǰ�Ƿ��нڵ�
    virtual BOOL HasPrev();
    // ���֮���Ƿ��нڵ�
    virtual BOOL HasNext();

    // ����ָ��ǰһ�ڵ��ָ��
    VisualListNodeBase *SetPrev(VisualListNodeBase *prev);
    // ����ָ���һ�ڵ��ָ��
    VisualListNodeBase *SetNext(VisualListNodeBase *next);

    // ִ�л�ͼ����
    virtual void draw(Graphics & g, INT left, INT top, INT index, Gdiplus::Font  & fntNodeTitle, Gdiplus::Font &  fntNodeContent) = 0;

    // ��ȡָ��λ��
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

