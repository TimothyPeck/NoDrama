import QtQuick
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: loginWindow
    //width: 640
    //height: 480
    visible: true
    title: qsTr("Hello World")
    color: "#232323"

    RowLayout{
        id: rowLayout
        anchors.fill: parent
        Layout.alignment: Qt.AlignCenter
        ColumnLayout {

            Layout.alignment: Qt.AlignCenter
            id: inputs
            spacing: 6

            Image {
                id: logo
                source: ":/images/images/NoDramaTranparent.PNG"
            }

            RowLayout{
                Text {
                    id: userActiveText
                    text: qsTr("Current user: ")
                    font.pointSize: 25
                    color: 'white'
                }

                Text {
                    id: userActive
                    text: qsTr(" blablabla")
                    font.pointSize: 20
                    color: 'white'
                }
            }

            Text {
                id: infoHeader
                text: qsTr("NoDrama Team")
                font.pointSize: 50
                color: 'white'
            }

            Text {
                id: memberOne
                text: qsTr("Michel Jeanne Thèrèse")
                font.pointSize: 25
                color: 'white'
            }

            Text {
                id: memberTwo
                text: qsTr("Peck Timothy Roy")
                font.pointSize: 25
                color: 'white'
            }

            Text {
                id: memberThree
                text: qsTr("Tan Dorian")
                font.pointSize: 25
                color: 'white'
            }
        }
    }
}
