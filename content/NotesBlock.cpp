#include "NotesBlock.h"

#include "core/manager/BlockList.h"


bool NotesBlock::s_registered = BlockList::getInstance().addBlock(NotesBlock::info());


NotesBlock::NotesBlock(CoreController* controller, QString uid)
    : BlockBase(controller, uid)
    , m_text(this, "text")
    , m_richText(this, "richText", true)
{
    m_widthIsResizable = true;
}
