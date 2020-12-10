import QtQuick 2.9
import QtQuick.Controls 2.3

Item {
    id: errorPopup
    implicitWidth: parent.width
    implicitHeight: parent.height

    Popup {
        id: popupArea
        width: parent.width
        height: parent.height
        background: Rectangle {
            color: "white"
            opacity: 0.7
        }

        Rectangle {
            id: popupWindow
            width: parent.width >> 1
            height: parent.height >> 4
            color: "black"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            radius: 15
        }

        Text {
            id: errorMessage
            color: "white"
            anchors.horizontalCenter: popupWindow.horizontalCenter
            anchors.verticalCenter: popupWindow.verticalCenter
            font.bold: true
            font.family: "Times New Roman"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        MouseArea { anchors.fill: parent; onClicked: { closeErrorPopup() }}
    }

    function openErrorPopup(errorMsg, msgSize) {
        errorMessage.text = errorMsg
        errorMessage.font.pointSize = (msgSize)? msgSize : parent.width * 0.02
        popupArea.open()
    }

    function closeErrorPopup() {
        popupArea.close()
    }

}
