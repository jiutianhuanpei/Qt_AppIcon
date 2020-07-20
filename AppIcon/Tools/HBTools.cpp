#include "HBTools.h"
#include <QDir>

HBTools::HBTools(QObject *parent) : QObject(parent)
{

}

QStringList HBTools::cmdStrListWithNum(int num, QString from, QString to) {

    QString toDir = to + "/logo.iconset";
    QDir dir(toDir);
    if (!dir.exists()) {
        QDir().mkpath(toDir);
    }

    QString str1 = QString("sips -z %1 %1 %2 --out %3/icon_%1.png").arg(num).arg(from).arg(toDir);
    QString str2 = QString("sips -z %1 %1 %2 --out %3/icon_%1@2x.png").arg(num).arg(from).arg(toDir);

    return QStringList() << str1 << str2;
}

QStringList HBTools::cmdStrListWithNums(QList<int> nums, QString from, QString to) {

    QStringList list;

    for (int i = 0; i < nums.count(); i++) {
        QStringList temp = cmdStrListWithNum(nums[i], from, to);
        list.append(temp);
    }

    return list;
}
