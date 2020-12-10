#include "schedulethread.h"

ScheduleThread::ScheduleThread(vector<set_data_t> &scheduleList, int& period) {
    pScheduleList = &scheduleList;
    this->period = &period;
    load();

    // Timer to Get current time
    QTimer* secTimer = new QTimer();
    connect(secTimer, SIGNAL(timeout()), this, SLOT(getCurrentTime()));
    getCurrentTime();
    secTimer->start(1000);
}

ScheduleThread::~ScheduleThread() {}

void ScheduleThread::load() {
    schedule_data_t newSchedule;

    vector<set_data_t>::iterator setTime = pScheduleList->begin();
    while (setTime != pScheduleList->end()) {
        newSchedule.startTime = setTime->timeVal;
        newSchedule.keepTime = setTime->duration;
        newSchedule.nextIntv = 0;
        ++setTime;

        scheduleList.push_back(newSchedule);
    }

#ifdef DEBUG_MODE
    showAllSchedule();
#endif
}

void ScheduleThread::updatePeriod() {
    vector<schedule_data_t>::iterator schedule = scheduleList.begin();
    while (schedule != scheduleList.end()) {
        mutex.lock();
        schedule->nextIntv = 0;
        mutex.unlock();
        ++schedule;
    }
}

void ScheduleThread::updateSchedule(bool isAdd, const int& index) {
    if (isAdd) {
        set_data_t setTime = pScheduleList->at(static_cast<unsigned int>(index));
        schedule_data_t newSchedule;
        newSchedule.startTime = setTime.timeVal;
        newSchedule.keepTime = setTime.duration;
        newSchedule.nextIntv = 0;
        mutex.lock();
        scheduleList.insert(scheduleList.begin() + index, newSchedule);
        mutex.unlock();
    } else {
        mutex.lock();
        scheduleList.erase(scheduleList.begin() + index);
        mutex.unlock();
    }

    schedule = scheduleList.begin();

#ifdef DEBUG_MODE
    showAllSchedule();
#endif
}

void ScheduleThread::showAllSchedule() {
    int idx = 0;

    vector<schedule_data_t>::iterator schedule = scheduleList.begin();
    while (schedule != scheduleList.end()) {
        cout << "cpp: Schedule[" << idx << "]: Start Time[" << schedule->startTime \
             << "] Keep Time[" << schedule->keepTime << "] Next Interval[" \
             << schedule->nextIntv << "]" << endl;
        ++schedule;
        ++idx;
    }
}

void ScheduleThread::run() {
    schedule = scheduleList.begin();

    forever {
        if (schedule != scheduleList.end()) {
            // Execute the reserved schedule
            int runTime = schedule->startTime + schedule->nextIntv;
            if (current == runTime) {
                emit runSterilization(schedule->keepTime);
                if (*period) {
                    mutex.lock();
                    schedule->nextIntv += (runTime + *period < 86400)? *period : ~schedule->nextIntv + 1;
                    mutex.unlock();
                }
            } else if (*period && runTime < current ) {
                int interval = *period;
                while(runTime + interval < current) { interval += *period; };
                mutex.lock();
                schedule->nextIntv += (runTime + interval < 86400)? interval : ~schedule->nextIntv + 1;
                mutex.unlock();
            }
#ifdef DEBUG_MODE
            cout << "cpp: In Thread: Start[" << schedule->startTime << "] Keep[" << schedule->keepTime << "] Next[" << schedule->nextIntv << "] Period[" << *period  << "]" << endl;
#endif
            ++schedule;
        } else { schedule = scheduleList.begin(); sleep(1); }
        if (QThread::currentThread()->isInterruptionRequested()) { return; }
    }
}

void ScheduleThread::getCurrentTime() {
    QTime getTime = QTime::currentTime();
    current = getTime.msecsSinceStartOfDay()/1000;
#ifdef DEBUG_MODE
    cout << "cpp: Current Time: " << current << "sec" << endl;
#endif
}
