#include "video.h"
#include "ui_video.h"
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QDebug>
#include <QListWidgetItem>
#include "led.h"
#include <QTime>
#include <QScreen>

static int state=0;

video::video(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::video)
{
    ui->setupUi(this);
    /* 获取屏幕的分辨率，Qt官方建议使用这
        * 种方法获取屏幕分辨率，防上多屏设备导致对应不上
        * 注意，这是获取整个桌面系统的分辨率
        */
       QList <QScreen *> list_screen =  QGuiApplication::screens();

       /* 如果是ARM平台，直接设置大小为屏幕的大小 */
   #if __arm__
       /* 重设大小 */
       this->resize(list_screen.at(0)->geometry().width(),
                    list_screen.at(0)->geometry().height());
       /* 默认是出厂系统的LED心跳的触发方式,想要控制LED，
        * 需要改变LED的触发方式，改为none，即无 */
       system("echo none > /sys/class/leds/sys-led/trigger");
   #else
       /* 否则则设置主窗体大小为800x480 */
       this->resize(800, 480);
   #endif


    pPlayer=new QMediaPlayer;
    pPlayerList=new QMediaPlaylist;
    pVideoWidget=new QVideoWidget(ui->player);

    pPlayer->setPlaylist(pPlayerList);
    pPlayer->setVideoOutput(pVideoWidget);

    pPlayerList->setPlaybackMode(QMediaPlaylist::Loop);//设置循环模式
    pPlayer->setPlaylist(pPlayerList);//获取将播放列表要播放的文件

    connect(this->pPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(UpdateTime(qint64)));
    connect(this->pPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(UpdateTime(qint64)));

}

video::~video()
{
    delete ui;
}

void video::on_back_clicked()
{
    this->pPlayer->stop();
    MainWindow *md =new MainWindow();
    this->close();
    md->show();
}

void video::on_open_clicked()
{
        QString strCurrentPaht = QDir::homePath();
        QString strDirTitle = "select video file.";
        QString strFileType = "All Files(*.*);;MP4 Files(*.mp4);;MKV Files(*.mkv)";

        QStringList fileList = QFileDialog::getOpenFileNames(this, strDirTitle, strCurrentPaht, strFileType);
        for(int i = 0;i<fileList.count();i++)
         {
             QString aFile = fileList.at(i);
             pPlayerList->addMedia(QUrl::fromLocalFile(aFile));
             QFileInfo fileInfo(aFile);
             ui->listWidget->addItem(fileInfo.fileName());  //用于显示
         }
         if(pPlayer->state()!=QMediaPlayer::PlayingState)
         {
             pPlayerList->setCurrentIndex(0);
         }


}


void video::on_play_clicked()
{
    pVideoWidget->resize(ui->player->size());

    if(state==0){
        this->pPlayer->play();
        this->isPlaying=true;
        state=1;
}

    else{
        this->pPlayer->pause();
        this->isPlaying=false;
        state=0;
    }
}

void video::UpdateTime(qint64 position) {
    this->m_positionTime = position;
    QTime currentTime(0,0,0);
    currentTime = currentTime.addMSecs(position);

    this->m_durationTime = this->pPlayer->duration();

    this->ui->horizontalSlider->setMaximum(this->m_durationTime / 1000);
    this->ui->horizontalSlider->setValue(this->m_positionTime / 1000);

    if(this->isPlaying) {
        led::ChangedLED();
    }

    QTime totalTime(0,0,0);
    totalTime = totalTime.addMSecs(this->m_durationTime);

    QString currentTimeString = currentTime.toString("hh:mm:ss");
    QString totalTimeString = totalTime.toString("hh:mm:ss");

    this->ui->timelabel->setText(currentTimeString+"/"+totalTimeString);
}

void video::on_next_clicked()
{
    pPlayer->stop();
    int count = pPlayerList->mediaCount();
    if (0 == count)
        return;

    /* 列表下一个 */
    pPlayerList->next();
    pPlayer->play();
}
