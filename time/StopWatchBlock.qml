import QtQuick 2.12
import CustomElements 1.0
import "qrc:/core/ui/items"
import "qrc:/core/ui/controls"

BlockBase {
    id: root
    width: 120*dp
    height: 150*dp

    onWidthChanged: block.positionChanged()

    StretchColumn {
        anchors.fill: parent

        StretchText {
            id: timeText
            text: block.getTimeString()
            hAlign: Text.AlignHCenter
            font.family: "Courier"

            Connections {
                target: block
                onTimeStringChanged: timeText.text = block.getTimeString()
            }

            Timer {
                running: block.attr("running").val
                repeat: true
                interval: 100
                onTriggered: timeText.text = block.getTimeString()
            }
        }
        BlockRow {
            InputNode {
                node: block.node("startInput")
            }
            ButtonBottomLine {
                text: "Start"
                onPress: block.start()
                mappingID: block.getUid() + "start"
            }
        }
        BlockRow {
            InputNode {
                node: block.node("stopInput")
            }
            ButtonBottomLine {
                text: "Pause"
                onPress: block.stop()
                mappingID: block.getUid() + "stop"
            }
        }
        BlockRow {
            InputNode {
                node: block.node("resetInput")
            }
            ButtonBottomLine {
                text: "Reset"
                onPress: block.reset()
                mappingID: block.getUid() + "reset"
            }
        }


        DragArea {
            text: "Stopwatch"
        }
    }
}

