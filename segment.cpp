#include "segment.h"

std::pair<bool, Point> SegmentIntersection(const Segment &lhs, const Segment &rhs)
{
    auto lhs_direction = lhs.GetEnd(1) - lhs.GetEnd(0);
    auto rhs_direction = rhs.GetEnd(1) - rhs.GetEnd(0);
    if (Equal(SkewProduct(lhs_direction, rhs_direction), 0))
    {
        return {false, {}};
    }
    auto t = SkewProduct(rhs.GetEnd(0) - lhs.GetEnd(0), rhs_direction) /
            SkewProduct(lhs_direction, rhs_direction);
    auto intersection = lhs.GetEnd(0) +
            Point(lhs_direction.GetX() * t, lhs_direction.GetY() * t);
    if (lhs.OnSegment(intersection) && rhs.OnSegment(intersection))
    {
        return {true, intersection};
    }
    return {false, {}};
}

bool areSegmentsIntersect(const Segment &lhs, const Segment &rhs)
{
    if (rhs.OnSegment(lhs.GetEnd(0)) || rhs.OnSegment(lhs.GetEnd(1))) {
        return true;
    }
    return SegmentIntersection(lhs, rhs).first;
}
