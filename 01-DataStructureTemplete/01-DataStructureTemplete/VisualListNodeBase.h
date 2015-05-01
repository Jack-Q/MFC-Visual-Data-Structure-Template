#pragma once
class VisualListNodeBase {
public:
    VisualListNodeBase();
    virtual ~VisualListNodeBase();
    
protected:
    VisualListNodeBase *m_nodePrev;
    VisualListNodeBase *m_nodeNext;
public:
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
};

