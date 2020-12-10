#include "steptimectrl.h"

StepTimeCtrl::StepTimeCtrl() {
    Init();
}

StepTimeCtrl::~StepTimeCtrl() {}

void StepTimeCtrl::Init() {
    setTumbler(0, 0, 5);
}

void StepTimeCtrl::loadPeriod(int period) {
    savedHours = period / 3600;
    savedMinutes = (period % 3600) / 60;
    emit updateSetVal();
}

void StepTimeCtrl::setTumbler(const int &hours, const int &minutesIdx, const int &mInterval) {
    hoursVal = hours;
    this->minutesIdx = minutesIdx;
    this->mInterval = mInterval;

    emit updateTumbler();
}

int StepTimeCtrl::getSavedHours() const {
    return savedHours;
}

int StepTimeCtrl::getSavedMinutes() const {
    return savedMinutes;
}

int StepTimeCtrl::getHours() const {
    return hoursVal;
}

void StepTimeCtrl::setHours(const int &currentVal) {
    hoursVal = currentVal;
#ifdef DEBUG_MODE
    cout << "cpp: [" << this->metaObject()->className() << "]" << "Current Hours Value: " << hoursVal << endl;
#endif
}

int StepTimeCtrl::getMinutes() const {
    return minutesIdx;
}

void StepTimeCtrl::setMinutes(const int &currentVal) {
    minutesIdx = currentVal;
#ifdef DEBUG_MODE
    cout << "cpp: [" << this->metaObject()->className() << "]" <<  "Current Minutes Value: " << minutesIdx * mInterval << endl;
#endif
}

int StepTimeCtrl::getMInterval() const {
    return mInterval;
}

void StepTimeCtrl::reqToStore() {
    int minutesVal = minutesIdx * mInterval;
    int interval = hoursVal * 3600 + (minutesVal) * 60;
    static bool displayErr = false;

    if (interval <= 86400) {
        savedHours = hoursVal;
        savedMinutes = minutesVal;
#ifdef DEBUG_MODE
        cout << "cpp: Repeat Interval: " << interval << endl;
#endif
        emit storeSetTime(STEP_TIME_SETTING, &interval);
        emit updateSetVal();
    } else if (!displayErr) {
        errState = true;
        emit errorOnOff();
        QTimer::singleShot(1000, this, [&]() { errState = false; emit errorOnOff(); displayErr = false; });
        displayErr = true;
    }
}

bool StepTimeCtrl::getErrState() const {
    return errState;
}
