#include "point.h"
#include "segment.h"
#include "polygon.h"
#include <iostream>
#include <QApplication>
#include "mainwindow.h"

/*int main() {
    Polygon polygon;
    int num_vertex;
    std::cout << "Hello!" << std::endl;
    std::cin >> num_vertex;
    std::cout << num_vertex << std::endl;
    std::cout << "Hello2!" << std::endl;
    for (int i = 0; i < num_vertex; ++i) {
        int x, y;
        std::cout << "Enter points" << std::endl;
        std::cin >> x >> y;
        polygon.AddPoint(Point(x, y));
    }
    int x, y;
    std::cin >> x >> y;
    std::cout << "Here" << std::endl;
    auto status = polygon.Inside(Point(x, y));
    if (status == Polygon::InsideStatus::ON_BORDER) {
        std::cout << "OnBorder" << std::endl;
    }
    if (status == Polygon::InsideStatus::INSIDE) {
        std::cout << "inside" << std::endl;
    }
    if (status == Polygon::InsideStatus::OUTSIDE) {
        std::cout << "outside" << std::endl;
    }
}*/


int main(int argc, char *argv[])
{
    QApplication EditorApp(argc, argv);
    MainWindow Editor;
    Editor.show();

    return EditorApp.exec();
}
