#include "mainmenuctrl.h"
#include <wiringPi.h>

#define LIQUID_EXIT_1 27// BCM_GPIO_16, PIN_36
#define LIQUID_EXIT_2 28// BCM_GPIO_20, PIN_38

MainMenuCtrl::MainMenuCtrl(QQmlApplicationEngine &root) {
    root.rootContext()->setContextProperty("mainMenuCtrl", this);

    // Register Child Controller
    pManualCtrl = new ManualTimeCtrl();
    root.rootContext()->setContextProperty("manualCtrl", pManualCtrl);

    pStepCtrl = new StepTimeCtrl();
    root.rootContext()->setContextProperty("stepCtrl", pStepCtrl);

    Init();
}

MainMenuCtrl::~MainMenuCtrl() {}

void MainMenuCtrl::Init() {
    // Setup GPIO
    setupGPIO();

    // Setup Timer to Update The Current Date
    setupTimer();
}

int MainMenuCtrl::setupGPIO() {
    if (wiringPiSetup() == -1) {
        cout << "GPIO Init Fail" << endl;
        return -1;
    }

    pinMode(LIQUID_EXIT_1, OUTPUT);
    pinMode(LIQUID_EXIT_2, OUTPUT);

    // GPIO Off
    digitalWrite(LIQUID_EXIT_1, 1);
    digitalWrite(LIQUID_EXIT_2, 1);

    return 0;
}

void MainMenuCtrl::setupTimer() {
    QTimer* dateTimer = new QTimer(this);
    connect(dateTimer, SIGNAL(timeout()), this, SLOT(getDate()));
    dateTimer->start(1000);
}

void MainMenuCtrl::runSterilization(int sec) {
    static bool runState = false;
#ifdef DEBUG_MODE
    cout << "cpp: State[" << runState << "]: ";
#endif
    if (!runState) {
#ifdef DEBUG_MODE
        cout << "cpp: Start sterilization" << endl;
#endif
        runState = true;
        digitalWrite(LIQUID_EXIT_1, 0);
        digitalWrite(LIQUID_EXIT_2, 0);

        QTimer::singleShot(sec * 1000, this, []() {
            digitalWrite(LIQUID_EXIT_1, 1);
            digitalWrite(LIQUID_EXIT_2, 1);
            runState = false;});
    } else {
#ifdef DEBUG_MODE
        cout << "cpp: Running sterilization..." << endl;
        //TODO: Add Popup Message
#endif
    }
}

void MainMenuCtrl::stopSterilization() {
    // GPIO Off
    digitalWrite(LIQUID_EXIT_1, 1);
    digitalWrite(LIQUID_EXIT_2, 1);
}

QString MainMenuCtrl::convToKorDay(QString day) {
    if (day == "Monday") { return "월요일"; }
    else if (day == "Tuesday") { return "화요일"; }
    else if (day == "Wednesday") { return "수요일"; }
    else if (day == "Thursday") { return "목요일"; }
    else if (day == "Friday") { return "금요일"; }
    else if (day == "Saturday") { return "토요일"; }
    else { return "일요일"; }
}

QString MainMenuCtrl::convToKorAP(QString ap) {
    if (ap == "AM" || ap == "am") { return "오전"; }
    else { return "오후"; }
}

void MainMenuCtrl::getDate() {
    QDateTime currentDate = QDateTime::currentDateTime();
#ifdef DEBUG_MODE
    //cout << "cpp: Current Date: " << fromQString(currentDate.toString("yyyy-MM-dd dddd Thh:mm:ss AP")) << endl;
#endif
    if (!getConnectPage()) { return; }
    QString dateStr = currentDate.toString("yyyy년 MM월 dd일") + " " + convToKorDay(currentDate.toString("dddd")) + " "\
                    + convToKorAP(currentDate.toString("AP")) + " " + currentDate.toString("hh시 mm분 ss초");
    QMetaObject::invokeMethod(getConnectPage(), "qml_updateDate", Q_ARG(QVariant, dateStr));//"yyyy년 MM월 dd일 dddd요일 hh시 mm분 ss초 AP"))); //"yyyy-MM-dd dddd hh:mm:ss AP")));
}

ICtrl* MainMenuCtrl::getPageCtrl(const int& pageType) {
    switch (pageType) {
    case MAIN: return this;
    case MENUAL_TIME_SETTING: return pManualCtrl;
    case STEP_TIME_SETTING: return pStepCtrl;
    }

    return nullptr;
}

QObject* MainMenuCtrl::getCurrPage() {
    return pCurrentQml;
}

bool MainMenuCtrl::connectPage(const int& pageType, QObject* pStackQml) {
    bool res = false;

    QObject* pCurrentPage = pStackQml->children().constLast();
    pCurrentQml = pCurrentPage;
#ifdef DEBUG_MODE
    cout << "cpp: [" << pCurrentPage << "] Current Page: " << fromQString(pCurrentPage->objectName()) << endl;
    /*cout << "cpp: [" << this->metaObject()->className() << "]:Page[" << pageType << "]: " << fromQString(pCurrentQml->objectName()) << endl; */
#endif

    ICtrl* controller = getPageCtrl(pageType);
    if (controller) {
        controller->setConnectPage(*pCurrentPage);
        res = controller->getConnectPage();
        if (pageType == MAIN) { getDate(); }
        else { connect(controller->getConnectPage(), SIGNAL(qml_returnBack(QVariant)), this, SLOT(movePage(QVariant))); }
    } else {
#ifdef DEBUG_MODE
        /*cout << "cpp: Return Back Page: " << endl;
        QObject* pParent = pCurrentQml->parent();
        cout << "\tParent[" << pParent << "]: " << fromQString(pParent->objectName())<< endl;
        QList<QObject*>::const_iterator iter = pParent->children().begin();
        int idx = 0;
        while (iter != pParent->children().end()) {
            cout << "\t[" << idx << "]: " << fromQString(iter.operator*()->objectName()) << endl;
            ++iter;
            ++idx;
        }*/
#endif
        int currentPage = pStackQml->children().size() - 2;
        pCurrentQml = pStackQml->children().at(currentPage);

        // Return privious page
        res = disconnect(pCurrentPage, SIGNAL(qml_returnBack(QVariant)), this, SLOT(movePage(QVariant)));
    }

    return res;
}

void MainMenuCtrl::movePage(QVariant pageType, QObject* pStack) {
    static QObject* pStackQml = nullptr;

    int pageVal = pageType.toInt();
    pStackQml = (pStack)? pStack : pStackQml;
    bool res = connectPage(pageVal, pStackQml);

    emit reqUpdatePage(pageVal);

#ifdef DEBUG_MODE
    cout << "cpp: Page Connect & Disconnect Result: " << res << endl;
#endif
}
