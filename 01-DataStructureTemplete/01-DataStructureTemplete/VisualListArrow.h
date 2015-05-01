#pragma once

class VisualListArrow {
public:
    VisualListArrow(/*const Brush &brush,*/ const Color &color);
    inline INT_PTR AddPoint(const Point point);
    inline void RemovePoint(INT_PTR index = -1);
    virtual ~VisualListArrow();
    void draw(Graphics &g);
private:
    //Pen m_pen;
    //Brush m_brush;
    Color m_color;
    CArray<Point,Point> m_points;
};

