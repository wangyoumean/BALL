#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QPainter>


class Ball;//前置声明Ball类
class Border;

class MyWidget : public QWidget {
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr) ;//explicit用于避免出现隐式类型转换

    friend class Ball;
    private:
    void paintEvent(QPaintEvent *event) override ; //override表明该成员函数用来重写基类中的虚函数

    float g; //重力加速度
    float q;//碰撞系数
    int t;//定时器更新时间

    Ball *ball; // 指向 Ball 对象的指针
    Border *border;
    QTimer *timer; // 指向 QTimer 对象的指针



};

class Border {
public:
    void setPosition(int x , int y , int width , int height);
    void draw(QPainter& painter) const;
    friend class Ball;
protected:
    int rectX;//矩形框左上角x坐标
    int rectY;//矩形框左上角y坐标
    int rectWidth;//矩形框宽度
    int rectHeight;//矩形框高度

};

class Ball {

public:

    void setPosition(float x, float y);
    void setSpeed(float x,float y);
    void setRadius(int radius);
    void updateBallPosition() ;//改变小球位置的函数
    void draw(QPainter& painter) const;


private:
    float ballX; // 小球 x 坐标
    float ballY; // 小球 y 坐标
    int r;  //小球半径
    float dx; // 小球水平方向速度
    float dy; // 小球垂直方向速度
    MyWidget mywidget;
    Border border;

};
#endif // MYWIDGET_H
