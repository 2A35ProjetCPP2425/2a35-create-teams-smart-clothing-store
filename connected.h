#ifndef CONNECTED_H
#define CONNECTED_H

#include <QDialog>

namespace Ui {
class connected;
}

class connected : public QDialog
{
    Q_OBJECT

public:
    explicit connected(QWidget *parent = nullptr);
    ~connected();

private:
    Ui::connected *ui;
};

#endif // CONNECTED_H
