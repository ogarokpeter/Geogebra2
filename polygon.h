#pragma once
#include "point.h"
#include "segment.h"
#include <vector>

class Polygon
{
public:
    Polygon() = default;
    Polygon(std::initializer_list<Point> points);
    Polygon(const std::vector<Point>& points);
    void AddPoint(const Point& point);

    Point GetVertex(int num) const;
    Point GetMassCenter() const;
    enum class InsideStatus
    {
        INSIDE,
        ON_BORDER,
        OUTSIDE
    };
    InsideStatus GetInsideStatus(const Point& point) const;
    int Size() const;

    void SetRefractiveIndex(RealNumber refractive_index)
    {
        refractive_index_ = refractive_index;
    }

    RealNumber GetRefractiveIndex() const
    {
        return refractive_index_;
    }

    bool DoesSegmentIntersectPolygon(const Segment& segment) const;


private:
    int CrossQty(const Segment& segment) const;
    bool IsPointOnBorder(const Point& point) const;
    std::vector<Point> vertices_;
    RealNumber refractive_index_ = 0;
};

