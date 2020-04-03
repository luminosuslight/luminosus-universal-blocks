#include "ApplicationLogBlock.h"

#include "core/manager/BlockList.h"


bool ApplicationLogBlock::s_registered = BlockList::getInstance().addBlock(ApplicationLogBlock::info());


ApplicationLogBlock::ApplicationLogBlock(CoreController* controller, QString uid)
    : BlockBase(controller, uid)
{
    m_widthIsResizable = true;
    m_heightIsResizable = true;
}
