#include "GuiEditorBlock.h"

#include "core/manager/BlockList.h"
#include "core/manager/BlockManager.h"


bool GuiEditorBlock::s_registered = BlockList::getInstance().addBlock(GuiEditorBlock::info());


GuiEditorBlock::GuiEditorBlock(CoreController* controller, QString uid)
    : BlockBase(controller, uid)
    , m_code(this, "code", "", /*persistent*/ false)
    , m_saved(this, "saved", true, /*persistent*/ false)
{
    m_widthIsResizable = true;
    m_heightIsResizable = true;
    connect(m_controller->blockManager(), &BlockManager::focusChanged, this, &GuiEditorBlock::onFocusChanged);
    connect(&m_code, &StringAttribute::valueChanged, this, &GuiEditorBlock::onCodeChanged);
}

void GuiEditorBlock::apply() {
    BlockInterface* focusedBlock = m_controller->blockManager()->getFocusedBlock();
    if (!focusedBlock) {
        return;
    }
    focusedBlock->setGuiItemCode(m_code);
    m_saved = true;
}

void GuiEditorBlock::onFocusChanged() {
    BlockInterface* focusedBlock = m_controller->blockManager()->getFocusedBlock();
    if (!focusedBlock) {
        m_code = "No focused block";
        return;
    }

    QString qmlPath = focusedBlock->getBlockInfo().qmlFile;
    qmlPath.remove("qrc");

    QFile file(qmlPath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open file " + qmlPath + ".";
        return;
    }
    QByteArray content = file.readAll();
    file.close();

    m_code = QString::fromUtf8(content);
    m_saved = true;
}

void GuiEditorBlock::onCodeChanged() {
    m_saved = false;
}
