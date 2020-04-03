#include "ClockBlock.h"

#include "core/manager/BlockList.h"


bool ClockBlock::s_registered = BlockList::getInstance().addBlock(ClockBlock::info());


ClockBlock::ClockBlock(CoreController* controller, QString uid)
    : BlockBase(controller, uid)
{

}
