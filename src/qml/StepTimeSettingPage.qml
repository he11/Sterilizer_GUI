import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Page {
    id: stepTimeSettingPage
    background: PageScreen {}

    Connections { target: stepCtrl }
    signal qml_returnBack(var pageType)

    ColumnLayout{
        spacing: 0
        anchors.fill: parent

        Item {
            Layout.fillWidth: true; Layout.preferredHeight: parent.height * 0.2

            TopBanner {
                id: topBanner
                anchors.fill: parent
                isMainPage: false
                onBackButtonClicked: {
                    //console.log("Move to the back menu")
                    pageStack.pop()
                    qml_returnBack(255)
                }
            }
        }

        Item {
            id: titleBarArea
            Layout.fillWidth: true; Layout.preferredHeight: parent.height * 0.1

            TitleBar {
                id: titleBar
                height: parent.height
                anchors.rightMargin: parent.width >> 4
                anchors.leftMargin: parent.width >> 4
                anchors.left: parent.left
                anchors.right: parent.right
                titleName: "STEP TIME SETTING"
            }
        }

        Item {
            Layout.fillWidth: true; Layout.preferredHeight: parent.height * 0.45

            Item {
                id: tumblerArea
                width: parent.width * 0.6
                height: parent.height
                anchors.left: parent.left
                anchors.leftMargin: parent.width >> 4

                TimeSetupTumbler {
                    id: stepSetupTumbler
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width >> 5
                    frameSize: Qt.size(parent.width * 0.85, parent.height * 0.8)
                    setHours: stepCtrl.hoursVal
                    setMinutes: stepCtrl.minutesIdx
                    onHoursChanged: stepCtrl.hoursVal = getHours
                    onMinutesChanged: stepCtrl.minutesIdx = getMinutes
                    minutesInterval: stepCtrl.mInterval
                    hoursModel: 25
                    baseOn: false
                }
            }
            Item {
                id: buttonArea
                height: parent.height
                anchors.left: tumblerArea.right
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: parent.width >> 4

                MenuButton {
                    id: storeButton
                    radius: 36
                    anchors.right: parent.right
                    anchors.rightMargin: parent.width >> 3
                    anchors.verticalCenter: parent.verticalCenter
                    buttonSize: Qt.size(parent.width * 0.65, parent.width * 0.65)
                    border.width: 2
                    onButtonClicked: { stepCtrl.reqToStore() }

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

        Item {
            id: setInfoArea
            Layout.fillWidth: true; Layout.preferredHeight: parent.height * 0.25

            Text {
                id: setStepTime
                text: "반복 시간 : " + formatText(stepCtrl.savedHours) + ":" + formatText(stepCtrl.savedMinutes)
                anchors.horizontalCenter: parent.horizontalCenter
                color: "yellow"
                font.family: "Tahoma"
                font.bold: true
                anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: parent.width >> 4

                function formatText(targetData) { return targetData.toString().length < 2 ? "0" + targetData : targetData; }
            }
        }
    }

    Text {
        id: errMessage
        color: "red"
        text: "유효하지 않은 범위입니다. 다시 설정해주세요." //"Invalid range is set"
        font.bold: true
        font.family: "Times New Roman"
        font.pointSize: parent.width * 0.03
        anchors.right: parent.right
        anchors.rightMargin: parent.width >> 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.2
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        visible: stepCtrl.errState
    }
}
