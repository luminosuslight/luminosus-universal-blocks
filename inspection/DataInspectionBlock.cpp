#include "DataInspectionBlock.h"

#include "core/connections/Nodes.h"
#include "core/manager/BlockList.h"
#include "core/manager/Engine.h"


bool DataInspectionBlock::s_registered = BlockList::getInstance().addBlock(DataInspectionBlock::info());


DataInspectionBlock::DataInspectionBlock(CoreController* controller, QString uid)
    : OneInputBlock(controller, uid)
    , m_valueString(this, "valueString", "0%", /*persistent*/ false)
    , m_additionalValueString(this, "additionalValueString", "", /*persistent*/ false)
    , m_currentValue(this, "currentValue", 0, 0, 1, /*persistent*/ false)
    , m_valueHistory(50*3)  // 50 FPS * 3s
{
    m_valueHistory.fill(0.0, m_valueHistory.capacity());
    connect(m_controller->engine(), &Engine::updateBlocks, this, &DataInspectionBlock::eachFrame);
}

QVector<double> DataInspectionBlock::getValueHistory() const {
    return m_valueHistory.toVector();
}

void DataInspectionBlock::eachFrame() {
    double value = m_inputNode->getValue();
    m_currentValue = value;
    if (m_inputNode->constData().absoluteMaximumIsProvided()) {
        double absValue = m_inputNode->getAbsoluteValue();
        m_valueString = QString::number(60.0 / absValue, 'f', 1) + " BPM";
        m_additionalValueString = QString::number(absValue, 'f', 2) + " sec\n"
                + QString::number(1.0 / absValue, 'f', 2) + " Hz ";
    } else {
        m_valueString = QString::number(value * 100, 'f', 1) + "%";
        m_additionalValueString = "DMX Value " + QString::number(qRound(value * 255));
    }
    m_valueHistory.push_back(value);
    emit valueHistoryChanged();
}
