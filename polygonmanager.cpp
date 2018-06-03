#include "polygonmanager.h"
#include <iostream>
#include <cmath>
#include <QMouseEvent>
#include "dialog.h"
#include "mainwindow.h"

constexpr double kDistanceSensitivity = 10;

constexpr double MinRefractiveIndex = 1.0;
constexpr double MaxRefractiveIndex = 4.0;

GeogebraPlane::GeogebraPlane(GraphicsView * graphics_view, QGraphicsScene *scene, MainWindow * main_window)
{
    graphics_view_ = graphics_view;
    scene_ = scene;
    main_window_ = main_window;
    // QObject::connect(graphics_view_, SIGNAL(PressLeftMouseButton(QPoint)), this, SLOT(AddPoint(QPoint)));
    complete_polygons_.push_back(Polygon{});
}

void MakeColorFromRefractiveIndex(double index, int& red, int& green, int& blue)
{
    red = 0;
    green = 0;
    blue = 0;
    if (!((index >= MinRefractiveIndex) && (index <= MaxRefractiveIndex)))
    {
        return;
    }
    double mid = (MinRefractiveIndex + MaxRefractiveIndex) / 2;
    if (index >= mid)
    {
        green = round(255 * ((MaxRefractiveIndex - index) / (MaxRefractiveIndex - mid)));
        red = round(255 - green / 20);

    }
    else
    {
        red = round(255 * ((index - MinRefractiveIndex) / (mid - MinRefractiveIndex)));
        green = round(255 - red / 20);

    }

}

void GeogebraPlane::UpdateScene()
{
    // scene_->clear();
    for (const auto& polygon: complete_polygons_)
    {
        QPolygon qt_polygon;
        for (int vertex = 0; vertex < polygon.Size(); ++vertex)
        {
            auto point = polygon.GetVertex(vertex);
            qt_polygon.push_back(point.GetQPoint());
        }
        int red = 255, green = 0, blue = 0;
        MakeColorFromRefractiveIndex(polygon.GetRefractiveIndex(), red, green, blue);
        // std::cout << red << " " << green << " " << blue << std::endl;
        QBrush brush(QColor(red, green, blue));
        QPen pen;
        scene_->addPolygon(qt_polygon, pen, brush);
    }
    for (int i = 0; i + 1 < incomplete_polygon_.Size(); ++i)
    {
        QLine line(incomplete_polygon_.GetVertex(i).GetQPoint(),
                   incomplete_polygon_.GetVertex(i + 1).GetQPoint());
        QPen pen;
        scene_->addLine(line, pen);
    }
}

void GeogebraPlane::AddPoint(QPoint point)
{
    for (const auto& polygon: complete_polygons_)
    {
        if (polygon.GetInsideStatus(point) != Polygon::InsideStatus::OUTSIDE)
        {
            emit ErrorDuringAddingPoint("Точка внутри одного из ранее созданных многоугольников!");
            return;
        }
    }

    if (incomplete_polygon_.Size() == 0)
    {
        incomplete_polygon_.AddPoint(point);
        return;
    }

    Segment side(incomplete_polygon_.GetVertex(incomplete_polygon_.Size() - 1), point);
    for (const auto& polygon: complete_polygons_)
    {
        if (polygon.DoesSegmentIntersectPolygon(side))
        {
            emit ErrorDuringAddingPoint("Отрезок пересекает многоугольник!");
            return;
        }
    }

    for (int i = 0; i + 2 < incomplete_polygon_.Size(); ++i)
    {
        if (DoSegmentsHaveCommonPoint(side, Segment(incomplete_polygon_.GetVertex(i),
                                                    incomplete_polygon_.GetVertex(i + 1))))
        {
            emit ErrorDuringAddingPoint("Самопересекающийся многоугольник!");
            return;
        }
    }

    if (Distance(incomplete_polygon_.GetVertex(0), point) < kDistanceSensitivity)
    {
        if (incomplete_polygon_.Size() <= 2)
        {
            emit ErrorDuringAddingPoint("Слишком маленький размер многоугольника!");
            return;
        }

        for (const auto& polygon: complete_polygons_)
        {
            for (int j = 0; j < polygon.Size(); ++j)
            {
                if (incomplete_polygon_.GetInsideStatus(polygon.GetVertex(j))
                        != Polygon::InsideStatus::OUTSIDE)
                {
                    emit ErrorDuringAddingPoint("Вложенные многоугольники!");
                    return;
                }
            }
        }
        emit FinishEnteringPolygon(&incomplete_polygon_);
        std::cout << incomplete_polygon_.GetRefractiveIndex() << std::endl;
        complete_polygons_.push_back(incomplete_polygon_);
        incomplete_polygon_ = Polygon{};
        UpdateScene();
        return;
    }

    incomplete_polygon_.AddPoint(point);
    UpdateScene();
}
