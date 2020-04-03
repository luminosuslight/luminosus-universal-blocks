#ifndef APPLICATIONLOGBLOCK_H
#define APPLICATIONLOGBLOCK_H

#include "core/block_basics/BlockBase.h"


class ApplicationLogBlock : public BlockBase {

    Q_OBJECT

public:

    static bool s_registered;
    static BlockInfo info() {
        static BlockInfo info;
        info.typeName = "Application Log";
        info.category << "General" << "Inspection";
        info.orderHint = 0 + 900 + 2;
        info.visibilityRequirements << VisibilityRequirement::DeveloperMode;
        info.helpText = "Shows the application log.";
        info.qmlFile = "qrc:/universal-blocks/inspection/ApplicationLogBlock.qml";
        info.complete<ApplicationLogBlock>();
        return info;
    }

    explicit ApplicationLogBlock(CoreController* controller, QString uid);

public slots:
    virtual BlockInfo getBlockInfo() const override { return info(); }
};

#endif // APPLICATIONLOGBLOCK_H
