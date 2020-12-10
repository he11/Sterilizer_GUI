import QtQuick 2.9

Rectangle {
    id: pageScreen
    implicitWidth: parent.width
    implicitHeight: parent.height
    gradient: Gradient {
        GradientStop { position: 0; color: "#121212"; }
        GradientStop { position: 1; color: "#000000"; }
    }
}
