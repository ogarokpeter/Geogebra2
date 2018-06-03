#include "point.h"
#include <cmath>

RealNumber ScalarProduct(const Point &lhs, const Point &rhs)
{
    return lhs.GetX() * rhs.GetX() + lhs.GetY() * rhs.GetY();
}

RealNumber SkewProduct(const Point &lhs, const Point &rhs)
{
    return lhs.GetX() * rhs.GetY() - lhs.GetY() * rhs.GetX();
}

RealNumber SquareDistance(const Point &lhs, const Point &rhs)
{
    return ((lhs.GetX() - rhs.GetX()) * (lhs.GetX() - rhs.GetX())
            + (lhs.GetY() - rhs.GetY()) * (lhs.GetY() - rhs.GetY()));
}

RealNumber Distance(const Point &lhs, const Point &rhs)
{
    return std::hypot(lhs.GetX() - rhs.GetX(), lhs.GetY() - rhs.GetY());
}
