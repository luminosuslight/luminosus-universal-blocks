#ifndef NOTESBLOCK_H
#define NOTESBLOCK_H

#include "core/block_basics/BlockBase.h"


class NotesBlock : public BlockBase
{
    Q_OBJECT

public:

    static bool s_registered;
	static BlockInfo info() {
		static BlockInfo info;
		info.typeName = "Notes";
		info.nameInUi = "Notes";
        info.category << "General" << "Content";
        info.helpText = "Can be used to take notes or to create informative labels.\n\n"
                        "Markdown and basic HTML are supported.";
        info.qmlFile = "qrc:/universal-blocks/content/NotesBlock.qml";
        info.orderHint = 0 + 200 + 1;
		info.complete<NotesBlock>();
		return info;
	}

    explicit NotesBlock(CoreController* controller, QString uid);

signals:
	void textChanged();

public slots:
    virtual BlockInfo getBlockInfo() const override { return info(); }

protected:
    StringAttribute m_text;
    BoolAttribute m_richText;
};

#endif // NOTESBLOCK_H
