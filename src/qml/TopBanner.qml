import QtQuick 2.9
import QtQuick.Layouts 1.3

RowLayout {
    id: topBannerArea
    width: topBannerSize.width
    height: topBannerSize.height

    property size topBannerSize
    property bool isMainPage: false
    signal backButtonClicked()

    Item {
        id: leftItem
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        Layout.fillHeight: true; Layout.fillWidth: true

        Item {
            id: backButton
            width: parent.width * 0.2
            height: parent.height>>1
            anchors.leftMargin: topBannerArea.width >> 4
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            visible: isMainPage ? false : true

            Image {
                id: backButtonImage
                fillMode: Image.PreserveAspectCrop
                anchors.fill: parent

                MouseArea {
                    id: buttonMouseArea
                    anchors.fill: parent
                    onClicked: backButtonClicked()
                }
            }

            states: [
                State {
                    name: "defaultState"; when: (buttonMouseArea.pressed === false)
                    PropertyChanges { target: backButtonImage; source: "file:///home/pi/sterilizer_gui/icon_img/back_pull.png" }
                },

                State {
                    name: "pressedState"; when: buttonMouseArea.pressed
                    PropertyChanges { target: backButtonImage; source: "file:///home/pi/sterilizer_gui/icon_img/back_push.png" }
                }
            ]
        }
    }

    Item {
        id: midItem
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        Layout.fillHeight: true; Layout.fillWidth: true

        Image {
            id: logoImage
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            sourceSize.height: parent.height * 1.2
            sourceSize.width: parent.width * 1.2
            fillMode: Image.PreserveAspectCrop
            source: "file:///home/pi/sterilizer_gui/icon_img/telco_logo.png"
        }
    }

    Item { id: rightItem; Layout.fillHeight: true; Layout.fillWidth: true }
}
