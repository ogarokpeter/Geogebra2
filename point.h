#pragma once
#include <doublecomparison.h>
#include <QPoint>

class Point
{
public:
    Point() = default;
    Point(RealNumber x, RealNumber y) : x_(x), y_(y) {}
    Point(const QPoint& point) : x_(point.x()), y_(point.y()) {}

    QPoint GetQPoint() const {
        return QPoint(std::lround(x_), std::lround(y_));
    }

    RealNumber GetX() const {
        return x_;
    }

    RealNumber GetY() const {
        return y_;
    }

    void SetX(RealNumber x) {
        x_ = x;
    }

    void SetY(RealNumber y) {
        y_ = y;
    }

    Point operator+(const Point& other) const
    {
        return {x_ + other.x_, y_ + other.y_};
    }

    Point operator-(const Point& other) const
    {
        return {x_ - other.x_, y_ - other.y_};
    }
private:
    RealNumber x_ = 0;
    RealNumber y_ = 0;
};

RealNumber ScalarProduct(const Point& lhs, const Point& rhs);
RealNumber SkewProduct(const Point& lhs, const Point& rhs);
RealNumber Distance(const Point& lhs, const Point& rhs);
