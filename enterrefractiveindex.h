#pragma once

#include "polygon.h"
#include <QDialog>

namespace Ui
{
    class EnterRefractiveIndex;
}

class EnterRefractiveIndex : public QDialog
{
    Q_OBJECT

public:
    explicit EnterRefractiveIndex(QWidget *parent = 0);
    ~EnterRefractiveIndex();
    void SetPolygon(Polygon* polygon) { polygon_ = polygon; }


private slots:
    void on_pushButton_clicked();

private:
    Ui::EnterRefractiveIndex *ui;
    Polygon* polygon_;
};

