#include "mainwindow.h"
#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_login_clicked()
{
    // Get the input
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    hide();
    parentWidget()->show();
}
