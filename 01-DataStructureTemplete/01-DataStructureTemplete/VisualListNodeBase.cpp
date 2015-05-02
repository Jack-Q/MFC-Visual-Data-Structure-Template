#include "stdafx.h"
#include "VisualListNodeBase.h"


VisualListNodeBase::VisualListNodeBase() {
    m_nodeNext = NULL;
    m_nodePrev = NULL;
}


VisualListNodeBase::~VisualListNodeBase() {
}


// ��ȡǰһ���ڵ�
VisualListNodeBase * VisualListNodeBase::GetPrev() {
    return m_nodePrev;
}


// ��ȡ��һ���ڵ�
VisualListNodeBase * VisualListNodeBase::GetNext() {
    return m_nodeNext;
}

// ���֮ǰ�Ƿ��нڵ�
BOOL VisualListNodeBase::HasPrev() {
    return BOOL(m_nodePrev);
}

// ���֮���Ƿ��нڵ�
BOOL VisualListNodeBase::HasNext() {
    return BOOL(m_nodeNext);
}

// ����ָ��ǰһ�ڵ��ָ��
VisualListNodeBase *VisualListNodeBase::SetPrev(VisualListNodeBase *prev) {
    VisualListNodeBase *currentPrev = m_nodePrev;
    m_nodePrev = prev;
    return currentPrev;
}

// ����ָ���һ�ڵ��ָ��
VisualListNodeBase *VisualListNodeBase::SetNext(VisualListNodeBase *next) {
    VisualListNodeBase *currentNext = m_nodeNext;
    m_nodeNext = next;
    return currentNext;
}