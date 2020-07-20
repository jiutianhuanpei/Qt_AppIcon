#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>

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

    QProcess *m_cmd;


    void on_btn_from_clicked();
    void on_btn_to_clicked();

};
#endif // WIDGET_H
