import QtQuick 2.12
import QtQuick.Controls 2.12
import CustomElements 1.0
import "qrc:/core/ui/items"
import "qrc:/core/ui/controls"

BlockBase {
    id: root
    width: 700*dp
    height: 700*dp
    onWidthChanged: block.positionChanged()

    StretchColumn {
        anchors.fill: parent

        ScrollView {
            implicitHeight: -1
            TextEdit {
                id: codeInput
                objectName: "codeInput"
                height: contentHeight
                width: contentWidth
                text: block.attr("code").val
                onTextChanged: {
                    if (text !== block.attr("code").val) {
                        block.attr("code").val = text
                    }
                }
                color: block.attr("saved").val ? "#fff" : "#faa"
                font.family: "Quicksand"
                font.pixelSize: 18*dp
                selectByMouse: true
            }
        }

        ButtonSideLine {
            height: 30*dp
            text: "Apply"
            onClick: block.apply()
        }

        DragArea {
            text: "GUI Editor"

            WidthResizeArea {
                target: root
                minSize: 450*dp
                maxSize: 1100*dp
            }
        }
    }  // end main Column

    HeightResizeArea {
        width: 30*dp
        height: 30*dp
        target: root
        minSize: 300*dp
        maxSize: 1000*dp
        anchors.right: parent.right
        anchors.top: parent.top
    }
}
