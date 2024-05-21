#include "ball.h"
#include "ui_ball.h"

Ball::Ball(QWidget *parent) : QWidget(parent), ui(new Ui::Ball),border(nullptr)//初始化
{
    ui->setupUi(this);
    // 初始化小球的其他属性
    ballX = 0;
    ballY = 0;
    r = 10; // 默认半径
    dx = 0;
    dy = 0;
    g = 9.8; // 重力加速度
    q = 0.9; // 碰撞系数
    t = 16; // 假设定时器更新时间为16ms ，使程序以60帧运行


    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Ball::updateBallPosition);
}



void Ball::setSpeed(float x,float y){
    dx = x;
    dy = y;
}
void Ball::setRadius(int radius){
    r = radius;
}
void Ball::setPosition(float x, float y){
    ballX = x;
    ballY = y;
}

/*void Ball::setBorder(Border *b){
    border = b;
}*/

void Border::setPosition(int x, int y, int width, int height){
    rectX = x;
    rectY = y;
    rectWidth = width;
    rectHeight = height;
}

void Ball::startMoving(){
    timer->start(t);
}

void Ball::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event); // 调用基类的paintEvent函数

    QPainter painter(this);
    draw(painter); // 调用draw函数进行绘制
}

void Ball::draw(QPainter& painter) const {
    // 绘制矩形框
    painter.drawRect(border->getX(), border->getY(), border->getWidth(), border->getHeight());

    // 绘制小球
    painter.setBrush(Qt::red);//设置画刷为红色
    painter.drawEllipse(QPointF(ballX, ballY), r, r);
}

void Ball::updateBallPosition(){
    // 使用border指针访问Border类的公共接口
    int rectX = border->getX();
    int rectY = border->getY();
    int rectWidth = border->getWidth();
    int rectHeight = border->getHeight();

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
      update();//重绘窗口
}

Ball::~Ball()//Ball类的析构函数
{
    delete ui;
    /*timer->stop();
    delete timer;*/
    delete border;

}
