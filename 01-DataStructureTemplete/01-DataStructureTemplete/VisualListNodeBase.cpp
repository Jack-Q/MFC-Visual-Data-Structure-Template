#include "stdafx.h"
#include "VisualListNodeBase.h"


VisualListNodeBase::VisualListNodeBase() {
}


VisualListNodeBase::~VisualListNodeBase() {
}


// 获取前一个节点
VisualListNodeBase * VisualListNodeBase::GetPrev() {
    return m_nodePrev;
}


// 获取后一个节点
VisualListNodeBase * VisualListNodeBase::GetNext() {
    return m_nodeNext;
}

// 检查之前是否还有节点
BOOL VisualListNodeBase::HasPrev() {
    return FALSE;
}

// 检查之后是否还有节点
BOOL VisualListNodeBase::HasNext() {
    return FALSE;
}

// 更新指向前一节点的指针
VisualListNodeBase *VisualListNodeBase::SetPrev(VisualListNodeBase *prev) {
    VisualListNodeBase *currentPrev = m_nodePrev;
    m_nodePrev = prev;
    return currentPrev;
}

// 更新指向后一节点的指针
VisualListNodeBase *VisualListNodeBase::SetNext(VisualListNodeBase *next) {
    VisualListNodeBase *currentNext = m_nodeNext;
    m_nodeNext = next;
    return currentNext;
}