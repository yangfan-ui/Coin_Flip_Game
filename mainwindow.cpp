#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //chooseLevel界面back按钮
    chooseLevel=new ChooseLevelScene(this);
    connect(chooseLevel,&ChooseLevelScene::backButtonClicked,[=](){
        chooseLevel->close();
        this->show();
    });

    QPixmap pix;
    pix.load(":/res/MenuSceneStartButton.png");
    int x=(this->width()-pix.width())/2;
    int y=this->height()-pix.width()-50;
    //创建开始音乐
    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);
    //创建开始按钮
    MyPushButton *startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->setGeometry(x,y,pix.width(),pix.height());
    connect(startBtn,&QPushButton::clicked,[=](){
        startSound->play();
        startBtn->jump(true);
        startBtn->jump(false);
        //延时进入到选择关卡场景中
        QTimer::singleShot(500,this,[=](){
            //设置chooseScene场景的位置
            chooseLevel->setGeometry(this->geometry());
            //自身隐藏
            this->hide();
            //显示选择关卡场景
        chooseLevel->show();
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionquit_X_triggered()
{
    this->close();
}

void MainWindow::paintEvent(QPaintEvent * ev)
{
    //创建画家
    QPainter painter(this);
    //画背景图
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,pix.scaled(this->size()));

    pix.load(":/res/Title.png");
    painter.drawPixmap(20,30,pix.width()*3/4,pix.height()*3/4,pix);
}
