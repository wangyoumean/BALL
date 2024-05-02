
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


Ball::Ball(Border* border,float q,float g,int t, QObject *parent)
    : QObject(parent), border(border),q(q),g(g),t(t),ballX(0), ballY(0), dx(0) , dy(0) , r(20){
    // 初始化小球位置
}


MyWidget::MyWidget(QWidget *parent) : QWidget(parent), g(12), q(0.9), t(30) {
    border = new Border(50,50,200,400);// 创建矩形框对象
    ball = new Ball(border, q, g, t); // 创建小球对象
    ball->setPosition(60, 60);//设置小球初始位置
    ball->setSpeed(3,6); // 设置小球初始速度

    timer = new QTimer(this); // 创建定时器
    connect(timer, &QTimer::timeout, this, [this]() { this->ball->updatePosition(); }); // 连接信号和槽
    timer->start(t); // 启动定时器
}
void Border::setPosition(int x, int y){
    // 设置矩形框的初始位置和大小
    rectX = x;
    rectY = y;

}

void MyWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // 使用ball和border对象的成员变量来绘制
    painter.drawRect(border->getX(), border->getY(), border->getWidth(), border->getHeight());
    painter.setBrush(Qt::red);
    painter.drawEllipse(ball->ballX, ball->ballY, ball->r * 2, ball->r * 2);
}





void Ball::updatePosition() {
    // 更新小球位置的逻辑
    ballX += dx;
    ballY += dy;

    int rectX = border->getX();
    int rectY = border->getY();
    int rectWidth = border->getWidth();
    int rectHeight = border->getHeight();

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


    emit positionChanged(); // 发出位置改变的信号
}



