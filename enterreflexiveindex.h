#pragma once

#include <QDialog>
#include "polygon.h"

namespace Ui {
class EnterReflexiveIndex;
}

class EnterReflexiveIndex : public QDialog
{
    Q_OBJECT

public:
    explicit EnterReflexiveIndex(QWidget *parent = 0);
    ~EnterReflexiveIndex();
    void SetPolygon(Polygon* polygon) { polygon_ = polygon; }


private slots:
    void on_pushButton_clicked();

private:
    Ui::EnterReflexiveIndex *ui;
    Polygon* polygon_;
};

