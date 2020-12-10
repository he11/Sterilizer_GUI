#ifndef MAINPAGECTRL_H
#define MAINPAGECTRL_H

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDateTime>

#include "manualtimectrl.h"
#include "steptimectrl.h"

class MainMenuCtrl : public ICtrl
{
    Q_OBJECT

private:
    QObject* pCurrentQml = nullptr;

    ManualTimeCtrl* pManualCtrl = nullptr;
    StepTimeCtrl* pStepCtrl = nullptr;

public:
    explicit MainMenuCtrl(QQmlApplicationEngine &);
    ~MainMenuCtrl();

    int setupGPIO();
    void setupTimer();

    ICtrl* getPageCtrl(const int&);
    QObject* getCurrPage();

    void stopSterilization();

signals:
    void reqUpdatePage(const int&);

public slots:
    void getDate();
    Q_INVOKABLE void runSterilization(int);
    Q_INVOKABLE void movePage(QVariant, QObject* pStack=nullptr);

protected:
    void Init();
    bool connectPage(const int&, QObject *);
    QString convToKorDay(QString);
    QString convToKorAP(QString);
};

#endif // MAINPAGECTRL_H
