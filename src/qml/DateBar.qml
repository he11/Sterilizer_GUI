import QtQuick 2.9

Rectangle {
    id: dateBar
    width: dateBarSize.width
    height: dateBarSize.height
    radius: 15
    border.width: 2
    border.color: "#303030"
    gradient: Gradient {
        GradientStop { position: 0; color: "#8f8f8f" }
        GradientStop { position: 0.4; color: "white" }
        GradientStop { position: 0.6; color: "white" }
        GradientStop { position: 1; color: "#8f8f8f" }
    }

    property size dateBarSize
    property alias currentDate: localDate.text

    Text {
        id: localDate
        color: "black"
        text: ""
        font.family: "Tahoma"
        font.pointSize: parent.width * 0.022 // size bug
        font.bold: true
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
