#include "StopWatchBlock.h"

#include "core/connections/Nodes.h"
#include "core/manager/BlockList.h"
#include "core/helpers/constants.h"


bool StopWatchBlock::s_registered = BlockList::getInstance().addBlock(StopWatchBlock::info());


StopWatchBlock::StopWatchBlock(CoreController *controller, QString uid)
    : BlockBase(controller, uid)
    , m_startInput(nullptr)
    , m_stopInput(nullptr)
    , m_resetInput(nullptr)
    , m_lastStartValue(0.0)
    , m_lastStopValue(0.0)
    , m_lastResetValue(0.0)
    , m_lastSessionTime(this, "lastSessionTime", 0.0, 0.0, std::numeric_limits<double>::max())
    , m_beginCurrentSession(HighResTime::now())
    , m_running(this, "running", false)
{
    // prepare nodes:
    m_startInput = createInputNode("startInput");
    m_stopInput = createInputNode("stopInput");
    m_resetInput = createInputNode("resetInput");

    //connect signals and slots:
    connect(m_startInput, SIGNAL(dataChanged()), this, SLOT(onStartInputChanged()));
    connect(m_stopInput, SIGNAL(dataChanged()), this, SLOT(onStopInputChanged()));
    connect(m_resetInput, SIGNAL(dataChanged()), this, SLOT(onResetInputChanged()));
}

void StopWatchBlock::onStartInputChanged() {
    double value = m_startInput->getValue();
    if (value >= LuminosusConstants::triggerThreshold
            && m_lastStartValue < LuminosusConstants::triggerThreshold) {
        start();
    }
    m_lastStartValue = value;
}

void StopWatchBlock::onStopInputChanged() {
    double value = m_stopInput->getValue();
    if (value >= LuminosusConstants::triggerThreshold
            && m_lastStopValue < LuminosusConstants::triggerThreshold) {
        stop();
    }
    m_lastStopValue = value;
}

void StopWatchBlock::onResetInputChanged() {
    double value = m_resetInput->getValue();
    if (value >= LuminosusConstants::triggerThreshold
            && m_lastResetValue < LuminosusConstants::triggerThreshold) {
        reset();
    }
    m_lastResetValue = value;
}

void StopWatchBlock::start() {
    if (m_running) return;
    m_running = true;
    m_beginCurrentSession = HighResTime::now();
    emit timeStringChanged();
}

void StopWatchBlock::stop() {
    if (!m_running) return;
    m_running = false;
    m_lastSessionTime = m_lastSessionTime + HighResTime::elapsedSecSince(m_beginCurrentSession);
    emit timeStringChanged();
}

void StopWatchBlock::reset() {
    if (m_running) stop();
    m_lastSessionTime = 0.0;
    emit timeStringChanged();
}

QString StopWatchBlock::getTimeString() const {
    double elapsedSec = m_lastSessionTime;
    if (m_running) {
        elapsedSec += HighResTime::elapsedSecSince(m_beginCurrentSession);
    }
    int dsec = fmod(elapsedSec, 1) * 10;
    int secs = fmod(elapsedSec, 60);
    int mins = fmod((elapsedSec / 60), 60);
    int hours = fmod((elapsedSec / 3600), 60);
    QString timeString = QString("%1:%2:%3.%4").arg(hours, 2, 10, QChar('0')).arg(mins, 2, 10, QChar('0')).arg(secs, 2, 10, QChar('0')).arg(dsec);
    return timeString;
}
