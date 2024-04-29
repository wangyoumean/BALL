#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QPainter>


class Ball;//前置声明Ball类

class MyWidget : public QWidget {
    Q_OBJECT
public:
   explicit MyWidget(QWidget *parent = nullptr) ;//explicit用于避免出现隐式类型转换

protected:
    void paintEvent(QPaintEvent *event) override ; //override表明该成员函数用来重写基类中的虚函数

    float g; //重力加速度
    float q;//碰撞系数
    int rectX; // 矩形框左上角 x 坐标
    int rectY; // 矩形框左上角 y 坐标
    int rectWidth; // 矩形框宽度
    int rectHeight; // 矩形框高度
    int t;//定时器更新时间

    Ball *ballObject;//添加一个Ball对象指针
};


class Ball :public QObject , virtual protected MyWidget{
    Q_OBJECT

public:
    Ball(QWidget *parent = nullptr) :QObject(parent){}
    void setPosition();
    void setSpeed();
    void updateBallPosition() ;//改变小球位置的函数
    float getballX() const{return ballX;}//让
    float getballY() const{return ballY;}
    float getr() const{return r;}

private:
    float ballX; // 小球 x 坐标
    float ballY; // 小球 y 坐标
    int r;  //小球半径
    float dx; // 小球水平方向速度
    float dy; // 小球垂直方向速度


};
#endif // MYWIDGET_H
