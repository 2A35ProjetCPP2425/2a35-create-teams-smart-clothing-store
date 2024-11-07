#ifndef VIDEOBACKGROUND_H
#define VIDEOBACKGROUND_H

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QWidget>

class VideoBackground : public QWidget {
    Q_OBJECT

public:
    VideoBackground(QWidget *parent = nullptr, QWidget *videoContainer = nullptr);  // Constructor
    void playVideo(const QString &filePath);     // Method to play the video

private:
    QVideoWidget *videoWidget;   // Widget to display video
    QMediaPlayer *mediaPlayer;   // Player to control video playback

private slots:
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status); // Handle media status for looping
};

#endif // VIDEOBACKGROUND_H

