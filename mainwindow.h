#pragma once
#include <QMainWindow>
#include "graphicview.h"
#include "polygonmanager.h"

namespace Ui {
class MainWindow;
}
class Dialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void OpenDialogWindow(QString text);
    void OpenRefractiveIndexEnteringWindow(Polygon* polygon);
private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene_;
    GraphicsView* graphics_view_;
    GeogebraPlane plane;
};
