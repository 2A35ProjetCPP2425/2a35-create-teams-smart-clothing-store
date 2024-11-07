#include "connected.h"
#include "ui_connected.h"

connected::connected(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::connected)
{
    ui->setupUi(this);
}

connected::~connected()
{
    delete ui;
}
