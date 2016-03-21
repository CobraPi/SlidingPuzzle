import QtQuick 2.6
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
