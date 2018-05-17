#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "polygonmanager.h"

namespace Ui {
class Widget;
class GraphicsView;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QGraphicsView *view;
    QGraphicsScene scene;
    GeogebraPlane plane;
    void mousePressEvent(QMouseEvent* event);
};

#endif // WIDGET_H
