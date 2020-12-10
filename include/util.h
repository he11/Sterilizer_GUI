#ifndef UTIL_H
#define UTIL_H

#include <Qt>
#include <QObject>
#include <QString>
#include <QVariant>

#include <iostream>

using namespace std;

QString toQString(char* const &);
string fromQString(QString const &);

string getObjectName(const QObject *);
QObject* getObjectIns(const QObject *, QString);
QObject* getDirObjectIns(const QObject *, QString);

char* genUuid(char* const &);

#endif // UTIL_H
