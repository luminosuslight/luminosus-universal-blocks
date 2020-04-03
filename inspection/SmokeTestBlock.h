#ifndef SMOKETESTBLOCK_H
#define SMOKETESTBLOCK_H

#include "core/block_basics/BlockBase.h"


class SmokeTestBlock : public BlockBase {

    Q_OBJECT

public:

    static bool s_registered;
    static BlockInfo info() {
        static BlockInfo info;
        info.typeName = "Smoke Test";
        info.category << "General" << "Inspection";
        info.orderHint = 0 + 900 + 5;
        info.visibilityRequirements << VisibilityRequirement::DeveloperMode;
        info.helpText = "Exists to quickly test if all Blocks work and the program doesn't crash.\n"
                        "Can also be used to do stress tests with many Blocks.";
        info.qmlFile = "qrc:/universal-blocks/inspection/SmokeTestBlock.qml";
        info.complete<SmokeTestBlock>();
        return info;
    }

    explicit SmokeTestBlock(CoreController* controller, QString uid);

public slots:
    virtual BlockInfo getBlockInfo() const override { return info(); }

    void addAllBlockTypes();
    void deleteAllBlocks();
};

#endif // SMOKETESTBLOCK_H
