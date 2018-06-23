#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QFileInfo>
#include <QMessageBox>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_clear_clicked();

private:
    Ui::LoginDialog *ui;

    QSqlDatabase myDB;
};

#endif // LOGINDIALOG_H
