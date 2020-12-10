#ifndef STEPTIMECTRL_H
#define STEPTIMECTRL_H

#include "common.h"
#include "ictrl.h"

class StepTimeCtrl : public ICtrl
{
    Q_OBJECT
    Q_PROPERTY(int savedHours READ getSavedHours NOTIFY updateSetVal)
    Q_PROPERTY(int savedMinutes READ getSavedMinutes NOTIFY updateSetVal)
    Q_PROPERTY(int hoursVal READ getHours WRITE setHours NOTIFY updateTumbler)
    Q_PROPERTY(int minutesIdx READ getMinutes WRITE setMinutes NOTIFY updateTumbler)
    Q_PROPERTY(int mInterval READ getMInterval NOTIFY updateTumbler)
    Q_PROPERTY(bool errState READ getErrState NOTIFY errorOnOff)

private:
    bool errState = false;
    int savedHours, savedMinutes;
    int hoursVal, minutesIdx, mInterval;

public:
    explicit StepTimeCtrl();
    ~StepTimeCtrl();

    void loadPeriod(int);

    int getSavedHours() const;
    int getSavedMinutes() const;

    void setTumbler(const int &, const int &, const int &);
    int getHours() const;
    void setHours(const int &);
    int getMinutes() const;
    void setMinutes(const int &);
    int getMInterval() const;

    bool getErrState() const;

    Q_INVOKABLE void reqToStore();

signals:
    void updateSetVal();
    void updateTumbler();
    void errorOnOff();

public slots:

protected:
    void Init();
};

#endif // STEPTIMECTRL_H
