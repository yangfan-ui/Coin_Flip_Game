#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QSound>
#include <QDebug>
#include <mypushbutton.h>
#include "playscene.h"

namespace Ui {
class ChooseLevelScene;
}

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseLevelScene(QWidget *parent = 0);
    ~ChooseLevelScene();
    //初始化选择关卡场景
    void initLevelChooseBtn();
    //初始化返回按钮
    void initBackbtn();
    //重写绘图事件
    void paintEvent(QPaintEvent * event);

private slots:
    void on_actionquit_triggered();
signals:
    void backButtonClicked();

private:
    Ui::ChooseLevelScene *ui;
    PlayScene * playScene;
};

#endif // CHOOSELEVELSCENE_H
