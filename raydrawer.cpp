#include "raydrawer.h"

constexpr double kPointRadius = 5;

RayDrawer::RayIntersection RayDrawer::FindNearestIntersectionPoint()
{
    RayIntersection result;
    result.point = ray_.GetEnd();
    // std::cout << "ray " << ray_.GetBegin().GetX() << " " << ray_.GetBegin().GetY() << std::endl;
    // std::cout << "ray " << ray_.GetEnd().GetX() << " " << ray_.GetEnd().GetY() << std::endl;

    for (const auto& polygon: *polygons_)
    {
        for (int i = 0; i < polygon.Size(); ++i)
        {
            auto intersection = SegmentIntersection({polygon.GetVertex(i), polygon.GetVertex(i+1)},
                                                     {ray_.GetBegin(), result.point});
            // std::cout << intersection.second.GetX() << " " << intersection.second.GetY() << std::endl;
            if (intersection.first)
            {
                if (Distance(intersection.second, ray_.GetBegin()) < EPS)
                {
                    continue;
                }
                result.point = intersection.second;
                result.segment = {polygon.GetVertex(i), polygon.GetVertex(i+1)};
                result.polygon = &polygon;
            }
        }
    }
    // std::cout << "res " << result.point.GetX() << " " << result.point.GetY() << std::endl;
    return result;
}

bool RayDrawer::FindNewRay(const Point& intersection_point, const Segment& intersection_segment,
                           double outer_index, double inner_index)
// возвращает true, если происходит преломление, и false, если отражение
{
    bool is_refract = true;

    Point perpendicular_point = ray_.ConvertToPoint()
            - intersection_segment.ConvertToPoint()
            * ScalarProduct(ray_.ConvertToPoint(), intersection_segment.ConvertToPoint()) / intersection_segment.SquareLength();

    double b1 = atan2(SkewProduct(perpendicular_point, ray_.ConvertToPoint()),
                      ScalarProduct(perpendicular_point, ray_.ConvertToPoint()));

    double sinb2 = (outer_index * sin(b1)) / inner_index;

    Point new_direction;

    if ((sinb2 >= 1) || (sinb2 <= -1))
    {
        new_direction = -(ray_.ConvertToPoint()
                - intersection_segment.ConvertToPoint() * 2
                * ScalarProduct(ray_.ConvertToPoint(), intersection_segment.ConvertToPoint()) / intersection_segment.SquareLength());
        is_refract = false;
    }
    else
    {
        new_direction = perpendicular_point;
        new_direction.Rotate(asin(sinb2));
    }

    Point next = intersection_point + new_direction;
    ray_ = Ray(intersection_point, next);

    return is_refract;
}

void RayDrawer::TrassRay()
{
    bool is_inside = false;
    for (int i = 0; i < static_cast<int>(polygons_->size()); ++i)
    {
        if ((*polygons_)[i].GetInsideStatus(ray_.GetBegin()) == Polygon::InsideStatus::INSIDE)
        {
            is_inside = true;
        }
    }
    QPen pen;
    double x_coordinate_of_circle = ray_.GetBegin().GetX() - kPointRadius / 2;
    double y_coordinate_of_circle = ray_.GetBegin().GetY() - kPointRadius / 2;
    QBrush brush(Qt::SolidPattern);
    scene_->addEllipse(x_coordinate_of_circle, y_coordinate_of_circle, kPointRadius, kPointRadius, pen, brush);
    while (true)
    {
        auto intersection = FindNearestIntersectionPoint();
        QLine line(ray_.GetBegin().GetQPoint(),
                   intersection.point.GetQPoint());
        QPen pen;
        scene_->addLine(line, pen);
        if (!intersection.polygon)
        {
            break;
        }
        bool is_refract;
        if (is_inside)
        {
            is_refract = FindNewRay(intersection.point, intersection.segment,
                       intersection.polygon->GetRefractiveIndex(), 1.0);
        }
        else
        {
            is_refract = FindNewRay(intersection.point, intersection.segment,
                       1.0, intersection.polygon->GetRefractiveIndex());
        }
        if (is_refract == true)
        {
                is_inside = !is_inside;
        }
    }
}
