import QtQuick
import QtQuick.Window 2.15
import QtQuick.Controls
import QtQuick.Layouts 1.3

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    color: "#232323"

    RowLayout{
        id: rowLayout
        anchors.fill: parent
        Layout.alignment: Qt.AlignCenter

        ColumnLayout {

            Layout.alignment: Qt.AlignCenter
            id: inputsparty
            spacing: 6

            // Party name
            TextField {
                id: partyname
                Layout.minimumWidth: 100
                Layout.preferredWidth: 300
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                Layout.alignment: Qt.AlignHCenter
                placeholderText: qsTr("Party name")
                background: Rectangle {
                    radius: 10
                    color: "#c9f1fd"
                }
            }

            // Number of people
            RowLayout {
                Label {
                    text: "Number of people"
                    color: "#c9f1fd"
                }

                SpinBox {
                    id: nbpeople
                    from: 1
                    value: 6
                }
            }

            // Minimum affinity
            RowLayout {
                Label {
                    text: "Minimum affinity"
                    color: "#c9f1fd"
                }
                ComboBox {
                    id: minaffinity
                    model: 11
                    delegate: ItemDelegate {
                        text: index
                    }
                }
            }

            // Date et heure
            RowLayout {
                Label {
                    text: "Date et heure"
                    color: "#c9f1fd"
                }
                TextField {
                    id: date
                    Layout.minimumWidth: 100
                    Layout.preferredWidth: 300
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    Layout.alignment: Qt.AlignHCenter
                    placeholderText: qsTr("Date")
                    background: Rectangle {
                        radius: 10
                        color: "#c9f1fd"
                    }
                }
                TextField {
                    id: time
                    Layout.minimumWidth: 100
                    Layout.preferredWidth: 300
                    horizontalAlignment: TextInput.AlignHCenter
                    verticalAlignment: TextInput.AlignVCenter
                    Layout.alignment: Qt.AlignHCenter
                    placeholderText: qsTr("Time")
                    background: Rectangle {
                        radius: 10
                        color: "#c9f1fd"
                    }
                }
            }

            // Location
            TextField {
                id: location
                Layout.minimumWidth: 100
                Layout.preferredWidth: 300
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                Layout.alignment: Qt.AlignHCenter
                placeholderText: qsTr("Location")
                background: Rectangle {
                    radius: 10
                    color: "#c9f1fd"
                }
            }

            // List of preview people
            ListModel {
                id: guestModel

                ListElement {
                    name: "Jeanne"
                }
                ListElement {
                    name: "Dorian"
                }
                ListElement {
                    name: "Tim"
                }
            }

            Component {
                id:guestDelegate
                Item {
                    id: wrapper
                    width: 150; height: 40
                    Row {
                        Label {
                            text: name;
                            background: Rectangle { color: wrapper.ListView.isCurrentItem ? "lightsteelblue" : "white" }
                            width: 110
                            height: 40
                            //Layout.alignment: Qt.AlignCenter
                        }

                        Button {
                            background: Rectangle{ color: wrapper.ListView.isCurrentItem ? "lightsteelblue" : "lightblue" }
                            text: qsTr("-")
                            //Layout.alignment: Qt.AlignLeft
                            height: 40
                            width: 40
                        }
                    }
                }
            }

            ScrollView
            {
                width: 180
                height: 200
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                Layout.alignment: Qt.AlignHCenter

                ListView{
                    anchors.fill: parent
                    model: guestModel
                    delegate: guestDelegate
                    //highlight: Rectangle { color: "lightsteelblue" }
                    focus: true
                }
            }

            // Add guest
            Button {
                id: addguest
                Layout.minimumWidth: 150
                Layout.preferredWidth: 150
                Layout.minimumHeight: 45
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Add guest")
                background: Rectangle {
                    radius: 10
                    color: addguest.down?'#b2a7f9':'#a8c6fa'
                }
            }

            // Create party
            Button {
                id: createParty
                Layout.minimumWidth: 150
                Layout.preferredWidth: 150
                Layout.minimumHeight: 45
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Create party")
                background: Rectangle {
                    radius: 10
                    color: createParty.down?'#b2a7f9':'#a8c6fa'
                }
            }
        }
    }
}
