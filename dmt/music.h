#ifndef MUSIC_H
#define MUSIC_H

#include <QMainWindow>
#include "mainwindow.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <QDebug>
#include "led.h"
#include <QListWidgetItem>
#include <QSlider>
#include <QMouseEvent>

namespace Ui {
class music;
}

class music : public QMainWindow
{
    Q_OBJECT

public:
    explicit music(QWidget *parent = nullptr);
    ~music();

private slots:
    void on_back_clicked();

    void on_open_clicked();

    void on_play_clicked();

    void UpdateTime(qint64 position);


    void on_pushButton_clicked();



private:
    Ui::music *ui;

    QMediaPlayer* pPlayer;
    QMediaPlaylist* pPlayerList;
    QVideoWidget* pVideoWidget;
    qint64 m_durationTime;
    qint64 m_positionTime;


        bool isPlaying;
};

#endif // MUSIC_H
