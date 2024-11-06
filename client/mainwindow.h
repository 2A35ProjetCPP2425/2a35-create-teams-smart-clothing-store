#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButtonajouter_clicked();
  //  int getClientCIN();
    void on_pushButtonasupprimer_clicked();
    void on_tableView_clicked();
    void on_pushButton_modif_clicked();

     //void on_pushButton_modif_clicked();
private:
    Ui::MainWindow *ui;
   Client csupp;
 int getClientCIN();
};

#endif // MAINWINDOW_H
