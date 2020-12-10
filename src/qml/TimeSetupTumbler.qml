import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Frame {
    id: outFrame
    width: frameSize.width
    height: frameSize.height
    topPadding: height * 0.05
    bottomPadding: topPadding
    rightPadding: width * 0.05
    leftPadding: rightPadding
    background: Rectangle {
        radius: 17
        gradient: Gradient {
            GradientStop { position: 0; color: "#444444" }
            GradientStop { position: 0.2; color: "#dbdbdb" }
            GradientStop { position: 0.8; color: "#dbdbdb" }
            GradientStop { position: 1; color: "#444444" }
        }
    }

    property size frameSize

    property int setHours: 0
    property int setMinutes: 0
    property int setBase: 0
    property alias getHours: hours.currentIndex
    property alias getMinutes: minutes.currentIndex
    property alias getBase: base.currentIndex

    property int hoursModel: 13
    property int hoursInterval: 1
    property int minutesInterval: 1
    property bool separatorOn: true
    property bool baseOn: true

    signal hoursChanged()
    signal minutesChanged()
    signal baseChanged()

    function formatText(modelData, interval) {
        var data = (interval)? modelData * interval : modelData
        return (data.toString().length) < 2 ? "0" + data : data
    }

    Component {
        id: tumblerDelegate
        Label {
            color: "white"
            text: formatText(modelData, Tumbler.tumbler.interval)
            font.family: "Tahoma"
            opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount >> 1)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: parent.width >> 1
        }
    }

    RowLayout {
        id: inFrame
        width: parent.width
        height: parent.height * 0.7
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Rectangle {
            id: baseFrame
            radius: 10
            visible: baseOn
            border.width: 1
            border.color: "black"
            Layout.fillWidth: true; Layout.fillHeight: true
            gradient: Gradient {
                GradientStop { position: 0; color: "black" }
                GradientStop { position: 0.3; color: "#565656" }
                GradientStop { position: 0.6; color: "#565656" }
                GradientStop { position: 1; color: "black" }
            }

            Tumbler {
                id: base
                model: ["오전", "오후"]
                anchors.fill: parent
                wheelEnabled: true
                visibleItemCount: 2
                delegate: tumblerDelegate
                currentIndex: setBase
                onCurrentIndexChanged: baseChanged()
            }
        }

        Item {
            id: baseSpacing
            Layout.fillHeight: true; Layout.preferredWidth: parent.width * 0.01
            visible: baseOn
        }

        Rectangle {
            id: hoursFrame
            radius: 10
            border.width: 1
            border.color: "black"
            Layout.fillWidth: true; Layout.fillHeight: true
            gradient: Gradient {
                GradientStop { position: 0; color: "black" }
                GradientStop { position: 0.3; color: "#565656" }
                GradientStop { position: 0.6; color: "#565656" }
                GradientStop { position: 1; color: "black" }
            }

            Tumbler {
                id: hours
                model: hoursModel/interval
                anchors.fill: parent
                wheelEnabled: true
                visibleItemCount: 3
                delegate: tumblerDelegate
                currentIndex: setHours
                onCurrentIndexChanged: hoursChanged()
                property int interval
                interval: hoursInterval
            }
        }

        Text {
            id: separator
            color: "black"
            text: ":"
            font.family: "Arial"
            font.pointSize: parent.height >> 1
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Layout.fillHeight: true; Layout.preferredWidth: parent.width * 0.05
            visible: separatorOn
        }

        Rectangle {
            id: minutesFrame
            radius: 10
            border.width: 1
            border.color: "black"
            Layout.fillWidth: true; Layout.fillHeight: true
            gradient: Gradient {
                GradientStop { position: 0; color: "black" }
                GradientStop { position: 0.3; color: "#565656" }
                GradientStop { position: 0.6; color: "#565656" }
                GradientStop { position: 1; color: "black" }
            }

            Tumbler {
                id: minutes
                model: 60/interval
                anchors.fill: parent
                wheelEnabled: true
                visibleItemCount: 3
                delegate: tumblerDelegate
                currentIndex: setMinutes
                onCurrentIndexChanged: minutesChanged()
                property int interval
                interval: minutesInterval
            }
        }
    }
}
