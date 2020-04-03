#ifndef DATAINSPECTIONBLOCK_H
#define DATAINSPECTIONBLOCK_H

#include "core/block_basics/OneInputBlock.h"
#include "core/helpers/utils.h"
#include "core/helpers/QCircularBuffer.h"

#include <QTimer>


class DataInspectionBlock : public OneInputBlock {

    Q_OBJECT
    Q_PROPERTY(QVector<double> valueHistory READ getValueHistory NOTIFY valueHistoryChanged)

public:

    static bool s_registered;
    static BlockInfo info() {
        static BlockInfo info;
        info.typeName = "Data Inspection";
        info.category << "General" << "Inspection";
        info.orderHint = 0 + 900 + 1;
        info.helpText = "Shows the incoming value in percent or as an absolute value.\n"
                        "Connect it in addition to other Blocks to an output to "
                        "preview its value.";
        info.qmlFile = "qrc:/universal-blocks/inspection/DataInspectionBlock.qml";
        info.complete<DataInspectionBlock>();
        return info;
    }

    explicit DataInspectionBlock(CoreController* controller, QString uid);

signals:
    void valueHistoryChanged();

public slots:
    virtual BlockInfo getBlockInfo() const override { return info(); }

    QString getValueString() const { return m_valueString; }

    QVector<double> getValueHistory() const;

private slots:
    void eachFrame();

protected:
    StringAttribute m_valueString;
    StringAttribute m_additionalValueString;
    DoubleAttribute m_currentValue;

    Qt3DCore::QCircularBuffer<double> m_valueHistory;

};

#endif // DATAINSPECTIONBLOCK_H
