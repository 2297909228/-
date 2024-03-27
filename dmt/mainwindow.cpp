#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_music_clicked()
{
    music *m=new music();
    this->close();
    m->show();

}

void MainWindow::on_video_clicked()
{
    video *v=new video();
    this->close();
    v->show();
}
