#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include <QFileDialog>
#include <QDir>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    int w = ui->label_pic_encode->width();
    int h = ui->label_pic_encode->height();
    ui->label_pic_encode->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

void MainWindow::on_pushButton_choosefile_decode_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Choose an image", QDir::homePath(), "*.png");
    ui->lineEdit_filepath_decode->setText(file_name);
    QPixmap pix(file_name);
    int w = ui->label_pic_decode->width();
    int h = ui->label_pic_decode->height();
    ui->label_pic_decode->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}
