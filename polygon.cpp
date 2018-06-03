#include "polygon.h"
#include <cmath>

Polygon::Polygon(std::initializer_list<Point> points)
{
    vertices_.reserve(points.size());
    for (const auto& point : points)
    {
        vertices_.push_back(point);
    }
}

void Polygon::AddPoint(const Point &point)
{
    vertices_.push_back(point);
}

Point Polygon::GetVertex(int num) const
{
    num %= Size();
    if (num < 0)
    {
        num += Size();
    }
    return vertices_[num];
}

Point Polygon::GetMassCenter() const
{
    auto result = Point();
    for (int i = 0; i < Size(); ++i)
    {
        result = result + GetVertex(i);
    }
    result = result / Size();
    return result;
}

Polygon::InsideStatus Polygon::GetInsideStatus(const Point &point) const
{
    if (IsPointOnBorder(point))
    {
        return Polygon::InsideStatus::ON_BORDER;
    }
    Segment infinity_ray({-1, point.GetY()}, point);
    int intersection_number = CrossQty(infinity_ray);
    // количество пересечений от границы (-1, Yp) до тестируемой точки (Xp, Yp) включительно
    for (int i = 0; i < Size(); ++i)
    {
        if (infinity_ray.IsPointOnSegment(GetVertex(i)))
            // пересечение с вершиной учитывается, если она (в порядке обхода вершин):
            // - верхняя для негоризонтальной стороны
            // - первая для горизонтальной стороны
        {
            ++intersection_number;
            if (LessEqual(GetVertex(i).GetY(), GetVertex(i - 1).GetY()))
            {
                --intersection_number;
            }
            if (Less(GetVertex(i).GetY(), GetVertex(i + 1).GetY()))
            {
                --intersection_number;
            }
        }
    }
    if (intersection_number % 2 == 1)
    {
        return Polygon::InsideStatus::INSIDE;
    }
    else
    {
        return Polygon::InsideStatus::OUTSIDE;
    }
}

int Polygon::CrossQty(const Segment& segment) const
// количество пересечений тестируемым отрезком многоугольника
    {
        int result = 0;
        for (int i = 0; i < Size(); ++i)
        {
            if (DoSegmentsHaveCommonPoint(segment, Segment(GetVertex(i), GetVertex(i + 1))))
            {
                ++result;
            }
        }
        for (int i = 0; i < Size(); ++i)
        {
            if (segment.IsPointOnSegment(GetVertex(i)))
            {
                --result;
            }
        }
        return result;
    }

bool Polygon::IsPointOnBorder(const Point &point) const
{
    for (int i = 0; i < Size(); ++i)
    {
        if (Segment(GetVertex(i), GetVertex(i + 1)).IsPointOnSegment(point))
        {
            return true;
        }
    }
    return false;
}

int Polygon::Size() const
{
    return static_cast<int>(vertices_.size());
}

bool Polygon::DoesSegmentIntersectPolygon(const Segment &segment) const
{
    for (int i = 0; i < Size(); ++i)
    {
        if (DoSegmentsHaveCommonPoint(Segment(GetVertex(i), GetVertex(i + 1)), segment))
        {
            return true;
        }
    }
    return false;
}

Polygon::Polygon(const std::vector<Point> &points) : vertices_(points)
{}


