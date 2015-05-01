#include "stdafx.h"
#include "VisualListNodeBase.h"


VisualListNodeBase::VisualListNodeBase() {
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
    return FALSE;
}

// ���֮���Ƿ��нڵ�
BOOL VisualListNodeBase::HasNext() {
    return FALSE;
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