#ifndef PERFORMANCEMONITORBLOCK_H
#define PERFORMANCEMONITORBLOCK_H

#include "core/block_basics/OneOutputBlock.h"

#include <QTimer>


class PerformanceMonitorBlock: public OneOutputBlock {

    Q_OBJECT

public:

    static bool s_registered;
    static BlockInfo info() {
        static BlockInfo info;
        info.typeName = "Performance Monitor";
        info.category << "General" << "Inspection";
        info.orderHint = 0 + 900 + 3;
        info.visibilityRequirements << VisibilityRequirement::DeveloperMode;
        info.helpText = "Shows performance information about current CPU usage and "
                        "actually rendered Frames Per Second (FPS).\n\n"
                        "Note: CPU usage is only available on Linux.";
        info.qmlFile = "qrc:/universal-blocks/inspection/PerformanceMonitorBlock.qml";
        info.complete<PerformanceMonitorBlock>();
        return info;
    }

    explicit PerformanceMonitorBlock(CoreController* controller, QString uid);

public slots:
    virtual BlockInfo getBlockInfo() const override { return info(); }

    QString getQtCompileVersion() const { return QT_VERSION_STR; }
    QString getQtRuntimeVersion() const { return qVersion(); }

    void updateCpuUsage();

protected:
    QTimer m_refreshTimer;
    DoubleAttribute m_cpuUsage;
};

#endif // PERFORMANCEMONITORBLOCK_H
