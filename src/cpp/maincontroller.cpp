#include "maincontroller.h"

enum {
    T_HOURS,
    T_MINUTES,
    T_BASE,
    T_DURATION,
    TOTAL_IDX_CNT
};

static bool timeCompare(const set_data_t &, const set_data_t &);

MainController::MainController(int &argc, char** argv)
    :QGuiApplication (argc, argv) {
    int result = Init();
    if (result != 0) { this->~MainController(); }
}

MainController::~MainController() {}

int MainController::Init() {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //TODO: Timer counting thread init & DB init etc...
    loadFromDB();
#ifdef DEBUG_MODE
    showAllList();
#endif
    // Create schedule thread & Run
    schedulerInit();

    root.rootContext()->setContextProperty("mainCtrl", this);
    pMainMenuCtrl = new MainMenuCtrl(root);
    connect(pMainMenuCtrl, SIGNAL(reqUpdatePage(const int&)), this, SLOT(updatePage(const int&)));

    root.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (root.rootObjects().isEmpty())
        return -1;

    pRootQml = root.rootObjects()[0];
    setConnectPage(*pRootQml);

    bool res = runStopThread(pScheduleThread, true);
#ifdef DEBUG_MODE
    cout << "Schedule Thread Init State: " << res<< endl;
#endif

    reinterpret_cast<StepTimeCtrl *>(pMainMenuCtrl->getPageCtrl(STEP_TIME_SETTING))->loadPeriod(period);
    pMainMenuCtrl->movePage(MAIN, pStackQml);

    return 0;
}

void MainController::exitApp() {
    this->~MainController();
}

void MainController::stopSterilization() {
    pMainMenuCtrl->stopSterilization();
}

const QObject* MainController::getConnectPage() {
    return pConnectQml;
}

void MainController::setConnectPage(QObject &connectQml) {
    pConnectQml = &connectQml;

    pScheduleListQml = getDirObjectIns(pConnectQml, "scheduleList");
    pStackQml = getDirObjectIns(pConnectQml, "pageStack");

    // Connect Cpp to Qml
    connect(this, SIGNAL(updateList(QVariant)), pConnectQml, SLOT(qml_updateList(QVariant)));
    //connect(this, SIGNAL(), pConnectQml, SLOT());
    //connect(pConnectQml, SIGNAL(), this, SLOT());
}

void MainController::schedulerInit() {
    pScheduleThread = new ScheduleThread(scheduleList, period);
    connect(this, SIGNAL(updatePeriod()), pScheduleThread, SLOT(updatePeriod()));
    connect(this, SIGNAL(updateSchedule(bool, const int&)), pScheduleThread, SLOT(updateSchedule(bool, const int&)));
    connect(pScheduleThread, SIGNAL(runSterilization(int)), this, SLOT(runSterilization(int)));
    connect(pScheduleThread, &QThread::finished, pScheduleThread, &QObject::deleteLater);
}

bool MainController::runStopThread(QThread *target, bool runSwitch) {
    static bool running = false;

    if (runSwitch && !running) { target->start(); }
    else if (!runSwitch && running) { target->requestInterruption(); }
    return (running = (runSwitch)? true : false);
}

void MainController::runSterilization(int sec) {
    pMainMenuCtrl->runSterilization(sec);
}

bool MainController::getDisplayList() {
    return displayList;
}

bool MainController::getDisplayExit() {
    return displayExit;
}

void MainController::updatePage(const int& pageType) {
    static ICtrl* pConnectedCtrl = nullptr;
    QObject* pCurrentQml = pMainMenuCtrl->getCurrPage();

    if (pageType == MENUAL_TIME_SETTING || pageType == STEP_TIME_SETTING) {
        ICtrl* controller = pMainMenuCtrl->getPageCtrl(pageType);
        connect(controller, SIGNAL(storeSetTime(const int&, int* const &)), \
                this, SLOT(storeSetTime(const int&, int* const &)));
        pConnectedCtrl = controller;
        displayExit = false;
    } else if (pConnectedCtrl) {
        disconnect(pConnectedCtrl, SIGNAL(storeSetTime(const int&, int* const &)), \
                   this, SLOT(storeSetTime(const int&, int* const &)));
        pConnectedCtrl = nullptr;
        displayExit = true;
    }
    displayList = (pageType != STEP_TIME_SETTING)? true : false;
    //QMetaObject::invokeMethod(pConnectQml, "qml_displayList", Q_ARG(QVariant, displayList));
    emit updateScreen();

#ifdef DEBUG_MODE
    cout << "cpp: [" << this->metaObject()->className() << "]:Page[" << pageType << "]: " << fromQString(pCurrentQml->objectName()) << endl;
#endif
}

static bool timeCompare(const set_data_t &obj1, const set_data_t &obj2) {
    if (obj1.timeVal < obj2.timeVal) { return true; }
    else if (obj1.timeVal == obj2.timeVal) { if (obj1.duration > obj2.duration) { return true; }}
    return false;
}

