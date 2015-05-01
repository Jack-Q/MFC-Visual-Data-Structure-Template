#pragma once
class VisualListNodeBase {
public:
    VisualListNodeBase();
    virtual ~VisualListNodeBase();
    
protected:
    VisualListNodeBase *m_nodePrev;
    VisualListNodeBase *m_nodeNext;
public:
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
};

