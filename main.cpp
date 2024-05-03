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

MyWidget::MyWidget(QWidget *parent) : QWidget(parent), border(new Border), ball(new Ball(this,border)),timer(new QTimer(this)){

        g = 12; //初始化重力加速度
        q = 0.9;//设置碰撞系数
        t = 30;//定时器更新间隔时间，单位为ms
        border->setPosition(400,500,300,500);//设置矩形框左上角的X、Y坐标、宽度和高度
        ball->setRadius(20);//设置小球的半径


        // 创建一个定时器，用于更新小球的位置

        if (ball){
        connect(timer, &QTimer::timeout, this, [this]() { this->ball->updateBallPosition(); }); // 连接信号和槽
        }
        timer->start(t); // 每隔t毫秒更新一次小球位置


    }

MyWidget::~MyWidget() {
    delete ball; // 释放 ball 指针指向的内存
    delete border; // 释放 border 指针指向的内存
    // 不需要删除 timer，因为 Qt 会自动处理它
}

Ball::Ball(MyWidget* widget, Border* border) : mywidget(widget), border(border) {

}

void Border::draw(QPainter& painter) const {
    // 使用传入的 QPainter 绘制矩形
    painter.drawRect(rectX, rectY, rectWidth, rectHeight);
}

void Ball::draw(QPainter& painter) const {
    // 使用传入的 QPainter 绘制圆形
    painter.drawEllipse(ballX, ballY, r * 2, r * 2);
}

void MyWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event)
    QPainter painter(this);

         // 绘制矩形框
         border->draw(painter);

         // 绘制小球
         painter.setBrush(Qt::red); // 设置画刷颜色为红色
         ball->draw(painter);
     }

void Border::setPosition(int x , int y , int width , int height){
    rectX = x;
    rectY = y;
    rectWidth = width;
    rectHeight = height;
}

void Ball::setPosition(float x, float y) {
    ballX = x;
    ballY = y;
}

void Ball::setSpeed(float x, float y) {
    dx = x;
    dy = y;
}

void Ball::setRadius(int radius) {
    r = radius;
}

void Ball::updateBallPosition(){

    //设置小球的速度和初始位置
    setSpeed(3,6);
    setPosition(border->rectX + 10,border->rectY + 10);

    // 小球的运动
    ballX += dx;
    ballY += dy;

    if (ballX <= border->rectX || ballX >= border->rectX + border->rectWidth - 2*r) {
        dx = -dx; // 改变水平方向速度方向
        dx = dx * mywidget->q;
    }

    if (ballY <= border->rectY || ballY >= border->rectY + border->rectHeight - 2*r) {
        dy = -dy; // 改变垂直方向速度方向
        dy = dy * mywidget->q;

        ballY = border->rectY + border->rectHeight - 2*r;//限制小球不会掉出矩形框
    }

    dy += (mywidget->g / 1000 * mywidget->t);//每次更新小球位置时，垂直速度加上重力加速度,单位换算成秒

    // 更新界面，触发重绘事件
    mywidget->update();
}


