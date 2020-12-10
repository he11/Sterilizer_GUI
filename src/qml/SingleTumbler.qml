import QtQuick 2.9
import QtQuick.Controls 2.3

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

    property bool startZero: true
    property alias dataModel: target.model
    property alias setTarget: target.currentIndex
    property alias getTarget: target.currentIndex

    signal valueChanged()

    function formatText(modelData, startZero) {
        var data = startZero? modelData : modelData + 1
        return data.toString().length < 2 ? "0" + data : data;
    }

    Component {
        id: tumblerDelegate
        Label {
            color: "white"
            text: formatText(modelData, startZero)
            font.family: "Tahoma"
            opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount >> 1)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: parent.width >> 1
        }
    }

    Rectangle {
        id: inFrame
        radius: 10
        border.width: 1
        border.color: "black"
        width: parent.width
        height: parent.height * 0.7
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        gradient: Gradient {
            GradientStop { position: 0; color: "black" }
            GradientStop { position: 0.3; color: "#565656" }
            GradientStop { position: 0.6; color: "#565656" }
            GradientStop { position: 1; color: "black" }
        }

        Tumbler {
            id: target
            anchors.fill: parent
            wheelEnabled: true
            visibleItemCount: 3
            delegate: tumblerDelegate
            onCurrentIndexChanged: valueChanged()
        }
    }
}
