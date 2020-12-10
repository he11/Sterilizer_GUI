#ifndef ICTRL_H
#define ICTRL_H

#include <QObject>
#include "common.h"

class ICtrl : public QObject
{
    Q_OBJECT

private:
    QObject* pConnectQml = nullptr;

public:
    QObject* getConnectPage();
    void setConnectPage(QObject &);


signals:
    virtual void storeSetTime(const int&, int* const &);

public slots:
};

#endif // ICTRL_H
