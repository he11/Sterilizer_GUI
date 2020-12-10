import QtQuick 2.9

Rectangle {
    id: menuButton
    radius: 20
    width: buttonSize.width
    height: buttonSize.height
    border.width: 3
    gradient: Gradient {
        GradientStop { id: gradientTop; position: 0 }
        GradientStop { id: gradientMiddle1; position: 0.2 }
        GradientStop { id: gradientMiddle2; position: 0.7 }
        GradientStop { id: gradientBottom; position: 1.0 }
    }

    property size buttonSize
    property alias name: buttonName.text

    Text {
        id: buttonName
        text: ""
        font.bold: true
        font.family: "Tahoma"
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.fill: parent
        font.pixelSize: parent.width * 0.09
    }

    signal buttonClicked()

    MouseArea {
        id: buttonMouseArea
        anchors.fill: parent
        onClicked: buttonClicked()
    }

    states: [
        State {
            name: "defaultState"; when: (buttonMouseArea.pressed === false)
            PropertyChanges { target: menuButton; border.color: "white" }
            PropertyChanges { target: gradientTop; color: "#46d200" }
            PropertyChanges { target: gradientMiddle1; color: "#a4ff76" }
            PropertyChanges { target: gradientMiddle2; color: "#a4ff76" }
            PropertyChanges { target: gradientBottom; color: "#46d200" }
            PropertyChanges { target: buttonName; color: "white" }
        },

        State {
            name: "pressedState"; when: buttonMouseArea.pressed
            PropertyChanges { target: menuButton; border.color: "#222222" }
            PropertyChanges { target: gradientTop; color: "#a4ff76" }
            PropertyChanges { target: gradientMiddle1; color: "#46d200" }
            PropertyChanges { target: gradientMiddle2; color: "#46d200" }
            PropertyChanges { target: gradientBottom; color: "#a4ff76" }
            PropertyChanges { target: buttonName; color: "black" }
        }
    ]
}
