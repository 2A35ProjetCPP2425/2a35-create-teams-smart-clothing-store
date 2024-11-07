#include "videobackground.h"
#include <QUrl>
#include <QVBoxLayout>
#include <QMediaPlayer>

VideoBackground::VideoBackground(QWidget *parent, QWidget *videoContainer) : QWidget(parent) {
    // Initialize video widget and media player
    videoWidget = new QVideoWidget(videoContainer);  // Set video widget inside the container
    mediaPlayer = new QMediaPlayer(this);

    // Set the video widget as the output for the media player
    mediaPlayer->setVideoOutput(videoWidget);

    // Set a layout for the video container if it doesn't already have one
    if (videoContainer->layout() == nullptr) {
        QVBoxLayout *layout = new QVBoxLayout(videoContainer);
        layout->addWidget(videoWidget);
        videoContainer->setLayout(layout);
    }

    // Connect signal to handle looping
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &VideoBackground::handleMediaStatusChanged);
}

void VideoBackground::playVideo(const QString &filePath) {
    // Set the media source and play the video
    mediaPlayer->setSource(QUrl::fromLocalFile(filePath));
    mediaPlayer->play();
}

// Handle media status changes to implement looping
void VideoBackground::handleMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia) {
        // Restart the video to create a loop
        mediaPlayer->setPosition(0);
        mediaPlayer->play();
    } else if (status == QMediaPlayer::LoadingMedia || status == QMediaPlayer::BufferedMedia) {
        // Add handling for when the media is loading or buffering
        // For example, you could show a loading spinner if needed
    }
}

