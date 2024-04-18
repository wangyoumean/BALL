#ifndef MYWIDGET_H
#define MYWIDGET_H


#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QPainter>

class MyWidget : public QWidget {

private:
    int rectX; // 矩形框左上角 x 坐标
    int rectY; // 矩形框左上角 y 坐标
    int rectWidth; // 矩形框宽度
    int rectHeight; // 矩形框高度

    int ballX; // 小球 x 坐标
    int ballY; // 小球 y 坐标
    int r;
    int dx; // 小球水平方向速度
    int dy; // 小球垂直方向速度
    double gravity; //重力加速度

public:
    MyWidget(QWidget *parent = nullptr) : QWidget(parent) {
        // 设置矩形框的初始位置和大小
        rectX = 50;
        rectY = 50;
        rectWidth = 200;
        rectHeight = 250;
        gravity = 1; //初始化重力加速度

        // 设置小球的初始位置和速度
        ballX = rectX + 10; // 使小球初始位置在矩形框内部
        ballY = rectY + 10;
        dx = 2; // 水平方向速度
        dy = 2; //竖直方向速度
        r = 10;//设置小球半径




        // 创建一个定时器，用于更新小球的位置
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MyWidget::updateBallPosition);
        timer->start(30); // 每隔30毫秒更新一次小球位置
    }

protected:
    void paintEvent(QPaintEvent *event)  { //event参数并未被使用，报错是正常的
        QPainter painter(this);

        // 绘制矩形框
        painter.drawRect(rectX, rectY, rectWidth, rectHeight);

        // 绘制小球
        painter.setBrush(Qt::red); // 设置画刷颜色为红色
        painter.drawEllipse(ballX, ballY, r*2, r*2); // 小球直径
    }

private slots:
    void updateBallPosition() {
        // 移动小球
        ballX += dx;
        ballY += dy;


        // 边界检查，确保小球在矩形框内运动
        if (ballX <= rectX || ballX >= rectX + rectWidth - 2*r) {
            dx = -dx; // 改变水平方向速度方向
        }
        if (ballY <= rectY ) {
            dy = -dy; // 改变垂直方向速度方向

        }
        if (ballY >= rectY + rectHeight - 2*r) {
         //限制小球不会掉出矩形框
         dy = -dy ;
         ballY = rectY + rectHeight - 2*r;
        }

        dy += gravity;//每次更新小球位置时，垂直速度加上重力加速度

//加个停止代码，当y方向速度为零时，停止程序
        // 更新界面，触发重绘事件
        update();
    }
};



#endif // MYWIDGET_H
