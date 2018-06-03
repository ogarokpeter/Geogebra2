#include "point.h"
#include "segment.h"
#include "polygon.h"
#include <iostream>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication EditorApp(argc, argv);
    MainWindow Editor;
    Editor.show();

    return EditorApp.exec();
}
