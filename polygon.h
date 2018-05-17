#pragma once
#include "point.h"
#include "segment.h"

class Polygon
{
public:
    Polygon() = default;
    Polygon(std::initializer_list<Point> points);
    Polygon(const std::vector<Point>& points);
    void AddPoint(const Point& point);

    Point GetVertex(int num) const;
    Point GetMassCenter() const;
    enum class InsideStatus {
        INSIDE,
        ON_BORDER,
        OUTSIDE
    };
    InsideStatus Inside(const Point& point) const;
    bool IsOnBorder(const Point& point) const;
    int Size() const;

    void SetRefractiveIndex(RealNumber refractive_index)
    {
        refractive_index_ = refractive_index;
    }

    RealNumber GetRefactiveIndex() const {
        return refractive_index_;
    }

    bool isSegmentIntersects(const Segment& segment);


private:
    int CrossQty(const Segment& segment) const;
    std::vector<Point> vertices_;
    RealNumber refractive_index_ = 0;
};

