#include "mypushbutton.h"
#include <QDebug>

MyPushButton::MyPushButton(QString normalPath,QString pressPath,QWidget *parent)
   :QPushButton(parent)
{
    //给类的成员变量赋值
    normalImgPath=normalPath;
    if(""==pressPath) {
        pressImgPath=normalImgPath;
    } else {
        pressImgPath=pressPath;
    }
    QString str=QString("QPushButton{border-image : url(%1);}").arg(normalImgPath);
    //设置按钮的背景图
    setStyleSheet(str);
}
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    QString str=QString("QPushButton{border-image : url(%1);}").arg(normalImgPath);
    //设置按钮的背景图
    setStyleSheet(str);
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    QString str=QString("QPushButton{border-image : url(%1);}").arg(pressImgPath);
    //设置按钮的背景图
    setStyleSheet(str);
    return QPushButton::mouseReleaseEvent(e);
}
void MyPushButton::jump(bool isDown)
{
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    if ( isDown ) {   //起始位置和结束位置
        animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
        animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    } else {
        animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
        animation->setEndValue(QRect(this->x(), this->y() , this->width(), this->height()));
    }
    //持续的时间
    animation->setDuration(200);
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
