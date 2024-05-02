#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QObject>

// 独立的Border类
class Border {
public:
    Border(int x , int y , int width , int height ){
    rectX = x;
    rectY = y;
    rectWidth = width;
    rectHeight = height;
    }
    void setPosition(int x, int y);
    int getX() const { return rectX; }
    int getY() const { return rectY; }
    int getWidth() const { return rectWidth; }
    int getHeight() const { return rectHeight; }
protected:
    int rectX;
    int rectY;
    int rectWidth;
    int rectHeight;
};

// 独立的Ball类
class Ball : public QObject {
    Q_OBJECT
public:
    explicit Ball(Border* border, float q,float g,int t, QObject *parent = nullptr);
    void updatePosition(); // 更新小球位置的方法
    void setPosition(float x,float y){
        ballX = x;
        ballY = y;
    }
    void setSpeed(float vx,float vy){
        dx = vx;
        dx = vy;
    }// 设置小球速度
    float ballX; // 小球 x 坐标
    float ballY; // 小球 y 坐标
    int r;
    float dx;
    float dy;
signals:
    void positionChanged(); // 当小球位置改变时发出的信号

private:
    Border* border; // 指向Border对象的指针
    float g;
    float q;
    int t;
};

// MyWidget类
class MyWidget : public QWidget {
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

private:
    float g; //重力加速度
    float q; //碰撞系数
    int t; //定时器更新时间
    QTimer *timer; // 定时器
    Ball *ball; // 小球对象
    Border *border; // 矩形框对象
};

#endif // MYWIDGET_H
