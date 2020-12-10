#include "ictrl.h"

QObject* ICtrl::getConnectPage() {
    return pConnectQml;
};

void ICtrl::setConnectPage(QObject &connectQml) {
    pConnectQml = &connectQml;

    // Connect Cpp to Qml
    //connect(this, SIGNAL(), pConnectQml, SLOT());
    //connect(pConnectQml, SIGNAL(), this, SLOT());
};
