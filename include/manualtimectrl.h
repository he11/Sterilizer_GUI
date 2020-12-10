#ifndef MENUALSETTINGCTRL_H
#define MENUALSETTINGCTRL_H

#include "common.h"
#include "ictrl.h"

class ManualTimeCtrl : public ICtrl
{
    Q_OBJECT
    Q_PROPERTY(int hoursVal READ getHours WRITE setHours NOTIFY updateTumbler)
    Q_PROPERTY(int minutesVal READ getMinutes WRITE setMinutes NOTIFY updateTumbler)
    Q_PROPERTY(int baseVal READ getBase WRITE setBase NOTIFY updateTumbler)
    Q_PROPERTY(int durationVal READ getDuration WRITE setDuration NOTIFY updateTumbler)
    Q_PROPERTY(bool errState READ getErrState NOTIFY errorOnOff)

private:
    bool errState = false;
    int hoursVal, minutesVal, baseVal, durationVal;

public:
    explicit ManualTimeCtrl();
    ~ManualTimeCtrl() override;

    void setTumbler(const int &, const int &, const int &, const int &);
    int getHours() const;
    void setHours(const int &);
    int getMinutes() const;
    void setMinutes(const int &);
    int getBase() const;
    void setBase(const int &);
    int getDuration() const;
    void setDuration(const int &);

    bool getErrState() const;

    Q_INVOKABLE void reqToStore();
    Q_INVOKABLE void displayError();

signals:
    void updateTumbler();
    void errorOnOff();

public slots:

protected:
    void Init();
};

#endif // MENUALSETTINGCTRL_H
