#ifndef IMAGEBLOCK_H
#define IMAGEBLOCK_H

#include "core/block_basics/BlockBase.h"


class ImageBlock : public BlockBase {

    Q_OBJECT

public:

    static bool s_registered;
    static BlockInfo info() {
        static BlockInfo info;
        info.typeName = "Image";
        info.nameInUi = "Image";
        info.category << "General" << "Content";
        info.availabilityRequirements << AvailabilityRequirement::LocalFileSelection;
        info.helpText = "Displays an image file.";
        info.qmlFile = "qrc:/universal-blocks/content/ImageBlock.qml";
        info.orderHint = 0 + 200 + 2;
        info.complete<ImageBlock>();
        return info;
    }

    explicit ImageBlock(CoreController* controller, QString uid);

public slots:
    virtual BlockInfo getBlockInfo() const override { return info(); }

protected:
    StringAttribute m_filePath;
    DoubleAttribute m_rotation;
    BoolAttribute m_shadow;
};

#endif // IMAGEBLOCK_H
