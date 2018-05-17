#include "mainwindow.h"
#include "dialog.h"
#include "ui_mainwindow.h"
#include "enterreflexiveindex.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene_(new QGraphicsScene(0, 0, 400, 400)),
    graphics_view_(new GraphicsView(scene_)),
    plane(graphics_view_, scene_, this)
{
    ui->setupUi(this);
    graphics_view_->show();
    graphics_view_->setRenderHint(QPainter::Antialiasing);
    QObject::connect(&plane, SIGNAL(ErrorDuringAddingPoint(QString)), this, SLOT(OpenDialogWindow(QString)));
    QObject::connect(&plane, SIGNAL(FinishEnteringPolygon(Polygon*)), this, SLOT(OpenRefractiveIndexEnteringWindow(Polygon*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene_;
    delete graphics_view_;
}

void MainWindow::OpenDialogWindow(QString text)
{
    Dialog dialog;
    dialog.SetText(text);
    dialog.show();
    dialog.exec();
}

void MainWindow::OpenRefractiveIndexEnteringWindow(Polygon *polygon)
{
    EnterReflexiveIndex dialog;
    dialog.SetPolygon(polygon);
    dialog.show();
    dialog.exec();
}
