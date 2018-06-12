#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_choosefile_encode_clicked();
    void on_pushButton_choosefile_decode_clicked();

private:
    Ui::MainWindow *ui;
    LoginDialog *logindialog;
};

#endif // MAINWINDOW_H
