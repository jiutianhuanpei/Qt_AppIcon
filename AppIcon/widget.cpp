#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QPushButton>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QDir>
#include <iostream>

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

        QMessageBox::warning(this, "", "请先选择一张图片");
        return;
    }


    m_imgPath = filePath;
    QFileInfo info(filePath);
    ui->name_lbl->setText(info.fileName());

    QDir dir(iconDir);
    if (!dir.exists()) {
        QDir().mkdir(iconDir);
    }


}

void Widget::on_btn_to_clicked()
{

    if (m_imgPath.isEmpty()) {

        QMessageBox::warning(this, "", "请先选择一张图片");
        return;
    }

    QString path = QFileDialog::getExistingDirectory(this, "保存在这里", deskPath);

    if (path.isEmpty()) {
        QMessageBox::warning(this, "", "请选择保存的目录");
        return;
    }

    QString cmdStr = QString("mkdir %1").arg(iconDir);
    system(cmdStr.toStdString().c_str());

    QList<int> param;
    param << 16 << 32 << 64 << 128 << 256 << 512;
    QStringList list = cmdStrListWithSize(param);

    QFile file("tmp.sh");
    file.open(QIODevice::ReadWrite);

    QString text = "#1 /bin/sh\n";
    text += list.join("\n").toStdString().c_str();

    file.write(text.toStdString().c_str());

    file.close();
    system("chmod +x tmp.sh");
    system("./tmp.sh");

    cmdStr = QString("iconutil -c icns %1").arg(iconDir);

    system(cmdStr.toStdString().c_str());

    cmdStr = QString("cp logo.icns %1/logo.icns").arg(path);

    system(cmdStr.toStdString().c_str());

    cmdStr = QString("rm -rf tmp.sh %1 logo.icns").arg(iconDir);
    system(cmdStr.toStdString().c_str());
}


QStringList Widget::cmdStrListWithSize(QList<int> sizeNums)
{


    QStringList list;

    for (int i = 0; i < sizeNums.count(); i++) {

        int num = sizeNums[i];

        QStringList tmp = cmdStrWithNum(num);

        list.append(tmp);

    }
    return list;
}

QStringList Widget::cmdStrWithNum(int num)
{
    QString str1 = QString("sips -z %1 %1 %2 --out logo.iconset/icon_%1.png").arg(num).arg(m_imgPath);
    QString str2 = QString("sips -z %1 %1 %2 --out logo.iconset/icon_%1@2x.png").arg(num).arg(m_imgPath);

    return QStringList() << str1 << str2;
}


Widget::~Widget()
{
    delete ui;
}

