#include "geogebragraphicsview.h"
#include <iostream>
#include <QMouseEvent>

void GeogebraGraphicsView::mousePressEvent(QMouseEvent *event)
{
    std::cout << "Kek!!!" << std::endl;
    //emit AddPoint(event->pos());
}
