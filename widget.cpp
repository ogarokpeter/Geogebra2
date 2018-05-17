//#include "geogebraplane.h"
#include "geogebragraphicsview.h"
#include "graphicview.h"
#include "widget.h"
#include "ui_widget.h"
#include "polygonmanager.h"
#include <iostream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    view(new GraphicsView()),
    scene(0, 0, 500, 500),
    plane(dynamic_cast<GraphicsView*>(view), &scene)
{
    ui->setupUi(this);
    view->setScene(&scene);
    QPen pen(Qt::green);
    //scene.addLine(0,0,200,200,pen);
    view->show();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    auto point = event->pos();
    std::cout << point.x() << " " << point.y() << std::endl;
}



