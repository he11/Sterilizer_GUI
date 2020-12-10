import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Page {
    id: mainPage
    background: PageScreen {}

    Connections { target: mainMenuCtrl }
    function qml_updateDate(updateDate) { dateBar.currentDate = updateDate }

    Component {
        id: menualPage
        ManualTimeSettingPage {
            id: manualTimeSettingPage
            objectName: "manualTimeSettingPage"
        }
    }

    Component {
        id: stepPage
        StepTimeSettingPage {
            id: stepTimeSettingPage
            objectName: "stepTimeSettingPage"
        }
    }

    TopBanner {
        id: topBanner
        topBannerSize: Qt.size(parent.width, parent.height * 0.2)
        isMainPage: true
    }

    RowLayout {
        id: menuArea
        height: parent.height * 0.24
        anchors.top: topBanner.bottom
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: parent.width >> 5
        anchors.right: parent.right
        anchors.rightMargin: parent.width >> 5

        Item {
            Layout.fillHeight: true; Layout.fillWidth: true

            MenuButton {
                id: menualTimeSettingButton
                name: "MANUAL\nTIME SETTING\n(동작시간 설정)"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                buttonSize: Qt.size(parent.width * 0.8, parent.height * 0.8)
                onButtonClicked: {
                    //console.log("Move to the menual time setting page")
                    pageStack.push(menualPage)
                    mainMenuCtrl.movePage(1)
                }
            }
        }

        Item {
            Layout.fillHeight: true; Layout.fillWidth: true

            MenuButton {
                id: stepTimeSettingButton
                name: "STEP\nTIME SETTING\n(반복시간 설정)"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                buttonSize: Qt.size(parent.width * 0.8, parent.height * 0.8)
                onButtonClicked: {
                    //console.log("Move to the step time setting page")
                    pageStack.push(stepPage)
                    mainMenuCtrl.movePage(2)
                }
            }
        }

        Item {
            Layout.fillHeight: true; Layout.fillWidth: true

            MenuButton {
                id: runButton
                name: "START\n(동    작)"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                buttonSize: Qt.size(parent.width * 0.8, parent.height * 0.8)
                onButtonClicked: {
                    mainMenuCtrl.runSterilization(5)
                }
            }
        }
    }

    RowLayout {
        id: dateArea
        height: parent.height * 0.18
        anchors.top: menuArea.bottom
        anchors.topMargin: 0
        anchors.rightMargin: parent.width >> 4
        anchors.leftMargin: parent.width >> 4
        anchors.left: parent.left
        anchors.right: parent.right

        Item {
            id: element
            Layout.fillHeight: true; Layout.fillWidth: true

            DateBar {
                id: dateBar
                anchors.top: parent.top
                anchors.topMargin: parent.height >> 3
                dateBarSize: Qt.size(parent.width, parent.height * 0.6)
            }
        }
    }
}
