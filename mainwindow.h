#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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



private:
    Ui::MainWindow *ui;
    stock *S;
    VideoBackground *videoBackground;      // Video background object for the first container
    VideoBackground *videoBackground_2;    // Video background object for the second container
};

#endif // MAINWINDOW_H
