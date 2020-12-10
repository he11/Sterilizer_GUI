import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import "."

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    color: "white"
    visibility: "FullScreen"

    Connections { target: mainCtrl }
    ErrorPopup { id: errorPopUp }
    //function qml_displayError() { errMessage.visible = true }
    //function qml_errMsgTimeOut() { errMessage.visible = false }
    //function qml_displayList(isOn) { scheduleList.visible = isOn }
    function qml_updateList(idx) { scheduleList.model.insert(idx, {"reservedTime": mainCtrl.getSetTimeStr(idx)})}

    Component {
        id: initPage
        MainPage {
            id: mainPage
            objectName: "mainPage"
        }
    }

    StackView
    {
        id: pageStack
        objectName: "pageStack"
        anchors.fill: parent

        replaceEnter: Transition { PropertyAnimation { property: "opacity"; from: 1; to: 1; duration: 0 }}
        replaceExit: Transition { PropertyAnimation { property: "opacity"; from: 1; to: 1; duration: 0 }}
        pushEnter: Transition { PropertyAnimation { property: "opacity"; from: 1; to: 1; duration: 0 }}
        pushExit: Transition { PropertyAnimation { property: "opacity"; from: 1; to: 1; duration: 0 }}
        popEnter: Transition { PropertyAnimation { property: "opacity"; from: 1; to: 1; duration: 0 }}
        popExit: Transition { PropertyAnimation { property: "opacity"; from: 1; to: 1; duration: 0 }}

        initialItem: initPage
    }

    Component.onCompleted: {
        for (var i=0; i<mainCtrl.getListSize(); i++) {
            scheduleList.model.append({"reservedTime": mainCtrl.getSetTimeStr(i)})
        }
    }

    Component {
        id: listDelegate
        Rectangle {
            id: inFrame
            width: scheduleList.width
            height: scheduleList.height * 0.2
            border.width: 2
            radius: 8
            gradient: Gradient {
                GradientStop { id: gradientTop; position: 0 }
                GradientStop { id: gradientMiddle; position: 0.3 }
                GradientStop { id: gradientBottom; position: 1.3 }
            }

            Label {
                id: objLabel
                font.bold: true
                font.family: "Tahoma"
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: parent.height * 0.6
                text: reservedTime
            }

            MouseArea {
                id: objDeleteArea
                anchors.fill: parent
                onClicked: {
                    //console.log("Delete selected object(" + index + ")")
                    mainCtrl.rmSetTime(index)
                    scheduleList.model.remove(index)
                }
            }

            states: [
                State {
                    name: "defaultState"; when: (objDeleteArea.pressed === false)
                    PropertyChanges { target: inFrame; border.color: "black" }
                    PropertyChanges { target: gradientTop; color: "#222222" }
                    PropertyChanges { target: gradientMiddle; color: "black" }
                    PropertyChanges { target: gradientBottom; color: "#222222" }
                    PropertyChanges { target: objLabel; color: "yellow" }
                },

                State {
                    name: "pressedState"; when: objDeleteArea.pressed
                    PropertyChanges { target: inFrame; border.color: "white" }
                    PropertyChanges { target: gradientTop; color: "white" }
                    PropertyChanges { target: gradientMiddle; color: "white" }
                    PropertyChanges { target: gradientBottom; color: "#626262" }
                    PropertyChanges { target: objLabel; color: "black" }
                }
            ]
        }
    }

    Text {
        id: errMessage
        color: "red"
        text: "시간 설정 실패(최대 설정 개수: 5)" //"To set the data is failure(Max: 5)"
        font.bold: true
        font.family: "Times New Roman"
        font.pointSize: parent.width * 0.02
        anchors.right: parent.right
        anchors.rightMargin: parent.width >> 4
        anchors.bottom: scheduleList.top
        anchors.bottomMargin: 0
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        visible: mainCtrl.errState
    }

    ListView {
        id: scheduleList
        objectName: "scheduleList"
        height: parent.height * 0.3
        boundsBehavior: Flickable.StopAtBounds
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.09
        anchors.right: parent.right
        anchors.rightMargin: parent.width >> 4
        anchors.left: parent.left
        anchors.leftMargin: parent.width >> 4
        model: ListModel{}
        delegate: listDelegate
        visible: mainCtrl.displayList

        Rectangle {
            id: outFrame
            anchors.fill: parent
            color: "#00000000"
            border.color: "white"
            border.width: 2
            radius: 8
        }
    }

    Item {
        id: exitButtonArea
        width: parent.width
        height: parent.height * 0.2
        visible: mainCtrl.displayExit

        ExitButton {
            id: exitButton
            anchors.right: parent.right
            anchors.rightMargin: parent.width >> 4
            buttonSize: Qt.size(parent.width >> 4, parent.height >> 1)
            anchors.verticalCenter: parent.verticalCenter
            onButtonClicked: {
                mainCtrl.stopSterilization()
                mainWindow.close()
            }
        }
    }
}
