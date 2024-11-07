
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // Initialize the video background for the first container
    videoBackground = new VideoBackground(this, ui->videoContainer);
    QString videoPath = "C:\\Users\\chahi\\Downloads\\463945455_8246296228815154_3249887037257825995_n (1).mp4";
    videoBackground->playVideo(videoPath);

    // Initialize the video background for the second container
    videoBackground_2 = new VideoBackground(this, ui->videoContainer_2);
    QString videoPath2 = "C:/Users/chahi/Downloads/463975943_8649318385151407_60925717919105245_n (1).mp4";
    videoBackground_2->playVideo(videoPath2);
}

MainWindow::~MainWindow() {
    delete ui;
    delete videoBackground;   // Free memory for the first video background
    delete videoBackground_2; // Free memory for the second video background
}

void MainWindow::on_pushstock_clicked() {
    S = new stock(this);  // Create the stock window
    S->show();            // Show the window as a regular, non-modal window
    this->hide();         // Optionally hide the main window
}

