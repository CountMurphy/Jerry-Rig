#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QDialog>
#include<QSettings>

namespace Ui {
class ProcessManager;
}

class ProcessManager : public QDialog
{
    Q_OBJECT

public:
    explicit ProcessManager(QWidget *parent = 0, QSettings *settings = 0);//also needs some kind of container or args for params
    ~ProcessManager();

private:
    Ui::ProcessManager *ui;
};

#endif // PROCESSMANAGER_H
