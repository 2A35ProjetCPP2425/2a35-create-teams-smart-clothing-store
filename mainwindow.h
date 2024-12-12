#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "arduino.h"
#include "videobackground.h"
#include "stock.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);  // Constructor
    ~MainWindow();  // Destructor

private slots:
    void on_pushstock_clicked();

    void readRFID();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    stock *S;
    VideoBackground *videoBackground;      // Video background object for the first container
    VideoBackground *videoBackground_2;    // Video background object for the second container
    Arduino arduino;
};

#endif // MAINWINDOW_H
