#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "music.h"
#include "video.h"
#include <QMediaPlayer>
#include <QVideoWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_music_clicked();

    void on_video_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
