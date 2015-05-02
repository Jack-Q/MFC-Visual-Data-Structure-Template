#include "stdafx.h"
#include "VisualListArrow.h"


VisualListArrow::VisualListArrow(const Color &color)
    :m_color(color), m_brush(m_color) ,m_pen(&m_brush,3.0F)
{
    
}

VisualListArrow::~VisualListArrow() {
}

void VisualListArrow::draw(Graphics &g) {
    //TODO Draw Curve
    //g.DrawCurve(m_pen, m_points.GetData(), m_points.GetSize());
}

inline INT_PTR VisualListArrow::AddPoint(const Point point) {
    return m_points.Add(point);
}

inline void VisualListArrow::RemovePoint(INT_PTR index) {
    if (index == -1) {
        return m_points.RemoveAll();
    }
    if (index >= 0 && index < m_points.GetCount()) {
        return m_points.RemoveAt(index);
    }
}