#include "enterrefractiveindex.h"
#include "ui_enterRefractiveindex.h"

EnterRefractiveIndex::EnterRefractiveIndex(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnterRefractiveIndex)
{
    ui->setupUi(this);
        setModal(true);
}

EnterRefractiveIndex::~EnterRefractiveIndex()
{
    delete ui;
}

void EnterRefractiveIndex::on_pushButton_clicked()
{
    polygon_->SetRefractiveIndex(ui->doubleSpinBox->value());
    close();
}
