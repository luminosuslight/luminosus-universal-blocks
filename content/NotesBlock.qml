import QtQuick 2.12
import CustomElements 1.0
import "qrc:/core/ui/items"
import "qrc:/core/ui/controls"
import "qrc:/core/ui/snarkdown.js" as Snarkdown

BlockBase {
    id: root
    width: 100*dp
    height: Math.max((showStyled ? styledText.contentHeight : textInput.contentHeight) + 38*dp, 60*dp)
    onWidthChanged: block.positionChanged()
    settingsComponent: settings

    property bool showStyled: !textInput.activeFocus && block.attr("richText").val

    StretchColumn {
        anchors.fill: parent

        Item {
            implicitHeight: -1
            TextEdit {
                id: textInput
                opacity: showStyled ? 0 : 1
                anchors.fill: parent
                anchors.margins: 4*dp

                color: "#fff"
                font.family: "Quicksand"
                font.pixelSize: 18*dp
                wrapMode: TextEdit.Wrap
                selectByMouse: true

                text: block.attr("text").val
                onTextChanged: {
                    if (text !== block.attr("text").val) {
                        block.attr("text").val = text
                    }
                }
                Keys.onEscapePressed: focus = false
            }
            Text {
                id: styledText
                visible: showStyled
                anchors.fill: parent
                anchors.margins: 4*dp
                color: "#fff"
                font.family: "Quicksand"
                font.pixelSize: 18*dp
                wrapMode: Text.Wrap
                text: Snarkdown.parse(block.attr("text").val)
                textFormat: Text.RichText
                onLinkActivated: {
                    Qt.openUrlExternally(link)
                    textInput.focus = false
                }
            }
        }

        DragArea {
            text: "Notes"

            WidthResizeArea {
                target: root
                minSize: 100*dp
                maxSize: 2000*dp
            }
        }
    }  // end main Column

    Component {
        id: settings
        StretchColumn {
            leftMargin: 15*dp
            rightMargin: 15*dp
            defaultSize: 30*dp

            BlockRow {
                Text {
                    text: "Markdown:"
                    width: parent.width - 30*dp
                }
                AttributeCheckbox {
                    width: 30*dp
                    attr: block.attr("richText")
                }
            }
        }
    }  // end Settings Component
}

