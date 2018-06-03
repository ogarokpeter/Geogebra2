#pragma once
#include "point.h"
#include "doublecomparison.h"
#include <array>
#include <utility>
#include <cmath>

class Segment
{
public:
    Segment() = default;
    Segment(const Point& first, const Point& second) : ends_{first, second}
    {}
    Point GetEnd(int num) const
    {
        return ends_[num];
    }
    void SetEnd(int num, const Point& point)
    {
        ends_[num] = point;
    }
    RealNumber SquareLength() const
    {
        return SquareDistance(ends_[0], ends_[1]);
    }
    RealNumber Length() const
    {
        return Distance(ends_[0], ends_[1]);
    }
    Point ConvertToPoint() const
    {
        return ends_[1] - ends_[0];
    }
    bool IsPointOnSegment(Point point) const
    {
        auto direction = ends_[1] - ends_[0];
        if (NotEqual(SkewProduct(direction, ends_[1] - point), 0))
        {
            return false;
        }
        return (GreaterEqual(ScalarProduct(point - ends_[0], ends_[1] - ends_[0]), 0) &&
                GreaterEqual(ScalarProduct(point - ends_[1], ends_[0] - ends_[1]), 0));
    }
    RealNumber Cos(const Segment& other) const
    // возвращает косинус угла между данным вектором и вектором other
    {
        return ScalarProduct(ends_[1] - ends_[0], other.GetEnd(1) - other.GetEnd(0)) /
                (Length() * other.Length());
    }

    RealNumber Sin(const Segment& other) const
    // возвращает синус угла между данным вектором и вектором other
    {
        return SkewProduct(ends_[1] - ends_[0], other.GetEnd(1) - other.GetEnd(0)) /
                (Length() * other.Length());
    }

private:
    std::array<Point, 2> ends_;
};

std::pair<bool, Point> SegmentIntersection(const Segment& lhs, const Segment& rhs);
bool DoSegmentsHaveCommonPoint(const Segment& lhs, const Segment& rhs);
