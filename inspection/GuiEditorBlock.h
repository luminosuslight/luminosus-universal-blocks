#ifndef GUIEDITORBLOCK_H
#define GUIEDITORBLOCK_H

#include "core/block_basics/BlockBase.h"
#include "core/helpers/SmartAttribute.h"


class GuiEditorBlock: public BlockBase {

    Q_OBJECT

public:

    static bool s_registered;
    static BlockInfo info() {
        static BlockInfo info;
        info.typeName = "GUI Editor";
        info.category << "General" << "Inspection";
        info.visibilityRequirements << VisibilityRequirement::DeveloperMode;
        info.helpText = "Provides live editing of the QML part of the currently selected block.";
        info.qmlFile = "qrc:/universal-blocks/inspection/GuiEditorBlock.qml";
        info.orderHint = 0 + 900 + 4;
        info.complete<GuiEditorBlock>();
        return info;
    }

    explicit GuiEditorBlock(CoreController* controller, QString uid);

public slots:
    virtual BlockInfo getBlockInfo() const override { return info(); }

    void apply();

private slots:
    void onFocusChanged();
    void onCodeChanged();

protected:
    StringAttribute m_code;
    BoolAttribute m_saved;
};

#endif // GUIEDITORBLOCK_H
