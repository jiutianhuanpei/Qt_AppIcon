#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QString deskPath;
    QString iconDir;
    QString m_imgPath;


    void on_btn_from_clicked();
    void on_btn_to_clicked();

    QStringList cmdStrListWithSize(QList<int> sizeNums);
    QStringList cmdStrWithNum(int num);

};
#endif // WIDGET_H
