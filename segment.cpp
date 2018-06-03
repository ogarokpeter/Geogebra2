#include "segment.h"

std::pair<bool, Point> SegmentIntersection(const Segment &lhs, const Segment &rhs)
// возвращает статус и точку истинного пересечения отрезков
// (то есть если отрезки неколлинеарны и пересекаются в точке)
{
    auto lhs_direction = lhs.GetEnd(1) - lhs.GetEnd(0);
    auto rhs_direction = rhs.GetEnd(1) - rhs.GetEnd(0);
    if (Equal(SkewProduct(lhs_direction, rhs_direction), 0))
    {
        return {false, {}};
    }
    auto slope = SkewProduct(rhs.GetEnd(0) - lhs.GetEnd(0), rhs_direction) /
            SkewProduct(lhs_direction, rhs_direction);
    auto intersection = lhs.GetEnd(0) + lhs_direction * slope;
    if (lhs.IsPointOnSegment(intersection) && rhs.IsPointOnSegment(intersection))
    {
        return {true, intersection};
    }
    return {false, {}};
}

bool DoSegmentsHaveCommonPoint(const Segment &lhs, const Segment &rhs)
// возвращает true, если отрезки имеют общую точку, и false иначе
{
    if (rhs.IsPointOnSegment(lhs.GetEnd(0)) || rhs.IsPointOnSegment(lhs.GetEnd(1)))
    {
        return true;
    }
    if (lhs.IsPointOnSegment(rhs.GetEnd(0)) || lhs.IsPointOnSegment(rhs.GetEnd(1)))
    {
        return true;
    }
    return SegmentIntersection(lhs, rhs).first;
}
