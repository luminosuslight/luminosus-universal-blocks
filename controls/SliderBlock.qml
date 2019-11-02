import QtQuick 2.5
import CustomElements 1.0
import "qrc:/core/ui/items"
import "qrc:/core/ui/controls"

BlockBase {
    id: root
    width: 45*dp
    height: 200*dp

    StretchColumn {
        anchors.fill: parent

        HeightResizeArea {
            target: root
            minSize: 120*dp
            maxSize: 600*dp
        }

        Slider {
            id: slider
            objectName: "slider"
            mappingID: block.getUid() + "slider"
            value: block.value
            onValueChanged: {
                if (value !== block.value) {
                    block.value = value;
                }
            }
        }

        DragArea {
            OutputNode {
                node: block.node("outputNode")
            }
        }
    }
}

