#include "mainwindow.h"
#include "dialog.h"
#include "ui_mainwindow.h"
#include "enterrefractiveindex.h"
#include "polygon.h"
#include "raydrawer.h"

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
    QObject::connect(&plane, SIGNAL(FinishEnteringPolygon(Polygon*)), this, SLOT(ActionEnteringPolygonEnded(Polygon*)));
    QObject::connect(graphics_view_, SIGNAL(PressLeftMouseButton(QPoint)), this, SLOT(ActionLeftMouseButtonPressed(QPoint)));
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
    EnterRefractiveIndex dialog;
    dialog.SetPolygon(polygon);
    dialog.show();
    dialog.exec();
}

void MainWindow::ActionLeftMouseButtonPressed(QPoint point)
{
    if (status_ == EnteringStatus::WAITING)
    {
        if (ui->pushButton->GetStatus())
        {
            status_ = EnteringStatus::ENTERINGRAY;
        }
        else
        {
            status_ = EnteringStatus::ENTERINGPOLYGON;
        }
    }
    if (status_ == EnteringStatus::ENTERINGPOLYGON)
    {
        plane.AddPoint(point);
    }
    else
    {
        ray_points_.push_back(point);
        if (ray_points_.size() == 2)
        {
            rays_.push_back({ray_points_[0], ray_points_[1]});
            status_ = EnteringStatus::WAITING;
            ray_points_.clear();
        }
    }
    scene_->clear();
    plane.UpdateScene();
    for (const auto& ray: rays_)
    {
        RayDrawer drawer(ray, &plane);
        drawer.TrassRay();
    }
}

void MainWindow::ActionEnteringPolygonEnded(Polygon* polygon)
{
    status_ = EnteringStatus::WAITING;
    OpenRefractiveIndexEnteringWindow(polygon);
}
