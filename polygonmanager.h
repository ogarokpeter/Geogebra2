#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPoint>
#include <vector>
#include "graphicview.h"
#include <iostream>
#include "polygon.h"

class MainWindow;

class GeogebraPlane : public QObject
{
    Q_OBJECT
public:
    GeogebraPlane() = default;
    GeogebraPlane(GraphicsView*, QGraphicsScene*, MainWindow*);
    void SetParams(GraphicsView* view, QGraphicsScene* scene, MainWindow* window)
    {
        graphics_view_ = view;
        scene_ = scene;
        main_window_ = window;
    }
    void UpdateScene();
    QGraphicsScene* GetGraphicsScene() const
    {
        return scene_;
    }
    GraphicsView* GetGraphicsView() const
    {
        return graphics_view_;
    }
public slots:
    void AddPoint(QPoint point);
private:
    std::vector<Polygon> complete_polygons_;
    Polygon incomplete_polygon_;
    GraphicsView* graphics_view_;
    QGraphicsScene* scene_;
    friend class RayDrawer;
    MainWindow* main_window_;
signals:
    void ErrorDuringAddingPoint(const QString& string);
    void FinishEnteringPolygon(Polygon* polygon);
};
