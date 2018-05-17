#include "polygonmanager.h"
#include <iostream>
#include <QMouseEvent>
#include "dialog.h"
#include "mainwindow.h"

GeogebraPlane::GeogebraPlane(GraphicsView * graphics_view, QGraphicsScene *scene, MainWindow * main_window)
{
    graphics_view_ = graphics_view;
    scene_ = scene;
    main_window_ = main_window;
    QObject::connect(graphics_view_, SIGNAL(PressLeftMouseButton(QPoint)), this, SLOT(AddPoint(QPoint)));
    //QObject::connect(this, SIGNAL(ErrorDuringAddingPoint(QString)), main_window_, SLOT())
    polygons_.push_back(Polygon{});
}

void GeogebraPlane::UpdateScene()
{
    scene_->clear();
    for (int i = 0; i + 1 < polygons_.size(); ++i) {
        QPolygon qt_polygon;
        for (int v = 0; v < polygons_[i].Size(); ++v)
        {
            auto point = polygons_[i].GetVertex(v);
            qt_polygon.push_back(point.GetQPoint());
        }
        QBrush brush(QColor(255, 0, 0));
        QPen pen;
        scene_->addPolygon(qt_polygon, pen, brush);
    }
    const auto& polygon = polygons_.back();
    for (int i = 0; i + 1 < polygon.Size(); ++i) {
        QLine line(polygon.GetVertex(i).GetQPoint(), polygon.GetVertex(i + 1).GetQPoint());
        QPen pen;
        scene_->addLine(line, pen);
    }
}

void GeogebraPlane::AddPoint(QPoint point)
{
    auto& polygon = polygons_.back();
    for (int i = 0; i + 1 < polygons_.size(); ++i) {
        if (polygons_[i].Inside(point) != Polygon::InsideStatus::OUTSIDE) {
            emit ErrorDuringAddingPoint("Точка внутри одного из ранее созданных многоугольников!");
            return;
        }
    }
    if (polygon.Size() == 0) {
        polygon.AddPoint(point);
        return;
    }
    Segment side(polygon.GetVertex(polygon.Size() - 1), point);
    for (int i = 0; i + 1 < polygons_.size(); ++i) {
        if (polygons_[i].isSegmentIntersects(side)) {
            emit ErrorDuringAddingPoint("Отрезок пересекает многоугольник!");
            return;
        }
    }
    if (Distance(polygon.GetVertex(0), point) < 10) {
        if (polygon.Size() <= 2) {
            emit ErrorDuringAddingPoint("Слишком маленький размер многоугольника!");
            return;
        }

        for (int i = 0; i + 1 < polygons_.size(); ++i)
        {
            for (int j = 0; j < polygons_[i].Size(); ++j)
            {
                if (polygon.Inside(polygons_[i].GetVertex(j)) != Polygon::InsideStatus::OUTSIDE)
                {
                    emit ErrorDuringAddingPoint("Вложенные многоугольники");
                    return;
                }
            }
        }
        emit FinishEnteringPolygon(&polygon);
        std::cout << polygon.GetRefactiveIndex() << std::endl;
        polygons_.push_back(Polygon{});
        UpdateScene();
        return;
    }
    for (int i = 0; i + 2 < polygon.Size(); ++i) {
        if (areSegmentsIntersect(side, Segment(polygon.GetVertex(i), polygon.GetVertex(i + 1)))) {
            emit ErrorDuringAddingPoint("Самопересекающийся многоугольник");
            return;
        }
    }

    polygon.AddPoint(point);
    UpdateScene();
}
