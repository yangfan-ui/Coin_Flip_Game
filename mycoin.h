#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>
#include <QDebug>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QString imgPath);
    //初始化金币
    void initObject(QString imagePath);
    //重写鼠标按下时间
    void mousePressEvent(QMouseEvent *e);
    //金币翻转
    void changeCoin();
    //状态标志位
    bool mIsGold;
    bool mIsAnimation;
    //当前按钮的行列编号
    int i;
    int j;
    //输赢的标志
    bool isWin;
signals:

public slots:

private:
    QTimer * timerGold; //金币翻银币的定时器
    QTimer * timerSilver; //银币翻金币的定时器
    int Min;
    int Max;
};

#endif // MYCOIN_H
