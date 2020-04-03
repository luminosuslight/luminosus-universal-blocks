#include "SmokeTestBlock.h"

#include "core/manager/BlockList.h"
#include "core/manager/BlockManager.h"


bool SmokeTestBlock::s_registered = BlockList::getInstance().addBlock(SmokeTestBlock::info());


SmokeTestBlock::SmokeTestBlock(CoreController* controller, QString uid)
    : BlockBase(controller, uid)
{
}

void SmokeTestBlock::addAllBlockTypes() {
    QStringList blockTypes = m_controller->blockManager()->blockList()->getAllBlockTypes();
    for (int i = 0; i < blockTypes.count(); ++i) {
        // add each block with a random position offset of 1500px:
        m_controller->blockManager()->addNewBlock(blockTypes[i], 1500);
    }
}

void SmokeTestBlock::deleteAllBlocks() {
    m_controller->blockManager()->deleteAllBlocks();
}
