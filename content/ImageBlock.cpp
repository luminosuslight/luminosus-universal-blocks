#include "ImageBlock.h"

#include "core/manager/BlockList.h"


bool ImageBlock::s_registered = BlockList::getInstance().addBlock(ImageBlock::info());


ImageBlock::ImageBlock(CoreController* controller, QString uid)
    : BlockBase(controller, uid)
    , m_filePath(this, "filePath", "")
    , m_rotation(this, "rotation", 0.0, 0.0, 360.0)
    , m_shadow(this, "shadow", false)
{
    m_widthIsResizable = true;
}
