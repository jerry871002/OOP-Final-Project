#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
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
    hide();

    delete currentUser;

    // Move the login dialog to the center of the screen
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - logindialog->width()) / 2;
    int y = (screenGeometry.height() - logindialog->height()) / 2;
    logindialog->move(x, y);

    logindialog->show();
}

void MainWindow::on_pushButton_encode_clicked()
{

}

void MainWindow::on_pushButton_decode_clicked()
{

}
