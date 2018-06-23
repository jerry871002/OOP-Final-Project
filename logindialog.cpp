#include <QFileInfo>
#include <QMessageBox>
#include "user.h"
#include "mainwindow.h"
#include "logindialog.h"
#include "ui_mainwindow.h"
#include "ui_logindialog.h"

#define PATH_TO_DB "/Users/Jerry_Yang/Desktop/oop-final-project/users-info.db"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(PATH_TO_DB);
    QFileInfo checkFile(PATH_TO_DB);

    if (checkFile.isFile())
    {
        if (myDB.open())
            ui->label_status->setText("[+]Connected to Database File");
        else
            ui->label_status->setText("[!]Database File exist but not opened");
    }
    else
    {
        ui->label_status->setText("[-]Database File doesn't exist");
    }
}

LoginDialog::~LoginDialog()
{
    delete ui;

    // Closing the connection to Database on exit
    myDB.close();
}

void LoginDialog::on_pushButton_login_clicked()
{
    // Get the input
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    // Enable to access methods or members from parent widget
    MainWindow* parent = qobject_cast<MainWindow*>(this->parent());

    // Check if the parent exist
    if (parent == 0)
    {
        ui->label_status->setText("[!]Parent widget doesn't exist");
        return;
    }

    // Check if Database is opened and connected
    if (!myDB.open())
    {
        ui->label_status->setText("[!]No connextion to DB");
        return;
    }

    QSqlQuery qry;
    if (qry.exec("SELECT username, password, first_name, last_name, can_encode, can_decode \
                FROM users_info WHERE username=\'" + username + "\' AND password =\'" + password + "\'"))
    {
        if (qry.next())
        {
            ui->label_status->setText("[+]Valid username and password");
            QString msg  = "Welcome! " + qry.value(2).toString() + " " + qry.value(3).toString();

            parent->currentUser = new User(qry.value(2).toString(), qry.value(3).toString(),
                                           qry.value(4).toBool(), qry.value(5).toBool());

            parent->ui->label_username->setText("Current User: " + qry.value(2).toString() + " " + qry.value(3).toString());

            ui->lineEdit_username->clear();
            ui->lineEdit_password->clear();

            hide();
            parent->show();
            QMessageBox::information(this, "Login success", msg);
        }
        else
        {
            ui->lineEdit_password->selectAll();
            ui->label_status->setText("[-]Wrong username or password");
        }
    }
}

void LoginDialog::on_pushButton_clear_clicked()
{
    ui->lineEdit_username->clear();
    ui->lineEdit_password->clear();
}
