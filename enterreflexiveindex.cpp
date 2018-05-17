#include "enterreflexiveindex.h"
#include "ui_enterreflexiveindex.h"

EnterReflexiveIndex::EnterReflexiveIndex(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnterReflexiveIndex)
{
    ui->setupUi(this);
        setModal(true);
}

EnterReflexiveIndex::~EnterReflexiveIndex()
{
    delete ui;
}

void EnterReflexiveIndex::on_pushButton_clicked()
{
    polygon_->SetRefractiveIndex(ui->doubleSpinBox->value());
    close();
}
