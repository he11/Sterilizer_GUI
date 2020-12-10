#include "manualtimectrl.h"

ManualTimeCtrl::ManualTimeCtrl() {
    Init();
}

ManualTimeCtrl::~ManualTimeCtrl() {}

void ManualTimeCtrl::Init() {
    setTumbler(0, 0, 0, 0);
}

void ManualTimeCtrl::reqToStore() {
    int setTime[4] = {hoursVal, minutesVal, baseVal, durationVal};
    emit storeSetTime(MENUAL_TIME_SETTING, setTime);
}

void ManualTimeCtrl::displayError() {
    static bool displayErr = false;
    if (!displayErr) {
        errState = true;
        emit errorOnOff();
        QTimer::singleShot(1000, this, [&]() { errState = false; emit errorOnOff(); displayErr = false; });
        displayErr = true;
    }
}

bool ManualTimeCtrl::getErrState() const {
    return errState;
}

void ManualTimeCtrl::setTumbler(const int &hours, const int &minutes, const int &base, const int &duration) {
    hoursVal = hours;
    minutesVal = minutes;
    baseVal = base;
    durationVal = duration;

    emit updateTumbler();
}

int ManualTimeCtrl::getHours() const {
    return hoursVal;
}

void ManualTimeCtrl::setHours(const int &currentVal) {
    hoursVal = currentVal;
#ifdef DEBUG_MODE
    //cout << "cpp: [" << this->metaObject()->className() << "]" << "Current Hours Value: " << hoursVal << endl;
#endif
}

int ManualTimeCtrl::getMinutes() const {
    return minutesVal;
}

void ManualTimeCtrl::setMinutes(const int &currentVal) {
    minutesVal = currentVal;
#ifdef DEBUG_MODE
    //cout << "cpp: [" << this->metaObject()->className() << "]" << "Current Minutes Value: " << minutesVal << endl;
#endif
}

int ManualTimeCtrl::getBase() const {
    return baseVal;
}

void ManualTimeCtrl::setBase(const int &currentVal) {
    baseVal = currentVal;
#ifdef DEBUG_MODE
    //cout << "cpp: [" << this->metaObject()->className() << "]" << "Current Base Value: " << baseVal << endl;
#endif
}

int ManualTimeCtrl::getDuration() const {
    return durationVal;
}

void ManualTimeCtrl::setDuration(const int &currentVal) {
    durationVal = currentVal;
#ifdef DEBUG_MODE
    //cout << "cpp: [" << this->metaObject()->className() << "]" << "Current Duration Value: " << durationVal << endl;
#endif
}
