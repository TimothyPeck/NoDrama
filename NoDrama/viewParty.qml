import QtQuick 2.0
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

    /* Si tu veux voir comment c'est senser marcher
    ScrollView {
        width: 180
        height:200
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        background: Rectangle { color: "#c9f1fd" }

        ListView{
            anchors.fill: parent
            model: GuestList {} //TO-DO
            delegate: guestDelegate
        }
    }
    */

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
                      height: 25; // chaque element
                      Row {
                          Label{
                              text: name
                              horizontalAlignment: TextInput.AlignHCenter
                              background: Rectangle{
                                  radius: 3
                                  color: "#a8c6fa" }
                              width: 150
                              height: 20
                          }
                      }
                  }
           }

            ScrollView {  // bonne place, mais pas les bons comportements dans un layout
                width: 180
                height:200
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                background: Rectangle { color: "#c9f1fd" }

                ListView{
                    anchors.fill: parent
                    model: GuestList {} //TO-DO
                    delegate: guestDelegate
                }
            }

            RowLayout
            {
                id: gridLayout
                Layout.alignment: Qt.AlignCenter
                Button {
                    id: btnDelete
                    Layout.minimumWidth: 50
                    Layout.preferredWidth: 50
                    Layout.minimumHeight: 25
                    Layout.alignment: Qt.AlignLeft
                    text: qsTr("Delete")
                    background: Rectangle {
                        radius: 10
                        color: btnDelete.down?'#b2a7f9':'red'
                    }
                                 /*
                                 onClicked: {
                                     var component = Qt.createComponent("./calendrier.qml")
                                     var window = component.createObject(loginWindow)
                                     window.show()
                                 }
                                 */

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
            }

        } // ferme colonne
    }// ferme row

} //ferme appli
