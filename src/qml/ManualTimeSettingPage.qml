import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Page {
    id: manualTimeSettingPage
    background: PageScreen {}

    Connections { target: manualCtrl }
    signal qml_returnBack(var pageType)

    TopBanner {
        id: topBanner
        topBannerSize: Qt.size(parent.width, parent.height * 0.2)
        isMainPage: false
        onBackButtonClicked: {
            //console.log("Move to the back menu")
            pageStack.pop()
            qml_returnBack(255)
        }
    }

    RowLayout {
        id: titleBarArea
        height: parent.height * 0.1
        anchors.top: topBanner.bottom
        anchors.topMargin: 0
        anchors.rightMargin: parent.width >> 4
        anchors.leftMargin: parent.width >> 4
        anchors.left: parent.left
        anchors.right: parent.right

        Item {
            Layout.fillHeight: true; Layout.fillWidth: true

            TitleBar {
                id: titleBar
                anchors.fill: parent
                titleName: "MANUAL TIME SETTING"
            }
        }
    }

    RowLayout {
        id: settingArea
        height: parent.height * 0.3
        spacing: 0
        anchors.top: titleBarArea.bottom
        anchors.topMargin: 0
        anchors.rightMargin: parent.width >> 4
        anchors.leftMargin: parent.width >> 4
        anchors.left: parent.left
        anchors.right: parent.right

        Item {
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.45

            TimeSetupTumbler {
                id: menualSetupTumbler
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                frameSize: Qt.size(parent.width * 0.9, parent.height * 0.8)
                setHours: manualCtrl.hoursVal
                setMinutes: manualCtrl.minutesVal
                setBase: manualCtrl.baseVal
                onHoursChanged: manualCtrl.hoursVal = getHours
                onMinutesChanged: manualCtrl.minutesVal = getMinutes
                onBaseChanged: manualCtrl.baseVal = getBase
            }
        }

        Item {
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.22

            Text {
                id: describeItem
                text: "지속 시간" //qsTr("KEEP")
                color: "white"
                font.family: "Tahoma"
                font.bold: true
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: parent.width * 0.2
            }
        }

        Item {
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.15

            SingleTumbler {
                id: durationTumbler
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                frameSize: Qt.size(parent.width * 0.7, parent.width * 0.7)
                dataModel: 61
                setTarget: manualCtrl.durationVal
                onValueChanged: manualCtrl.durationVal = getTarget
            }
        }

        Item {
            Layout.fillHeight: true; Layout.fillWidth: true

            MenuButton {
                id: storeButton
                radius: 36
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                buttonSize: Qt.size(parent.width * 0.55, parent.width * 0.55)
                border.width: 2
                onButtonClicked: {
                    if (manualCtrl.hoursVal && manualCtrl.durationVal) { manualCtrl.reqToStore() }
                    else { manualCtrl.displayError() }
                }

                Image {
                    id: storeImage
                    width: parent.width * 0.7
                    height: width
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    fillMode: Image.PreserveAspectCrop
                    source: parent.state === "pressedState"? "file:///home/pi/sterilizer_gui/icon_img/store_push.png" : "file:///home/pi/sterilizer_gui/icon_img/store_pull.png"
                }
            }
        }
    }

    Text {
        id: errMessage
        color: "red"
        text: "필수 설정 항목: 시간, 지속 시간"
        font.bold: true
        font.family: "Times New Roman"
        font.pointSize: parent.width * 0.02
        anchors.right: parent.right
        anchors.rightMargin: parent.width >> 4
        anchors.bottom: settingArea.bottom
        anchors.bottomMargin: 0
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        visible: manualCtrl.errState
    }
}
