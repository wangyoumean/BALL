#include "ball.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Border border;
    Ball ball;

    border.setPosition(50,50,400,500);
    ball.setPosition(50,50);
    ball.setSpeed(2,3);
    ball.setRadius(5);
    ball.startMoving();
    Ball b;
    b.show();



    return a.exec();
}

