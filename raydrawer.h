#pragma once
#include "polygonmanager.h"
#include "ray.h"

class RayDrawer
{
public:
    RayDrawer() = default;
    RayDrawer(const Ray& ray, GeogebraPlane* plane): ray_(ray), polygons_(&plane->complete_polygons_),
        graphics_view_(plane->GetGraphicsView()), scene_(plane->GetGraphicsScene()) {}
    void TrassRay();

private:
    Ray ray_;
    std::vector<Polygon>* polygons_;
    GraphicsView* graphics_view_;
    QGraphicsScene* scene_;
    struct RayIntersection
    {
        const Polygon* polygon = nullptr;
        Segment segment;
        Point point;
    };
    RayIntersection FindNearestIntersectionPoint();
    bool FindNewRay(const Point& intersection_point, const Segment& intersection_segment,
                    double outer_index, double inner_index);

};
