#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSound>
#include <QDebug>
#include <QPainter>
#include <mypushbutton.h>
#include "chooselevelscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //重写绘图事件
    void paintEvent(QPaintEvent * ev);

private slots:
    void on_actionquit_X_triggered();

private:
    Ui::MainWindow *ui;
    ChooseLevelScene * chooseLevel;
};

#endif // MAINWINDOW_H
