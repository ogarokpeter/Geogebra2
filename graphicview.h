#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>


class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    using QGraphicsView::QGraphicsView;
    GraphicsView() = default;
    ~GraphicsView() {}
public slots:
    void mousePressEvent(QMouseEvent* event) override;
signals:
    void PressLeftMouseButton(QPoint point);
    void PressRightMouseButton(QPoint point);
};
