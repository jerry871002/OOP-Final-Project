#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDesktopWidget>
#include <QFileDialog>
#include <QPixmap>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    logindialog = new LoginDialog(this);
    logindialog->show();

    // Move the login dialog to the center of the screen
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - logindialog->width()) / 2;
    int y = (screenGeometry.height() - logindialog->height()) / 2;
    logindialog->move(x, y);

    hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_choosefile_encode_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Choose an image", QDir::homePath(), "*.png");
    ui->lineEdit_filepath_encode->setText(file_name);
    QPixmap pix(file_name);

    // Set the image to proper size
    int w = ui->label_pic_encode->width();
    int h = ui->label_pic_encode->height();
    ui->label_pic_encode->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

void MainWindow::on_pushButton_choosefile_decode_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Choose an image", QDir::homePath(), "*.png");
    ui->lineEdit_filepath_decode->setText(file_name);
    QPixmap pix(file_name);

    // Set the image to proper size
    int w = ui->label_pic_decode->width();
    int h = ui->label_pic_decode->height();
    ui->label_pic_decode->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

void MainWindow::on_pushButton_logout_clicked()
{
    logindialog->ui->label_status->setText("[+]Connected to Database File");
    delete currentUser;

    // Move the login dialog to the center of the screen
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - logindialog->width()) / 2;
    int y = (screenGeometry.height() - logindialog->height()) / 2;
    logindialog->move(x, y);

    hide();
    logindialog->show();
}

void MainWindow::on_pushButton_encode_clicked()
{
    if (currentUser->checkEncode())
    {
        QString file_name = ui->lineEdit_filepath_encode->text();
        QString messageToHide = ui->textEdit_hide->toPlainText();
        QString messageKey = ui->textEdit_key_encode->toPlainText();

        // Check if all neccessary information are provided
        if (!file_name.isEmpty() && !messageToHide.isEmpty() && !messageKey.isEmpty())
            currentUser->encode(file_name, messageToHide, messageKey);

    }
    else
    {
        QMessageBox::warning(this, "Not Authorized!", "Current user is not allowed to encode.");
    }
}

void MainWindow::on_pushButton_decode_clicked()
{
    if (currentUser->checkDecode())
    {
        QString file_name = ui->lineEdit_filepath_decode->text();
        QString messageKey = ui->textEdit_key_decode->toPlainText();

        // Check if all neccessary information are provided
        if (!file_name.isEmpty() && !messageKey.isEmpty())
            currentUser->decode(file_name, messageKey);
    }
    else
    {
        QMessageBox::warning(this, "Not Authorized!", "Current user is not allowed to decode.");
    }
}
