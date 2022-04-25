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

            Label {
                id: username
                text: "Party Name"
                Layout.minimumWidth: 100
                Layout.preferredWidth: 300
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                Layout.alignment: Qt.AlignHCenter
                background: Rectangle {
                    radius: 3
                    color: "#a8c6fa"
                }
            }

            Label {
                id: partyDate
                text: "dd/mm/aaa"
                Layout.minimumWidth: 100
                Layout.preferredWidth: 300
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                Layout.alignment: Qt.AlignHCenter
                background: Rectangle {
                    radius: 3
                    color: "white"
                }
            }

            Label {
                id: location
                text: "Lieu"
                Layout.minimumWidth: 100
                Layout.preferredWidth: 300
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                Layout.alignment: Qt.AlignHCenter
                background: Rectangle {
                    radius: 3
                    color: "#a8c6fa"
                }
            }

            Component {
                            id: guestDelegate
                            Item {
                                width: 180;
                                height: 25;
                                Row {
                                    Text { text: name }
                                }
                            }
                        }

                        ScrollView
                        {
                            width: 180
                            height: 100

                            ListView{
                                anchors.fill: parent
                                model: GuestList {} //TO-DO
                                delegate: guestDelegate
                                highlight: Rectangle { color: "lightsteelblue" }
                                focus: true
                            }
                        }

                        Button {
                             id: back
                             Layout.minimumWidth: 50
                             Layout.preferredWidth: 50
                             Layout.minimumHeight: 25
                             Layout.alignment: Qt.AlignRight
                             text: qsTr("<--")
                             background: Rectangle {
                                 radius: 10
                                 color: createAccountButton.down?'#b2a7f9':'#a8c6fa'
                             }
                             /*
                             onClicked: {
                                 var component = Qt.createComponent("./calendrier.qml")
                                 var window = component.createObject(loginWindow)
                                 window.show()
                             }
                             */

                         }
/*ferme column*/ }


    }

}
