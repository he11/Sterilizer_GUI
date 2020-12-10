import QtQuick 2.9

Item {
    id: exitButton
    width: buttonSize.width
    height: buttonSize.height

    property size buttonSize

    signal buttonClicked()

    Image {
        id: exitButtonImage
        fillMode: Image.PreserveAspectCrop
        anchors.fill: parent

        MouseArea {
            id: buttonMouseArea
            anchors.fill: parent
            onClicked: buttonClicked()
        }
    }

    states: [
        State {
            name: "defaultState"; when: (buttonMouseArea.pressed === false)
            PropertyChanges { target: exitButtonImage; source: "file:///home/pi/sterilizer_gui/icon_img/exit_app_icon.png" }
        },

        State {
            name: "pressedState"; when: buttonMouseArea.pressed
            PropertyChanges { target: exitButtonImage; source: "file:///home/pi/sterilizer_gui/icon_img/exit_app_icon_push.png" }
        }
    ]
}
