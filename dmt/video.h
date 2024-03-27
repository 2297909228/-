#ifndef VIDEO_H
#define VIDEO_H

#include <QMainWindow>
#include "mainwindow.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <QDebug>
#include <QSlider>
#include <QLabel>
#include "led.h"


namespace Ui {
class video;
}

class video : public QMainWindow
{
    Q_OBJECT

public:
    explicit video(QWidget *parent = nullptr);
    ~video();

private slots:
    void on_back_clicked();

    void on_play_clicked();

    void on_open_clicked();

    void UpdateTime(qint64 position);

    void on_next_clicked();

private:
    Ui::video *ui;

    QMediaPlayer* pPlayer;
    QMediaPlaylist* pPlayerList;
    QVideoWidget* pVideoWidget;
    qint64 m_durationTime;
    qint64 m_positionTime;

        bool isPlaying;

};

#endif // VIDEO_H
