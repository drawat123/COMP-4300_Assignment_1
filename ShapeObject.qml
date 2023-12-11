import QtQuick

Rectangle {
    id: rectangle
    x: 100
    y: 100
    width: 100
    height: 100
    color: Qt.rgba(1, 0, 0, 1)
    property real sx: 1.5
    property real sy: 2.4
    property string text: ""
    property color fontColor: Qt.rgba(1, 1, 1, 1)
    property int fontSize: 12
    property url fontFilePath: ""

    FontLoader {
        id: fontLoader
        source: fontFilePath
    }

    Text {
        text: parent.text
        anchors.centerIn: parent
        color: parent.fontColor
        font.family: fontLoader.name
        font.pixelSize: parent.fontSize
    }
}
