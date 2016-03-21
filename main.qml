import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import SlidingPuzzle 1.0

Window {
    id: mainWin
    title: "Sliding Puzzle"
    visible: true
    width: 600
    height: 600

    onWidthChanged: {
        height = width
        setOGLSize()
    }

    onHeightChanged: {
        setOGLSize()
        height = width
    }

    property bool sizeSet: true

    OGLItem {
        id: glItem
        width: 100
        height: 100
        x: 100
        y: 100

        MouseArea{
            id: glHitArea
            anchors.fill: parent
            onClicked: {
                glItem.handleMouseClicked(mouseX, mouseY);
                mainWin.requestUpdate()
            }
        }

        onGameEnd: {
            endMenu.visible = true
            completeText.text = "Complete!"
            sizeSet = false
        }
    }

    Item {
        id: miniImage
        width: mainWin.width
        height: mainWin.height

        Item {
            id: miniPicContainer
            anchors.right: parent.right
            anchors.top: parent.top
            state: "min"

            Image {
                source: "test_cat.png"
                anchors.fill: parent
            }

            Rectangle {
                anchors.fill: parent
                color: Qt.rgba(1,1,1,0)
                border {
                    width: 3
                    color: "black"
                }
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    miniPicContainer.state = "max"
                }

                onExited: {
                    miniPicContainer.state = "min"
                }
            }

            states: [
                State {
                    name: "max"
                    PropertyChanges {
                        target: miniPicContainer
                        width: miniImage.width < miniImage.height ? miniImage.width/2 : miniImage.height/2
                        height: miniImage.width < miniImage.height ? miniImage.width/2 : miniImage.height/2
                        opacity: 1
                    }
                },
                State {
                    name: "min"
                    PropertyChanges {
                        target: miniPicContainer
                        width: 50
                        height: 50
                        opacity: .5
                    }
                }
            ]

            transitions: [
                Transition {
                    NumberAnimation {
                        properties: "width, height, opacity"
                        easing.type: Easing.OutQuad
                        duration: 500
                    }
                }

            ]

            PropertyAnimation {
                id: minAnimation
                target: miniPicContainer
            }
        }
    }

    Item{
        id: endMenu
//        visible: false
        width: mainWin.width
        height: mainWin.height

        Rectangle {
            anchors.fill: parent;
            color: Qt.rgba(1,1,1,.3)
        }

        Text {
            id: completeText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: settingsLayout.top
            anchors.bottomMargin: 50
            text: "Sliding Puzzle Game"
            font{
                pixelSize: winReleativeSize(10)
            }
        }

        ColumnLayout {
            id: settingsLayout
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Puzzle Size"
                font{
                    pixelSize: winReleativeSize(20)
                }
            }

            Slider {
                id: puzzleSizeSlider
                anchors.horizontalCenter: parent.horizontalCenter
                minimumValue: 3
                maximumValue: 10
                stepSize: 1
                tickmarksEnabled: true
                value: 4

                style: SliderStyle {
                    groove: Rectangle {
                        implicitWidth: 200
                        implicitHeight: 8
                        color: "gray"
                        radius: 8
//                        Rectangle {
//                            width: styleData.handlePosition
//                            height: parent.height
//                            color: "white"
//                            radius: 8
//                        }
                    }
                    handle: Rectangle {
                        anchors.centerIn: parent
                        color: control.pressed ? "lightgrey" : "white"
                        border.width: 1
                        implicitWidth: 20
                        implicitHeight: width
                        radius: width/2
                    }
                }
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: puzzleSizeSlider.value + "X" + puzzleSizeSlider.value
                font{
                    pixelSize: winReleativeSize(25)
                }
            }
        }

        Button {
            id: setSizeBtn
            onClicked: {
                glItem.startGame(puzzleSizeSlider.value)
                sizeSet = true
            }
            anchors.topMargin: 20
            anchors.top: settingsLayout.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: winReleativeSize(3)
            height: width/4
            Label {
                text: "Set Size"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font {
                    pixelSize: parent.height * .5
                }
            }
        }

        Button {
            id: playAgainBtn
            onClicked: {
                endMenu.visible = false
                if (!sizeSet)
                {
                    glItem.startGame(puzzleSizeSlider.value)
                }

                glItem.enableInput()
            }
            anchors.topMargin: 20
            anchors.top: setSizeBtn.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: winReleativeSize(3)
            height: width/4
            Label {
                text: "Play"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font {
                    pixelSize: parent.height * .5
                }
            }
        }
    }

    Component.onCompleted: {
        setOGLSize()
    }

    function winReleativeSize(factor)
    {
        return mainWin.width < mainWin.height ? mainWin.width/factor : mainWin.height/factor;
    }

    function setOGLSize()
    {
        var least = mainWin.width < mainWin.height ? mainWin.width : mainWin.height;
        glItem.width = least;
        glItem.height = least;
        glItem.x = mainWin.width/2 - least/2
        glItem.y = mainWin.height/2 - least/2
    }
}
