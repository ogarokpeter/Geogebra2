#pragma once
#include <QGraphicsView>
#include <iostream>


class GeogebraGraphicsView : public QGraphicsView
{
   Q_OBJECT
public:
    using QGraphicsView::QGraphicsView;
    GeogebraGraphicsView() = default;
    ~GeogebraGraphicsView() {}
public slots:
    void mousePressEvent(QMouseEvent* event);
};

