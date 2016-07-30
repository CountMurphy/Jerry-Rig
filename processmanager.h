#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QDialog>
#include<QSettings>
#include<QProcess>

namespace Ui {
class ProcessManager;
}

class ProcessManager : public QDialog
{
    Q_OBJECT

public:
    explicit ProcessManager(QWidget *parent = 0, QSettings *settings = 0);//also needs some kind of container or args for params
    QProcess *converter;
    ~ProcessManager();
private slots:
    void readReady();

private:
    Ui::ProcessManager *ui;
};

#endif // PROCESSMANAGER_H
