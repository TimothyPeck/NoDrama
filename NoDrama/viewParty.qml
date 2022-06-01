import QtQuick
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: loginWindow
    width: 360
    height: 640
    visible: true
    title: qsTr("Hello World")
    color: "#232323"

    RowLayout
    {
        id: gridLayout
        Layout.alignment: Qt.AlignCenter

        Button {
            id: back
            Layout.minimumWidth: 50
            Layout.preferredWidth: 50
            Layout.minimumHeight: 25
            Layout.alignment: Qt.AlignLeft
            text: qsTr("<--")
            background: Rectangle {
                radius: 10
                color: createAccountButton.down?'#b2a7f9':'#a8c6fa'
            }
        }

        Button {
            id: btnDelete
            Layout.minimumWidth: 50
            Layout.preferredWidth: 50
            Layout.minimumHeight: 25
            Layout.alignment: Qt.AlignRight
            text: qsTr("Delete")
            background: Rectangle {
                radius: 10
                color: btnDelete.down?'#b2a7f9':'red'
            }
        }
    }

    RowLayout{ //une seul ligne
        id: rowLayout
        anchors.fill: parent
        Layout.alignment: Qt.AlignCenter

        ColumnLayout { // une seul colonne mais plusieur ligne

            Layout.alignment: Qt.AlignCenter
            id: inputs
            spacing: 6

            Label {
                id: username
                Layout.minimumHeight: 30
                text: "Party Name"
                Layout.minimumWidth: 100
                Layout.preferredWidth: 300

                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                Layout.alignment: Qt.AlignHCenter
                background: Rectangle {
                    radius: 3
                    height: 30
                    color: "#a8c6fa"
                }
            }

            Label {
                id: partyDate
                Layout.minimumHeight: 30
                text: "dd/mm/aaa"
                Layout.minimumWidth: 100
                Layout.preferredWidth: 300
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                Layout.alignment: Qt.AlignHCenter
                background: Rectangle {
                    radius: 3
                    height: 30
                    color: "white"
                }
            }

            Label {
                id: location
                Layout.minimumHeight: 30
                text: "Lieu"
                Layout.minimumWidth: 100
                Layout.preferredWidth: 300
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                Layout.alignment: Qt.AlignHCenter
                background: Rectangle {
                    radius: 3
                    height: 30
                    color: "#a8c6fa"
                }
            }

            Label {
                id: guests
                text: "Invités"
                Layout.minimumHeight: 20
                Layout.minimumWidth: 100
                Layout.preferredWidth: 300
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                Layout.alignment: Qt.AlignHCenter
                background: Rectangle {
                    radius: 3
                    height: 20
                    color: "lightgrey"
                }
            }

            // Scroll view of the list of predetermined guests
            ScrollView
            {
                id: guestsScrollView
                anchors.top: guests.bottom
                anchors.topMargin: 3
                width: 280
                height: 300
                contentWidth: 280
                contentHeight: 300
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                Layout.alignment: Qt.AlignHCenter

                ListView{
                    anchors.fill: parent
                    focus: true
                    model: GuestList {} // guestModel
                    delegate:
                        Item {
                        id: wrapper
                        width: 280;
                        height: 40

                        Row {
                            Label {
                                leftPadding: 15
                                verticalAlignment: Text.AlignVCenter
                                text: name;
                                background: Rectangle {
                                    color: "white"
                                    //color: wrapper.ListView.isCurrentItem ? "lightsteelblue" : "white"
                                    border.color: "#cccccc";
                                    border.width:0.5
                                }
                                width: 280
                                height: 40
                                //Layout.alignment: Qt.AlignCenter
                            }
                        }
                    }
                }
            }
        } // ferme colonne
    }// ferme row
} //ferme appli
