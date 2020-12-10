import QtQuick 2.9

Rectangle {
    id: titleBar
    width: titleBarSize.width
    height: titleBarSize.height
    radius: 7
    gradient: Gradient {
        GradientStop { position: 0; color: "#222222" }
        GradientStop { position: 0.3; color: "black" }
        GradientStop { position: 1.3; color: "#222222" }
    }
    border.width: 2
    border.color: "white"

    property size titleBarSize
    property alias titleName: titleBarName.text

    Text {
        id: titleBarName
        color: "#2deaff"
        text: ""
        anchors.fill: parent
        font.family: "Tahoma"
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: width * 0.04
    }
}
