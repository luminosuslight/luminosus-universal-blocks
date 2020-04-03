#ifndef CLOCKBLOCK_H
#define CLOCKBLOCK_H

#include "core/block_basics/BlockBase.h"


class ClockBlock: public BlockBase {

    Q_OBJECT

public:

    static bool s_registered;
    static BlockInfo info() {
        static BlockInfo info;
        info.typeName = "Clock";
        info.category << "General" << "Time";
        info.orderHint = 0 + 300 + 1;
        info.helpText = "Displays the current 24h time.";
        info.qmlFile = "qrc:/universal-blocks/time/ClockBlock.qml";
        info.complete<ClockBlock>();
        return info;
    }

    explicit ClockBlock(CoreController* controller, QString uid);

public slots:
    virtual BlockInfo getBlockInfo() const override { return info(); }
};

#endif // CLOCKBLOCK_H
