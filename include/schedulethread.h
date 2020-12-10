#ifndef SCHEDULETHREAD_H
#define SCHEDULETHREAD_H

#include <QThread>
#include <QMutex>
#include <QTime>

#include "common.h"

typedef struct {
    int timeVal; // Since 00:00, seconds
    char timeStr[21];
    char rsvd[3] = {0,};
    int duration;
    char uuid[37];
} set_data_t;

typedef struct {
    int startTime;
    int keepTime;
    int nextIntv;
} schedule_data_t;

class ScheduleThread : public QThread
{
    Q_OBJECT

private:
    int current = 0;
    QMutex mutex;
    int* period = nullptr;
    vector<set_data_t>* pScheduleList = nullptr;
    vector<schedule_data_t> scheduleList;
    vector<schedule_data_t>::iterator schedule;

public:
    explicit ScheduleThread(vector<set_data_t> &, int&);
    ~ScheduleThread() override;

    void showAllSchedule();

signals:
    void runSterilization(int);

public slots:
    void getCurrentTime();
    void updatePeriod();
    void updateSchedule(bool, const int&);

protected:
    void load();
    void run() override;
};

#endif // SCHEDULETHREAD_H
