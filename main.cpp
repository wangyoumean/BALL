#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyWidget widget;
    widget.resize(300, 400);
    widget.setWindowTitle("Ball in Rectangle");
    widget.show();

    return app.exec();
}
