#pragma once

#include "point.h"
#include "segment.h"

class Ray
{
public:
    Ray() = default;
    Ray(const Point& begin, const Point& end): begin_(begin), end_(end)
    {
        Normalize();
    }
    Ray(const Segment& ray): begin_(ray.GetEnd(0)), end_(ray.GetEnd(1))
    {
        Normalize();
    }
    Point GetDirection() const;
    Point GetBegin() const;
    Point GetEnd() const;
    Segment ConvertToSegment() const;
    Point ConvertToPoint() const;
private:
    Point begin_, end_;
    void Normalize();
};
