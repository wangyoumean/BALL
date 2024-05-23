#include "ball.h"
#include "ui_ball.h"

Ball::Ball(float ballX, float ballY, float dx, float dy,int r,  Border *mborder, QWidget *parent):QWidget(parent){
    //初始化对象
    this->ballX = ballX;
    this->ballY = ballY;
    this->dx = dx;
    this->dy = dy;
    this->r = r;
    this->mborder = mborder;
    g = 9.8; // 重力加速度
    q = 0.8; // 碰撞系数
    t = 16; // 假设定时器更新时间为16ms ，使程序以60帧运行

    timer = new QTimer(this);// 创建定时器对象
    connect(timer,&QTimer::timeout,this,&Ball::updateBallPosition);// 连接定时器的timeout信号到更新小球位置的槽函数

}

Border::Border(int rectX , int rectY , int rectWidth , int rectHeight){
    //初始化
    this->rectX = rectX;
    this->rectY = rectY;
    this->rectWidth = rectWidth;
    this->rectHeight = rectHeight;
}

bool Border::checkCollision(float x, float y,int r, Direction direction) {
    switch (direction) {
    case LEFT:
    //检查小球是否碰撞到矩形框的左边界
    //如果小球的左边缘（x - r）小于等于左边界的X坐标（rectX），则发生碰撞
        return x - r <= rectX;
    case RIGHT:
    //检查小球是否碰撞到矩形框的右边界
        return x + r >= rectX + rectWidth;
    case TOP:
    // 检查小球是否碰撞到矩形框的上方
        return y - r <= rectY;
    case BOTTOM:
    //检查小球是否碰撞到矩形框的底部
        return y + r >= rectY + rectHeight;
    default:
    //如果方向不匹配任何已知的方向，则不发生碰撞
        return false;
        }
    }

void Ball::startMoving(){
    timer->start(t);//设置定时器，循环时间为t，可在后面设定
}

void Ball::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event); // 调用基类的paintEvent函数
    QPainter painter(this);
    mborder->draw(painter);//调用Border类的painter方法绘制矩形框
    draw(painter);//调用Ball类的painter方法绘制小球
}

void Ball::draw(QPainter& painter) const {
    //绘制小球
    painter.setBrush(Qt::red);//设置画刷为红色
    painter.drawEllipse(QPointF(ballX, ballY), r, r);
}

void Border::draw(QPainter& painter) const {
    //绘制矩形框
    painter.drawRect(rectX, rectY, rectWidth, rectHeight);
}

void Ball::updateBallPosition(){
    //小球的运动
    ballX += dx;
    ballY += dy;

    //检查小球是否碰撞到矩形框的左边或右边
    if ((dx < 0 && mborder->checkCollision(ballX, ballY, r, LEFT)) ||
        (dx > 0 && mborder->checkCollision(ballX, ballY, r, RIGHT))) {
    //如果是，改变X方向上的速度
        dx = -dx * q;// 改变水平方向速度方向和大小
    }
    // 检查小球是否碰撞到矩形框的上边或下边（地面）
    if ((dy < 0 && mborder->checkCollision(ballX, ballY, r, TOP)) ||
        (dy > 0 && mborder->checkCollision(ballX, ballY, r, BOTTOM))) {
    // 如果是，改变Y方向上的速度
        dy = -dy * q;//改变竖直方向速度方向和大小
        ballY = mborder->rectY + mborder->rectHeight - 2*r;//防止小球掉出矩形框
    }
        dy += (g / 1000 * t);//每次更新小球位置时，垂直速度加上重力加速度,单位换算成秒
    update();//重绘窗口
}
