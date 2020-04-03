#ifndef TIMERBLOCK_H
#define TIMERBLOCK_H

#include "core/block_basics/InOutBlock.h"

#include <QTimer>

// TODO: setting time is only possible by sending an absolute input value
// TODO: implement setting the time in the UI

class TimerBlock : public InOutBlock {

    Q_OBJECT

public:

    static bool s_registered;
    static BlockInfo info() {
        static BlockInfo info;
        info.typeName = "Timer";
        info.category << "General" << "Time";
        info.orderHint = 0 + 300 + 3;
        info.helpText = "A timer that can start an action after a specified "
                        "amount of time.";
        info.qmlFile = "qrc:/universal-blocks/time/TimerBlock.qml";
        info.complete<TimerBlock>();
        return info;
    }

    explicit TimerBlock(CoreController* controller, QString uid);

public slots:
    virtual BlockInfo getBlockInfo() const override { return info(); }

    QString getRemainingTimeString() const;

private slots:
    void start();
    void onTimerEnd();
    void onImpulseEnd();

protected:
    QTimer m_timer;
    BoolAttribute m_running;
};

#endif // TIMERBLOCK_H
