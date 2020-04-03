#ifndef STOPWATCHBLOCK_H
#define STOPWATCHBLOCK_H

#include "core/block_basics/BlockBase.h"
#include "core/helpers/utils.h"


class StopWatchBlock : public BlockBase {

    Q_OBJECT

public:

    static bool s_registered;
    static BlockInfo info() {
        static BlockInfo info;
        info.typeName = "Stopwatch";
        info.category << "General" << "Time";
        info.orderHint = 0 + 300 + 2;
        info.helpText = "A simple stopwatch.\n\n"
                        "Can be triggered by other blocks to stop the time between to "
                        "events accurately.";
        info.qmlFile = "qrc:/universal-blocks/time/StopWatchBlock.qml";
        info.complete<StopWatchBlock>();
        return info;
    }

    StopWatchBlock(CoreController* controller, QString uid);

signals:
    void timeStringChanged();

public slots:
    virtual BlockInfo getBlockInfo() const override { return info(); }

    void onStartInputChanged();
    void onStopInputChanged();
    void onResetInputChanged();

    void start();
    void stop();
    void reset();

    QString getTimeString() const;

protected:
    QPointer<NodeBase> m_startInput;
    QPointer<NodeBase> m_stopInput;
    QPointer<NodeBase> m_resetInput;

    double m_lastStartValue;
    double m_lastStopValue;
    double m_lastResetValue;

    DoubleAttribute m_lastSessionTime;
    HighResTime::time_point_t m_beginCurrentSession;

    BoolAttribute m_running;
};

#endif // STOPWATCHBLOCK_H
