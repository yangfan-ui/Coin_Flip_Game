#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QSound>
#include <QDebug>
#include <QPixmap>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QAction>
#include <QDebug>
#include "dataconfig.h"
#include "mycoin.h"
#include "mypushbutton.h"

namespace Ui {
class PlayScene;
}

class PlayScene : public QMainWindow
{
    Q_OBJECT

public:
    PlayScene(int level,QWidget *parent = 0);
    ~PlayScene();
    //重写绘图事件
    void paintEvent(QPaintEvent *ev);
    //初始化返回按钮
    void initBackBtn();
    //初始化金币
    void initCoin();
    //金币翻转和状态更新
    void coinClicked(int i,int j);
    //判断是否胜利
    bool isWin();
    //赢了的图标动画
    void jump(QLabel * label);
    void setLose();
    void setWin();

private slots:
    void on_actionquit_triggered();

signals:
    void playSceneBack();

private:
    Ui::PlayScene *ui;
    int level;
    int coinData[4][4];
    MyCoin * coinArray[4][4];
};

#endif // PLAYSCENE_H
