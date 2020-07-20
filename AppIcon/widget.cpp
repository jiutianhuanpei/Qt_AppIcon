#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QPushButton>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QDir>
#include <iostream>
#include <QFile>
#include "Tools/HBTools.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("图标生成");

    iconDir = "logo.iconset";

    QString username = QDir::home().dirName();

    deskPath = QString("/Users/%1/Desktop").arg(username);

    connect(ui->btn_from, &QPushButton::clicked, this, &Widget::on_btn_from_clicked);
    connect(ui->btn_to, &QPushButton::clicked, this, &Widget::on_btn_to_clicked);
}


void Widget::on_btn_from_clicked()
{


    QString filePath = QFileDialog::getOpenFileName(this, "选择图标文件", deskPath, "(*.png)");

    if (filePath.isEmpty()) {

        QMessageBox::warning(this, "", "请选择一张图片");
        return;
    }

    m_imgPath = filePath;
    QFileInfo info(filePath);
    ui->name_lbl->setText(info.fileName());

}

void Widget::on_btn_to_clicked()
{
    if (m_imgPath.isEmpty()) {

        QMessageBox::warning(this, "", "请先选择一张图片");
        return;
    }

    QString toPath = QFileDialog::getExistingDirectory(this, "请选择一个目录", deskPath);
    if (toPath.isEmpty()) {

        QMessageBox::warning(this, "", "请选择目标存放的目录");
        return;
    }

    QStringList list = HBTools::cmdStrListWithNums(QList<int>() << 16 << 32 << 64 << 128 << 256 << 512, m_imgPath, toPath);

    qDebug() << list;

    for (int i = 0; i < list.count(); i++) {

        QString cmd = list[i];
        system(cmd.toStdString().c_str());
    }

    QString cmd = QString("cd %1").arg(toPath);
    system(cmd.toStdString().c_str());

    cmd = QString("iconutil -c icns %1").arg(toPath + "/logo.iconset");
    system(cmd.toStdString().c_str());

    cmd = QString("rm -rf %1/logo.iconset").arg(toPath);
    system(cmd.toStdString().c_str());
}



Widget::~Widget()
{
    delete ui;
}

