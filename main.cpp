#include "widget.h"

#include <QApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>
QMediaPlayer *musicPlayer;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QMediaPlaylist *playlist = new QMediaPlaylist();
    QDir musicDir = QCoreApplication::applicationDirPath() + "/music/";
    QStringList musicList = musicDir.entryList(QStringList() << "*.mp3" << "*.MP3" << "*.wav" << "*.WAV",QDir::Files);
    foreach(QString filename, musicList) {
        playlist->addMedia(QUrl(QCoreApplication::applicationDirPath() + "/music/" + filename));
    }

    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    musicPlayer = new QMediaPlayer();
    musicPlayer->setPlaylist(playlist);
    musicPlayer->setVolume(5);
    musicPlayer->play();
    w.show();

    return a.exec();

}

void Widget::keyPressEvent( QKeyEvent *k )
{
    switch ( k->key() ) {
    case Qt::Key::Key_F4:
        musicPlayer->playlist()->previous();
        break;
    case Qt::Key::Key_F5:
        musicPlayer->playlist()->next();
        break;
    case Qt::Key::Key_F1:
        if (musicPlayer->state() == QMediaPlayer::PlayingState)
            musicPlayer->pause();
        else
            musicPlayer->play();
        break;
    case Qt::Key::Key_F2:
        if (musicPlayer->volume() >= 5)
            musicPlayer->setVolume(musicPlayer->volume()-5);
        break;
    case Qt::Key::Key_F3:
        if (musicPlayer->volume() <= 95 )
            musicPlayer->setVolume(musicPlayer->volume()+5);
        break;
    }
}
