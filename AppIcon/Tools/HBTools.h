#ifndef HBTOOLS_H
#define HBTOOLS_H

#include <QObject>

class HBTools : public QObject
{
    Q_OBJECT
public:
    explicit HBTools(QObject *parent = nullptr);

    static QStringList cmdStrListWithNum(int num, QString from, QString to);
    static QStringList cmdStrListWithNums(QList<int> nums, QString from, QString to);



signals:

};

#endif // HBTOOLS_H
