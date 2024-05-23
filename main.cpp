#include "ball.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Border border(50,50,400,500);//设置参数的值，依次为矩形框左上角x坐标、矩形框左上角y坐标、矩形框宽度、矩形框高度
    Ball ball(50,50,4,2,15,&border);//设置参数的值，分别为小球x坐标、小球y坐标、小球水平方向速度、小球竖直方向速度、小球半径和一个border指针

    ball.resize(500,600);//设置窗口大小
    ball.move(600,150);//移动窗口
    ball.setFixedSize(ball.width(),ball.height());//锁定窗口大小
    ball.setWindowTitle("运动小球");//窗口标题
    ball.startMoving();
    ball.show();



    return a.exec();
}

