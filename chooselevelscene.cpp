#include "chooselevelscene.h"
#include "ui_chooselevelscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseLevelScene)
{
    ui->setupUi(this);
    this->initLevelChooseBtn();
    this->initBackbtn();

}


ChooseLevelScene::~ChooseLevelScene()
{
    delete ui;
}

void ChooseLevelScene::on_actionquit_triggered()
{
    this->close();
}
void ChooseLevelScene::initBackbtn()
{
    //创建返回音乐
    QSound *backBtnSound=new QSound(":/res/BackButtonSound.wav", this);
    //创建返回按钮
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->setGeometry(300,540,77,32);
    connect(backBtn,&MyPushButton::clicked,[=](){
        backBtnSound->play();
        QTimer::singleShot(300,this,[=](){
            emit backButtonClicked();
        });
    });

}
void ChooseLevelScene::initLevelChooseBtn()
{
    QSound * sound = new QSound(":/res/TapButtonSound.wav", this);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            QPushButton * btn = new QPushButton(QString::number( i *4+j+1 ), this);
            btn->setGeometry(64 + 57*j + 15 * j , 180 + 57*i + i * 15, 57, 57);
            btn->setStyleSheet("QPushButton{border-image : url(:/res/LevelIcon.png);}");
            connect(btn, &QPushButton::clicked, [=](){
                sound->play();
                playScene = new PlayScene(i*4+j+1,this);
                this->hide();
                playScene->show();
                connect(playScene,&PlayScene::playSceneBack,[=](){
                    playScene->close();
                    this->show();
                });
            });
        }
    }   
}
void ChooseLevelScene::paintEvent(QPaintEvent * )
{
    //创建画家
    QPainter painter(this);
    //创建pixmap
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    //画pixmap
    painter.drawPixmap(0,0,pix.scaled(this->size()));

    pix.load(":/res/Title.png");
    painter.drawPixmap(20,40,pix.width()*3/4,pix.height()*3/4,pix);
}
