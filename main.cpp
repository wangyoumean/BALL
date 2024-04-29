
#include <QApplication>
#include "MyWidget.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MyWidget widget;//窗口设置
    widget.resize(400, 500);//设置界面大小
    widget.move(600,150);
    widget.setFixedSize(widget.width(),widget.height());//锁定界面大小

    widget.setWindowTitle("运动小球");

    widget.show();
    return a.exec();
}

MyWidget::MyWidget(QWidget *parent) : QWidget(parent) {

    ballObject = new Ball(parent);

        // 设置矩形框的初始位置和大小
        rectX = 50;
        rectY = 50;
        rectWidth = 200;
        rectHeight = 400;
        g = 12; //初始化重力加速度




        q = 0.9;//设置碰撞系数
        t = 30;//定时器更新间隔时间，单位为ms



        // 创建一个定时器，用于更新小球的位置
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, ballObject,&Ball::updateBallPosition);
        timer->start(t); // 每隔t毫秒更新一次小球位置

    }


void Ball::setSpeed(){
    // 设置小球的初始位置和速度
    dx = 3; // 水平方向速度
    dy = 6; //竖直方向速度
}
void Ball::setPosition(){
    ballX = rectX + 10; // 使小球初始位置在矩形框内部
    ballY = rectY + 10;
    r = 20;//设置小球半径
}


void MyWidget::paintEvent(QPaintEvent *event){

    QPainter painter(this);

         // 绘制矩形框
         painter.drawRect(rectX, rectY, rectWidth, rectHeight);

         // 绘制小球
         painter.setBrush(Qt::red); // 设置画刷颜色为红色
         painter.drawEllipse(ballObject->getballX(), ballObject->getballY(), ballObject->getr() * 2, ballObject->getr() * 2); // 小球直径
     }



void Ball::updateBallPosition(){
    // 小球的运动
    ballX += dx;
    ballY += dy;

    if (ballX <= rectX || ballX >= rectX + rectWidth - 2*r) {
        dx = -dx; // 改变水平方向速度方向
        dx = dx * q;
    }

    if (ballY <= rectY || ballY >= rectY + rectHeight - 2*r) {
        dy = -dy; // 改变垂直方向速度方向
        dy = dy * q;

        ballY = rectY + rectHeight - 2*r;//限制小球不会掉出矩形框
    }

    dy += (g / 1000 * t);//每次更新小球位置时，垂直速度加上重力加速度,单位换算成秒

    // 更新界面，触发重绘事件
    update();
}


