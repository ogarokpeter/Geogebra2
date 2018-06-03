#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <iostream>
#include <memory>

namespace Ui
{
    class Dialog;
}

class Dialog : public QDialog, std::enable_shared_from_this<Dialog>
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void SetText(const QString& text);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};


#endif // DIALOG_H
