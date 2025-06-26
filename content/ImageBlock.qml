pragma ComponentBehavior: Bound
import QtQuick 2.5
import QtQuick.Dialogs
import QtCore
import CustomElements 1.0
import "qrc:/core/ui/items"
import "qrc:/core/ui/controls"

BlockBase {
    id: root
    width: 130*dp
    height: controller.anchorManager().presentationMode
        ? width * (image.implicitHeight / Math.max(image.implicitWidth, 1))
        : width * (image.implicitHeight / Math.max(image.implicitWidth, 1)) + 30*dp
    settingsComponent: settings

    // hide background in presentation mode:
    color: controller.anchorManager().presentationMode ? "transparent" : "#444"
    showShadows: !controller.anchorManager().presentationMode || block.attr("shadow").val

    z: -1  // always in background

    required property var block

    StretchColumn {
        height: parent.height
        width: parent.width

        BlockRow {
            implicitHeight: -1  // stretch
            Image {
                id: image
                anchors.fill: parent
                source: block.attr("filePath").val
                rotation: block.attr("rotation").val

                // --------------------- Position Help Lines ---------------

                Rectangle {  // left
                    height: 2000*dp
                    y: -1000*dp
                    width: 1*dp
                    x: 0*dp
                    color: Qt.rgba(0.3, 0.6, 1, 1)
                    visible: root.pressed
                }
                Rectangle {  // right
                    height: 2000*dp
                    y: -1000*dp
                    width: 1*dp
                    anchors.right: parent.right
                    color: Qt.rgba(0.3, 0.6, 1, 1)
                    visible: root.pressed
                }
                Rectangle {  // | center
                    height: 2000*dp
                    y: -1000*dp
                    width: 1*dp
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: Qt.rgba(0.3, 0.6, 1, 0.5)
                    visible: root.pressed
                }
                Rectangle {  // - center
                    width: 2000*dp
                    x: -1000*dp
                    height: 1*dp
                    anchors.verticalCenter: parent.verticalCenter
                    color: Qt.rgba(0.3, 0.6, 1, 0.5)
                    visible: root.pressed
                }
                Rectangle {  // top
                    width: 2000*dp
                    x: -1000*dp
                    height: 1*dp
                    y: 0*dp
                    color: Qt.rgba(0.3, 0.6, 1, 1)
                    visible: root.pressed
                }
                Rectangle {  // bottom
                    width: 2000*dp
                    x: -1000*dp
                    height: 1*dp
                    anchors.bottom: parent.bottom
                    color: Qt.rgba(0.3, 0.6, 1, 1)
                    visible: root.pressed
                }
            }
        }

        DragArea {
            text: "Image"
            visible: !controller.anchorManager().presentationMode

            WidthAndHeightResizeArea {
                target: root
                minSize: 60*dp
                maxSize: 2000*dp
            }
        }
    }

    // -------------------------- Settings ----------------------------

    Component {
        id: settings
        StretchColumn {
            leftMargin: 15*dp
            rightMargin: 15*dp
            defaultSize: 30*dp

            BlockRow {
                StretchText {
                    text: "File:"
                }
                ButtonBottomLine {
                    width: 60*dp
                    text: "Select"
                    onClick: fileDialogLoader.active = true
                }

                Loader {
                    id: fileDialogLoader
                    active: false

                    sourceComponent: FileDialog {
                        id: fileDialog
                        title: "Select Image File"
                        currentFolder: StandardPaths.writableLocation(StandardPaths.PicturesLocation)
                        fileMode: FileDialog.OpenFile
                        nameFilters: ["Image Files (*)"]
                        onAccepted: {
                            if (selectedFile) {
                                root.block.attr("filePath").val = selectedFile
                            }
                            fileDialogLoader.active = false
                        }
                        onRejected: {
                            fileDialogLoader.active = false
                        }
                        Component.onCompleted: {
                            // don't set visible to true before component is complete
                            // because otherwise the dialog will not be configured correctly
                            visible = true
                        }
                    }
                }
            }

            BlockRow {
                StretchText {
                    text: "Rotation:"
                }
                AttributeNumericInput {
                    width: 60*dp
                    implicitWidth: 0  // do not stretch
                    attr: block.attr("rotation")
                }
            }

            BlockRow {
                Text {
                    text: "Shadow:"
                    width: parent.width - 30*dp
                }
                AttributeCheckbox {
                    width: 30*dp
                    attr: block.attr("shadow")
                }
            }
        }
    }  // end Settings Component
}

