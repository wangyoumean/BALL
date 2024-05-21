#ifndef BALL_H
#define BALL_H

#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class Ball; }
QT_END_NAMESPACE

class Border;//前置声明

class Ball : public QWidget
{
    Q_OBJECT
public:
    Ball(QWidget *parent = nullptr);
    void setPosition(float x, float y);
    void setSpeed(float x,float y);
    void setRadius(int radius);
    void updateBallPosition() ;//改变小球位置的函数
    void draw(QPainter& painter) const;
    ~Ball();
    void startMoving();//开始运动的函数
    //void setBorder(Border *b);
protected:
    void paintEvent(QPaintEvent *event) override;// 重写paintEvent函数
private:
    float ballX; // 小球 x 坐标
    float ballY; // 小球 y 坐标
    int r;  //小球半径
    float dx; // 小球水平方向速度
    float dy; // 小球垂直方向速度
    float g; //重力加速度
    float q;//碰撞系数
    int t;//定时器更新时间

    Ui::Ball *ui;
    Border *border;
    QTimer *timer;
};


class Border {
public:
    void setPosition(int x , int y , int width , int height);
    // 添加获取私有变量的公共接口
    int getX() const { return rectX; }
    int getY() const { return rectY; }
    int getWidth() const { return rectWidth; }
    int getHeight() const { return rectHeight; }

private:
    int rectX;//矩形框左上角x坐标
    int rectY;//矩形框左上角y坐标
    int rectWidth;//矩形框宽度
    int rectHeight;//矩形框高度

};



#endif // BALL_H
