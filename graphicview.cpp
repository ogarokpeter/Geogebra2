#include "graphicview.h"
#include "widget.h"
#include <iostream>

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    std::cout << "Kek!" << std::endl;
    if (event->button() == Qt::LeftButton)
    {
        emit PressLeftMouseButton(event->pos());
    }
    if (event->button() == Qt::RightButton)
    {
        emit PressRightMouseButton(event->pos());
    }
}
