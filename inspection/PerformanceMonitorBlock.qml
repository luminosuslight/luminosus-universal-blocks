import QtQuick 2.12
import CustomElements 1.0
import "qrc:/core/ui/items"
import "qrc:/core/ui/controls"

BlockBase {
    id: root
    width: 300*dp
    height: 150*dp

    property bool fpsTestRunning: false

    StretchColumn {
        anchors.fill: parent

        StretchRow {
            height: 120*dp

            Item {
                width: 60*dp

                Image {
                    width: 45*dp
                    height: 45*dp
                    anchors.centerIn: parent
                    source: "qrc:/core/ui/images/plus_icon.png"

                    RotationAnimator on rotation {
                        from: 0;
                        to: 360;
                        duration: 10 * 1000  // 10s per full rotation
                        loops: Animation.Infinite
                        running: fpsTestRunning
                    }

                    CustomTouchArea {
                        anchors.fill: parent
                        onClick: fpsTestRunning = !fpsTestRunning
                    }
                }
            }

            StretchColumn {
                implicitWidth: -1
                leftMargin: 10*dp

                BlockRow {
                    rightMargin: 15*dp
                    StretchText {
                        text: "Version:"
                        hAlign: Text.AlignLeft
                    }
                    StretchText {
                        text: controller.getVersionString()
                        hAlign: Text.AlignRight
                        font.family: "Courier"
                    }
                }
                BlockRow {
                    rightMargin: 15*dp
                    StretchText {
                        text: "Qt Runtime:"
                        hAlign: Text.AlignLeft
                    }
                    StretchText {
                        text: block.getQtRuntimeVersion()
                        hAlign: Text.AlignRight
                        font.family: "Courier"
                    }
                }
                BlockRow {
                    rightMargin: 15*dp
                    StretchText {
                        text: "FPS:"
                        hAlign: Text.AlignLeft
                    }
                    StretchText {
                        property real t
                        color: (!fpsTestRunning || fpsTimer.fps > 30) ? "white" : "#f22"
                        text: fpsTestRunning ? fpsTimer.fps : "[click image]"
                        hAlign: Text.AlignRight
                        font.family: "Courier"

                        Timer {
                            id: fpsTimer
                            property real fps: 0
                            property int frame: 0
                            repeat: true
                            interval: 1000
                            running: fpsTestRunning
                            onTriggered: {
                                fps = frame
                                frame = 0
                            }
                        }

                        NumberAnimation on t {
                            id: tAnim
                            from: 0
                            to: 100
                            loops: Animation.Infinite
                            running: fpsTestRunning
                        }

                        onTChanged: {
                            update() // force continuous animation
                            ++fpsTimer.frame
                        }
                    }
                }
                BlockRow {
                    StretchText {
                        text: "CPU:"
                        hAlign: Text.AlignLeft
                    }
                    StretchText {
                        text: (block.attr("cpuUsage").val * 100).toFixed(1) + " %"
                        hAlign: Text.AlignRight
                        font.family: "Courier"
                    }
                    OutputNode {
                        node: block.node("outputNode")
                    }
                }
            }  // end text column
        }  // end content Row

        DragArea {
            text: "Luminosus Info"
        }
    }  // end main Column
}
