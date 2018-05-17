#include "polygon.h"

Polygon::Polygon(std::initializer_list<Point> points)
{
    vertices_.reserve(points.size());
    for (const auto& point : points) {
        vertices_.push_back(point);
    }
}

void Polygon::AddPoint(const Point &point)
{
    vertices_.push_back(point);
}

Point Polygon::GetVertex(int num) const
{
    if (num < 0) {
        num += Size();
    }
    return vertices_[num % Size()];
}

Point Polygon::GetMassCenter() const
{
    auto result = Point();
    for (int i = 0; i < Size(); ++i) {
        result = result + GetVertex(i);
    }
    return Point(result.GetX() / Size(), result.GetY() / Size());
}

Polygon::InsideStatus Polygon::Inside(const Point &point) const
{
    if (IsOnBorder(point)) {
        return Polygon::InsideStatus::ON_BORDER;
    }
    const auto size = Size();
    Point a(0, point.GetY());
    Segment seg(a, point);
    int d = CrossQty(seg); // количество пересечений от границы (0, Yp) до тестируемой точки (Xp, Yp) включительно
    for(int i = 0; i < size; ++i)
    {
        if (seg.OnSegment(GetVertex(i))) //пересечение с вершиной учитывается, если она (в порядке обхода вершин):
            // - верхняя для негоризонтальной стороны
            // - первая для горизонтальной стороны
        {
            ++d;
            double y0 = GetVertex(i).GetY(); // y-коорд. i-ой точки
            double y1 = GetVertex(i - 1).GetY(); // y-коорд. (i-1)-ой точки
            double y2 = GetVertex(i + 1).GetY(); // y-коорд. (i+1)-ой точки
            if (LessEqual(y0, y1))
            {
                --d;
            }
            if (Less(y0, y2))
            {
                --d;
            }
        }
    }
    if (d%2 == 1)
    {
        return Polygon::InsideStatus::INSIDE; //внутри
    }
    else
    {
        return Polygon::InsideStatus::OUTSIDE;
    }
}

int Polygon::CrossQty(const Segment& s) const //Кол-во пересечений отрезком s многоугольника
    {
        int result = 0;
        for (int i = 0; i < Size(); ++i)
        {
            if (areSegmentsIntersect(s, Segment(GetVertex(i), GetVertex(i + 1))))
            {
                ++result;
            }
        }
        for (int i = 0; i < Size(); ++i)
        {
            if (s.OnSegment(GetVertex(i)))
            {
                --result;
            }
        }
        return result;
    }

bool Polygon::IsOnBorder(const Point &point) const
{
    for (int i = 0; i < Size(); ++i) {
        if (Segment(GetVertex(i), GetVertex(i + 1)).OnSegment(point)) {
            return true;
        }
    }
    return false;
}

int Polygon::Size() const
{
    return static_cast<int>(vertices_.size());
}

bool Polygon::isSegmentIntersects(const Segment &segment)
{
    for (int i = 0; i < Size(); ++i) {
        if (areSegmentsIntersect(Segment(GetVertex(i), GetVertex(i + 1)), segment)) {
            return true;
        }
    }
    return false;
}

Polygon::Polygon(const std::vector<Point> &points) : vertices_(points)
{}