int MainController::loadFromDB(char* tgUuid) {
    if (!tgUuid) { // Load all data from DB
        //sort(scheduleList.begin(), scheduleList.end(), timeCompare);

#if 1 // test data
        set_data_t a;
        genUuid(a.uuid);
        a.timeVal = 86340;
        a.duration = 19;
        int res = sprintf(a.timeStr, "%s %02d:%02d (%02d초)", "오후", 11, 59, 19);
        scheduleList.push_back(a);
        period = 3900;
#endif

        //TODO: qml list & thread list load


    } else { // Load target data from DB

    }

    return 0;
}

/* Reserved
int MainController::storeToDB(int* const &setTime) {
    // Create uuid version 4
    char uuid[37];
    genUuid(uuid);

    //TODO: Store target to DB

    appendToList(uuid, setTime);

    return 0;
}*/

int MainController::removeFromDB(unsigned int index) {
    char* rmTarget = getUuid(index);

#ifdef DEBUG_MODE
    cout << "cpp: Remove[" << index << "]: " << rmTarget << endl;
#endif
    //TODO: Remove target from DB

    return 0;
}

void MainController::showAllList() {
    int idx = 0;

    vector<set_data_t>::iterator iter = scheduleList.begin();
    while (iter != scheduleList.end()) {
        cout << "cpp: [" << idx << "]: UUID[" << iter->uuid \
             << "] TIME[" << iter->timeStr << "] TIMEVALUE[" \
             << iter->timeVal << "] DURATION[" << iter->duration << "]" << endl;
        ++iter;
        ++idx;
    }
}

void MainController::appendToList(const char* uuid, int* const &setTime) {
    set_data_t appd_data;

    int hours_24 = (setTime[T_HOURS] != 12)? setTime[T_HOURS] + (12 & (~setTime[T_BASE] + 1)) : 12 & (~setTime[T_BASE] + 1);
    appd_data.timeVal = hours_24 * 3600 + setTime[T_MINUTES] * 60;
    sprintf(appd_data.timeStr, "%s %02d:%02d (%02d초)", (setTime[T_BASE])? "오후" : "오전", \
                                                        setTime[T_HOURS], \
                                                        setTime[T_MINUTES], \
                                                        setTime[T_DURATION]);
    appd_data.duration = setTime[T_DURATION];
    memcpy(appd_data.uuid, uuid, 37);

    int idx = 0;
    vector<set_data_t>::iterator pos = scheduleList.begin();
    while (pos != scheduleList.end()) {
        if (appd_data.timeVal < pos->timeVal) { break; }
        else if (appd_data.timeVal == pos->timeVal) { if (appd_data.duration > pos->duration) { break; }}
        ++pos;
        ++idx;
    }
    scheduleList.insert(pos, appd_data);
#ifdef DEBUG_MODE
    cout << "cpp: Reserved Schedule: " << appd_data.timeStr << endl;
    showAllList();
#endif

    // ----> thread data append

    emit updateSchedule(true, idx);
    emit updateList(idx);
}

void MainController::removeToList(unsigned int index) {
    //TODO: lock processing
    scheduleList.erase(scheduleList.begin() + static_cast<int>(index));
#ifdef DEBUG_MODE
    showAllList();
#endif
    emit updateSchedule(false, static_cast<int>(index));
}

void MainController::storeSetTime(const int& pageType, int* const &setTime) {
    static bool displayErr = false;
    char uuid[37];

    if (pageType == MENUAL_TIME_SETTING) {
        if (getListSize() < 5) {
            // Create uuid version 4
            genUuid(uuid);

            //TODO: Store target to DB
            //int res = ;
            //cout << "cpp: To store the data in the DB is failure (err: " << res << ")" << endl;

            appendToList(uuid, setTime);
        } else if (!displayErr) {
            errState = true;
            emit errorOnOff();
            QTimer::singleShot(1000, this, [&]() { errState = false; emit errorOnOff(); displayErr = false; });
            displayErr = true;
            //QMetaObject::invokeMethod(pConnectQml, "qml_displayError");
            //QTimer::singleShot(1000, this, [&]() { displayErr = false; QMetaObject::invokeMethod(pConnectQml, "qml_errMsgTimeOut"); });
        }
    } else if (pageType == STEP_TIME_SETTING) {
        // Create uuid version 4
        genUuid(uuid);

        //TODO: Store target to DB
        //int res = ;
        //cout << "cpp: To store the data in the DB is failure (err: " << res << ")" << endl;

        period = *setTime;
        emit updatePeriod();
    }
}

void MainController::rmSetTime(unsigned int index) {
    // Remove the data from DB
    removeFromDB(index);

    // Remove the data from scheduleList
    removeToList(index);
}

char* MainController::getUuid(unsigned int index) {
    return scheduleList.at(index).uuid;
}

int MainController::getSetTimeVal(unsigned int index) {
    return scheduleList.at(index).timeVal;
}

unsigned int MainController:: getListSize() {
    return scheduleList.size();
}

QString MainController::getSetTimeStr(unsigned int index) {
    return toQString(scheduleList.at(index).timeStr);
}

bool MainController::getErrState() const {
    return errState;
}
