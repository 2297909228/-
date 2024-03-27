#include "led.h"
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>

led::led()
{

}

led::~led() {

}

void led::ChangedLED(){
    /* 在设置 LED 状态时先读取 */
#if __arm__
    system("echo none > /sys/class/leds/sys-led/trigger");
#endif
    QFile LedFile;

    bool isLed = false;

    LedFile.setFileName("/sys/devices/platform/leds/leds/sys-led/brightness");
    if (!LedFile.exists()) {
        qDebug() << "未获取到 LED 设备！\n";
        isLed = false;
    }

    if(!LedFile.open(QIODevice::ReadWrite)) {
        qDebug() << LedFile.errorString();
    }

    QTextStream in(&LedFile);

    /* 读取文件所有数据 */
    QString buf1 = in.readLine();

    /* 打印出读出的值 */
    qDebug() << "buf: " << buf1 <<endl;
    LedFile.close();
    if (buf1 == "1") {
        //pushButton->setText("LED 点亮");
        isLed = true;
    } else {
        //pushButton->setText("LED 熄灭");
        isLed = false;
    }

    /* 如果文件不存在，则返回 */
    if (!LedFile.exists()) {
        return;
    }

    if(!LedFile.open(QIODevice::ReadWrite)) {
        qDebug() << LedFile.errorString();
    }

    QByteArray buf[2] = {"0", "1"};

    /* 写 0 或 1 */
    if (isLed)
        LedFile.write(buf[0]);
    else
        LedFile.write(buf[1]);

    /* 关闭文件 */
    LedFile.close();
}

