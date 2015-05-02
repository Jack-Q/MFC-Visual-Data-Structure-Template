#pragma once

class VisualListArrow {
public:
    VisualListArrow(const Color &color);
    inline INT_PTR AddPoint(const Point point);
    inline void RemovePoint(INT_PTR index = -1);
    virtual ~VisualListArrow();
    void draw(Graphics &g);
private:
    Color m_color;
    SolidBrush m_brush;
    Pen m_pen;
    CArray<Point,Point> m_points;
};

