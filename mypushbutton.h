#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QPropertyAnimation>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(QString normalPath,QString pressPath="",QWidget *parent = 0);
    //重写鼠标按下和释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    //跳跃
    void jump(bool isDown);

    QString normalImgPath;
    QString pressImgPath;

signals:

public slots:

protected:

};

#endif // MYPUSHBUTTON_H
