#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSoundEffect>
#include<QMediaPlayer>
#include <QAudioOutput>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
/*
    QSoundEffect *effect=new QSoundEffect;
    //effect->setSource(QUrl::fromLocalFile((":/awooga.wav")));
    effect->setSource(QUrl("qrc:/awooga.wav"));

    effect->setLoopCount(1);  //循环次数
    //effect->setVolume(0.25f); //音量  0~1之间
    effect->play();

*/
    QMediaPlayer*player = new QMediaPlayer;
    //QAudioOutput*audioOutput = new QAudioOutput;
    //player->setAudioOutput(audioOutput);

    player->setSource(QUrl("qrc:/awooga.wav"));
    //audioOutput->setVolume(0.5);
    player->play();
    connect(player, &QMediaPlayer::errorOccurred, [](QMediaPlayer::Error error){
        qDebug() << "Player error:" << error;
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
