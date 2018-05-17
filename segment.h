#pragma once
#include "point.h"
#include "doublecomparison.h"
#include <array>
#include <utility>

class Segment
{
public:
    Segment() = default;
    Segment(const Point& first, const Point& second) : ends_{first, second}
    {}
    Point GetEnd(int num) const {
        return ends_[num];
    }
    void SetEnd(int num, const Point& point) {
        ends_[num] = point;
    }
    RealNumber Length() const {
        return Distance(ends_[0], ends_[1]);
    }
    bool OnSegment(Point point) const {
        auto direction = ends_[1] - ends_[0];
        if (NotEqual(SkewProduct(direction, ends_[1] - point), 0)) {
            return false;
        }
        return GreaterEqual(ScalarProduct(point - ends_[0], ends_[1] - ends_[0]), 0) &&
                GreaterEqual(ScalarProduct(point - ends_[1], ends_[0] - ends_[1]), 0);
    }
private:
    std::array<Point, 2> ends_;
};

std::pair<bool, Point> SegmentIntersection(const Segment& lhs, const Segment& rhs);
bool areSegmentsIntersect(const Segment& lhs, const Segment& rhs);
