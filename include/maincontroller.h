#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QList>
#include <QThread>

#include "mainmenuctrl.h"
#include "schedulethread.h"

class MainController : public QGuiApplication
{
    Q_OBJECT
    Q_PROPERTY(bool displayList READ getDisplayList NOTIFY updateScreen)
    Q_PROPERTY(bool displayExit READ getDisplayExit NOTIFY updateScreen)
    Q_PROPERTY(bool errState READ getErrState NOTIFY errorOnOff)

private:
    QQmlApplicationEngine root;
    QObject* pRootQml = nullptr;
    QObject* pConnectQml = nullptr;
    QObject* pStackQml = nullptr;

    QObject* pScheduleListQml = nullptr;
    ScheduleThread* pScheduleThread = nullptr;
    vector<set_data_t> scheduleList;
    int period = 0;

    bool errState = false;
    bool displayList = true;
    bool displayExit = true;

    MainMenuCtrl* pMainMenuCtrl = nullptr;

public:
    explicit MainController(int &, char **);
    ~MainController();

    const QObject* getConnectPage();
    void setConnectPage(QObject &);

    char* getUuid(unsigned int);
    int getSetTimeVal(unsigned int);

    bool getDisplayList();
    bool getDisplayExit();
    bool getErrState() const;

    Q_INVOKABLE unsigned int getListSize();
    Q_INVOKABLE QString getSetTimeStr(unsigned int);
    Q_INVOKABLE void rmSetTime(unsigned int);
    Q_INVOKABLE void exitApp();
    Q_INVOKABLE void stopSterilization();

signals:
    void updateList(QVariant);
    void updatePeriod();
    void updateSchedule(bool, const int&);
    void updateScreen();
    void errorOnOff();

public slots:
    void runSterilization(int);
    void updatePage(const int&);
    void storeSetTime(const int&, int* const &);

protected:
    int Init();
    void schedulerInit();
    bool runStopThread(QThread *, bool);

    int loadFromDB(char* tgUuid=nullptr);
    //int storeToDB(int* const &); // Reserved
    int removeFromDB(unsigned int);

    void removeToList(unsigned int);
    void appendToList(const char *, int* const &);
    void showAllList();
};

#endif // MAINCONTROLLER_H
