#include "mycoin.h"

MyCoin::MyCoin(QString imgPath):isWin(false),mIsAnimation(false),
    Min(0), Max(8)

{
    this->initObject(imgPath);
    timerGold=new QTimer(this);
    timerSilver=new QTimer(this);
    connect(timerGold,&QTimer::timeout,[=](){
        Min++;
        QString imgPath=QString(":/res/Coin000%1.png").arg(Min);
        this->initObject(imgPath);
        if(Min==8) {
            Min=0;
            timerGold->stop();
            {
                mIsAnimation=false;
            }
        }
    });
    connect(timerSilver,&QTimer::timeout,[=](){
        Max--;
        QString imgPath=QString(":/res/Coin000%1.png").arg(Max);
        this->initObject(imgPath);
        if(Max==1) {
            Max=8;
            timerSilver->stop();
            {
                mIsAnimation=false;
            }
        }
    });

}
void MyCoin::initObject(QString imagePath)
{
    QPixmap pix;
    if(!pix.load(imagePath)) {
        qDebug()<<"MyCoin图片加载失败"<<imagePath;
        return ;
    }
    //设置默认大小
    this->setFixedSize(pix.width(),pix.height());
    //设置按钮边框为0
    this->setStyleSheet("QPushButton{border : 0px}");
    //设置图标
    this->setIcon(QIcon(pix));
    //设置图片大小
    this->setIconSize(pix.size());
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->mIsAnimation || this->isWin) {
        qDebug() << "无法点击";
        return ;
    }
    return QPushButton::mousePressEvent(e);
}

void MyCoin::changeCoin()
{
   if(this->mIsGold) {
       timerGold->start(50);
       this->mIsGold=false;
   } else {
       timerSilver->start(50);
       this->mIsGold=true;
   }
   this->mIsAnimation=true;
}
