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
    void UpdateScene();
public slots:
    void AddPoint(QPoint point);
private:
    std::vector<Polygon> polygons_;
    GraphicsView* graphics_view_;
    QGraphicsScene* scene_;

    MainWindow* main_window_;
signals:
    void ErrorDuringAddingPoint(const QString& string);
    void FinishEnteringPolygon(Polygon* polygon);
};
