#pragma once
#include <QMainWindow>
#include <vector>
#include "graphicview.h"
#include "polygonmanager.h"
#include "polygon.h"
#include "ray.h"

namespace Ui
{
    class MainWindow;
}
class Dialog;

enum class EnteringStatus
{
    ENTERINGPOLYGON,
    ENTERINGRAY,
    WAITING
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void OpenDialogWindow(QString text);
    void OpenRefractiveIndexEnteringWindow(Polygon* polygon);
    void ActionLeftMouseButtonPressed(QPoint point);
    void ActionEnteringPolygonEnded(Polygon* polygon);
private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene_;
    GraphicsView* graphics_view_;
    GeogebraPlane plane;
    EnteringStatus status_ = EnteringStatus::WAITING;
    std::vector<Ray> rays_;
    std::vector<QPoint> ray_points_;
};
