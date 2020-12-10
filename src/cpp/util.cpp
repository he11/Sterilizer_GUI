#include "util.h"
#include <random>
#include <QThread>
QString toQString(char* const &cString) {
    return QString::fromUtf8(cString);
}

string fromQString(QString const &qString) {
    return qString.toUtf8().toStdString();
}

string getObjectName(const QObject* qObject) {
    return fromQString(qObject->objectName());
}

QObject* getObjectIns(const QObject* qObject, QString target) {
    return qObject->findChild<QObject *>(target);
}

QObject* getDirObjectIns(const QObject* qObject, QString target) {
    return qObject->findChild<QObject *>(target, Qt::FindDirectChildrenOnly);
}

char* genUuid(char* const &container) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 65535);
    int res = sprintf(container, "%04x%04x-%04x-%04x-%04x-%04x%04x%04x", \
                      dis(gen), dis(gen), dis(gen), \
                      (dis(gen) & 0x0fff) | 0x4000, \
                      (dis(gen) & 0x3fff) | 0x8000, \
                      dis(gen), dis(gen), dis(gen));

    return (res != 36)? nullptr : container;
}
