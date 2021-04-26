#include "playscene.h"
#include "ui_playscene.h"

PlayScene::PlayScene(int level,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayScene),
    level(level)
{
    ui->setupUi(this);
    QString title=QString("翻金币第%1关").arg(level);
    this->setWindowTitle(title);
    this->initBackBtn();
    this->initCoin();
}

PlayScene::~PlayScene()
{
    delete ui;
}

void PlayScene::on_actionquit_triggered()
{
    this->close();
}
void PlayScene::initBackBtn()
{
    //创建返回按钮背景音乐
    QSound * backBtnSound = new QSound(":/res/BackButtonSound.wav", this);
    //创建返回按钮
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    //设置父类
    backBtn->setParent(this);
    //设置位置和大小
    backBtn->setGeometry(300,540,77,32);
    //关联槽函数
    connect(backBtn,&MyPushButton::clicked,[=](){
        backBtnSound->play();
        QTimer::singleShot(300,this,[=](){
            emit playSceneBack();
        });
    });
}
void PlayScene::initCoin()
{
    dataConfig data;
    QSound * coinFlipSound = new QSound(":/res/ConFlipSound.wav",this);
    QSound * winSound = new QSound(":/res/LevelWinSound.wav");
    //通过当前的level找到dataConfig中的二维数组
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->coinData[i][j]= data.mData.value(this->level).at(i).at(j);
//            qDebug() << data.mData[this->level][i][j];
        }
    }
    //胜利背景图
    QLabel * successLabel = new QLabel(this);
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    successLabel->setPixmap(pix);
    successLabel->setFixedSize(pix.size());
    successLabel->move((this->width()-pix.width())/2,-pix.height());

    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            //创建金币
            QString imgPath;
            if ( 1 == this->coinData[i][j] ) {
                imgPath = ":/res/Coin0001.png";
            } else {
                imgPath = ":/res/Coin0008.png";
            }

            MyCoin * coin = new MyCoin(imgPath);
            coin->setParent(this);
            coin->setGeometry(94+(50+5)*j,283+(50+5)*i, 46, 46);
            coin->mIsGold = this->coinData[i][j] == 1 ? true : false;
            //给金币属性赋值
            coin->i = i;
            coin->j = j;
            //将金币放到金币的二维数组中，方便后期维护
            coinArray[i][j] = coin;
            //点击金币，进行翻转
            connect(coin, &MyCoin::clicked, [=](){
                //播放翻金币的音效
                coinFlipSound->play();
                //点击按钮 将所有按钮先都禁用
               this->setWin();
                //翻转当前被点击的按钮
                coinArray[i][j]->changeCoin();
                coinData[i][j] = coinData[i][j] == 0 ? 1 : 0;
                QTimer::singleShot(300,this,[=](){
                    //翻转周围的按钮
                    this->coinClicked(i, j);
                    //翻完周围金币后，将所有金币解开禁用
                    this->setLose();
                    //判断输赢
                    if ( !this->isWin() ) {
                        return ;
                    }
                    winSound->play();
                    this->jump(successLabel);
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    //创建画家
    QPainter painter(this);
    //创建pixmap
    QPixmap pix;
    pix.load(":/res/MenuSceneBg.png");
    //画pixmap
    painter.drawPixmap(0,0,pix.scaled(this->size()));

    QString str=QString("Level:%1").arg(this->level);
    QFont font("Times New Roman",35,6,true);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(30,565,str);


    pix.load(":/res/BoardNode.png");
    for(int i=0;i<4;i++) {
      for(int j=0;j<4;j++) {
          painter.drawPixmap(92+(50+5)*j,280+(50+5)*i,pix); 
      }
    }

}
void PlayScene::coinClicked(int i,int j)
{
    //上面的金币翻转
    if ( i - 1 >= 0 ) {
        coinArray[i - 1][j]->changeCoin();
        coinData[i - 1][j] = coinData[i - 1][j] == 1 ? 0 : 1;
    }
    //下面的金币翻转
    if ( i + 1 < 4 ) {
        coinArray[i + 1][j]->changeCoin();
        coinData[i + 1][j] = coinData[i + 1][j] == 1 ? 0 : 1;
    }
    //左边的金币翻转
    if ( j - 1 >= 0 ) {
        coinArray[i][j - 1]->changeCoin();
        coinData[i][j - 1] = coinData[i][j - 1] == 1 ? 0 : 1;
    }
    //右边的金币翻转
    if ( j + 1 < 4 ) {
        coinArray[i][j + 1]->changeCoin();
        coinData[i][j + 1] = coinData[i][j + 1] == 1 ? 0 : 1;
    }
}

bool PlayScene::isWin()
{
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            if ( this->coinData[i][j] == 0 ) {
                return false;
            }
        }
    }
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            coinArray[i][j]->isWin = true;
        }
    }
    return true;
}

void PlayScene::jump(QLabel * label)
{
    QPropertyAnimation * animation = new QPropertyAnimation(label,"geometry");
    //起始位置和结束位置
    animation->setStartValue(QRect(label->x(), label->y(), label->width(), label->height()));
    animation->setEndValue(QRect(label->x(), label->y() + 150, label->width(), label->height()));

    //持续的时间
    animation->setDuration(1000);
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();
}
void PlayScene::setLose()
{
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            coinArray[i][j]->isWin = false;
        }
    }
}

void PlayScene::setWin()
{
    for ( int i = 0; i < 4; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            coinArray[i][j]->isWin = true;
        }
    }
}
