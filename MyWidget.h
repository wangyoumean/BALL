#ifndef MYWIDGET_H
#define MYWIDGET_H


#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QPainter>

class MyWidget : public QWidget {
    Q_OBJECT
public:
    MyWidget(QWidget *parent = nullptr) ;

protected:
    void paintEvent(QPaintEvent *event) override; //override表明该成员函数用来重写基类中的虚函数


private slots:
        void updateBallPosition();//这里只声明函数
        //4.19:迁移完成，再次说明，出现链接问题，请先清除，再重新构建

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


};



#endif // MYWIDGET_H
