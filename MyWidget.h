#ifndef MYWIDGET_H
#define MYWIDGET_H


#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QPainter>

class MyWidget : public QWidget {
    Q_OBJECT
public:
   explicit MyWidget(QWidget *parent = nullptr) ;//explicit用于避免出现隐式类型转换

protected:
    void paintEvent(QPaintEvent *event) override; //override表明该成员函数用来重写基类中的虚函数


private slots://关于是否采用public slot的问题，等写到控制按钮时再决定
        void updateBallPosition();//这里只声明函数
        //4.19:迁移完成，再次说明，出现链接问题，请先清除，再重新构建

private:
    int rectX; // 矩形框左上角 x 坐标
    int rectY; // 矩形框左上角 y 坐标
    int rectWidth; // 矩形框宽度
    int rectHeight; // 矩形框高度

    float ballX; // 小球 x 坐标
    float ballY; // 小球 y 坐标
    int r;
    float dx; // 小球水平方向速度
    float dy; // 小球垂直方向速度
    float g; //重力加速度
    float q;//碰撞系数
    int t;//定时器更新时间


};



#endif // MYWIDGET_H
