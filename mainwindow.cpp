
#include "mainwindow.h"
#include "connected.h"
#include "four.h"
#include "qtimer.h"
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
    if (arduino.connect_arduino("COM5") == 0) {
        qDebug() << "Arduino connected successfully.";
    } else {
        qDebug() << "Failed to connect to Arduino.";
    }

    // Use a timer to periodically read RFID data
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::readRFID);
    timer->start(100); // Check for new data every 100ms
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


void MainWindow::on_pushButton_5_clicked()
{
    this->hide();
    connected *c = new connected(this);
    c->show();
}





void MainWindow::on_pushButton_6_clicked()
{
    this->hide();
    four *f =new four(this);
    f->show();
}
void MainWindow::readRFID() {
    QString data = arduino.read_from_arduino();
    if (!data.isEmpty()) {
        qDebug() << "UID received:" << data;
        // Update UI or perform actions with the received UID
        ui->label_5->setText("Scanned UID: " + data); // Example UI update
    }
}
