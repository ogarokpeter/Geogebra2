#include "ray.h"

const double kMaxPicSize = 10000;

Point Ray::GetDirection() const
{
    return (end_ - begin_) / Distance(end_, begin_);
}

Point Ray::GetBegin() const
{
    return begin_;
}

Point Ray::GetEnd() const
{
    return end_;
}

Segment Ray::ConvertToSegment() const
{
    return {begin_, end_};
}

Point Ray::ConvertToPoint() const
{
    return end_ - begin_;
}

void Ray::Normalize()
{
    end_ = begin_ + (GetDirection() * kMaxPicSize);
}

