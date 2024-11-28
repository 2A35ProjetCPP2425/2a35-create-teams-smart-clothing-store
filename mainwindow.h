#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"employe.h"
#include "qsortfilterproxymodel.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &email, QWidget *parent = nullptr);  // Explicit keyword added
    ~MainWindow();
private:
    void on_ajouterButton_clicked();
    void on_supprimerButton_clicked();
    // Function to modify an employee
    void on_modifierButton_clicked();
    void on_trierButton_clicked();
    void setupSearchFunctionality();
    void on_telechargerButton_clicked();
    void displayPosteStatistics();
    void displayEmployeeStatsByYear();
    void populateEmployeeInfo();
    void on_idEmpChanged();
    void on_soumettreButton_clicked();
    void refreshTableView();
    void onSelectionChanged(const QItemSelection &selected);
    void onIdChanged();
    void on_acceptation_clicked();
    void on_refuser_clicked();
    void onUpdateTypeCongeClicked();

private:
    Ui::MainWindow *ui;
    QSortFilterProxyModel *proxyModel;
    Employe cmp;
};
#endif // MAINWINDOW_H
