import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import SlidingPuzzle 1.0

Window {
    id: mainWin
    visible: true
    width: 600
    height: 600

    onWidthChanged: {
        setOGLSize()
    }

    onHeightChanged: {
        setOGLSize()
    }

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
            endItem.visible = true
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
        id: endItem
        visible: false
        width: mainWin.width
        height: mainWin.height

        Rectangle {
            anchors.fill: parent;
            color: Qt.rgba(1,1,1,.3)
        }

        Text {
            id: completeText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: "Complete!"
            font{
                pixelSize: parent.width < parent.height ? parent.width/10 : parent.height/10
            }
        }

        Button {
            id: playAgainBtn
            onClicked: {
                glItem.startGame(4)
                endItem.visible = false
            }
            anchors.topMargin: 20
            anchors.top: completeText.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width < parent.height ? parent.width/3 : parent.height/3
            height: width/4
            Label {
                text: "Play Again"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font {
                    pixelSize: parent.height * .5
                }
            }
        }

//        Button {
//            id: settingsBtn
//            onClicked: console.log("Settings")
//            anchors.top: playAgainBtn.bottom
//            anchors.horizontalCenter: parent.horizontalCenter
//            width: parent.width < parent.height ? parent.width/3 : parent.height/3
//            height: width/4
//            Label {
//                text: "Settings"
//                anchors.horizontalCenter: parent.horizontalCenter
//                anchors.verticalCenter: parent.verticalCenter
//                font {
//                    pixelSize: parent.height * .5
//                }
//            }
//        }
    }

    Component.onCompleted: {
        setOGLSize()
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
