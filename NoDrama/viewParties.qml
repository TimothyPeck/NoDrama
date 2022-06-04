import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: viewParties
    width: 360
    height: 640
    visible: true
    title: qsTr("My parties")
    color: "#232323"

    RowLayout
    {
        id: gridLayout
        Layout.alignment: Qt.AlignCenter

        Button {
            id: friends
            Layout.minimumWidth: 50
            Layout.preferredWidth: 50
            Layout.minimumHeight: 25
            Layout.alignment: Qt.AlignLeft
            text: qsTr("Friends")
            background: Rectangle {
                radius: 10
                color: friends.down?'#b2a7f9':'#a8c6fa'
            }

            onClicked: {
                var component = Qt.createComponent("./friendsPage.qml")
                var window = component.createObject(viewParties)
                window.show()
            }
        }

        Button {
            id: createParty
            Layout.minimumWidth: 100
            Layout.preferredWidth: 100
            Layout.minimumHeight: 25
            Layout.alignment: Qt.AlignRight
            text: qsTr("Create party")
            background: Rectangle {
                radius: 10
                color: createParty.down?'#b2a7f9':'#a8c6fa'
            }

            onClicked: {
                var component=Qt.createComponent("./createParty.qml")
                var window = component.createObject(viewParties)
                window.show()
            }
        }
    }

    ColumnLayout { // une seul colonne mais plusieur ligne
        anchors.fill: parent
        // Scroll view of the list of predetermined guests
        ScrollView
        {
            id: guestsScrollView
            anchors.top: createParty.bottom
            anchors.topMargin: 10
            width: 360
            height: 585
            contentWidth: 360
            contentHeight: 585
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            Layout.alignment: Qt.AlignHCenter

            ListView{
                anchors.topMargin: 10
                anchors.fill: parent
                focus: true
                model: PartiesList {}
                delegate:
                    Item {
                    id: wrapper
                    width: 360;
                    height: 110

                    Column {
                        Rectangle
                        {
                            width: 360
                            height: 30
                            color: "lightsteelblue"
                            Label{
                                anchors.fill: parent
                                text: name
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                            }
                        }
                        Rectangle{
                            width: 360
                            height: 70
                            color: "white"
                            Column{
                                Row {
                                    Label {
                                        text: date
                                        horizontalAlignment: Text.AlignLeft
                                        leftPadding: 15
                                        topPadding: 5
                                    }
                                    Label {
                                        text: time
                                        horizontalAlignment: Text.AlignRight
                                        leftPadding: 15
                                        topPadding: 5
                                    }
                                }

                                Label {
                                    topPadding: 4
                                    leftPadding: 15
                                    verticalAlignment: Text.AlignVCenter
                                    text: organiser;
                                    //Layout.alignment: Qt.AlignCenter
                                }
                                Label {
                                    topPadding: 4
                                    leftPadding: 15
                                    verticalAlignment: Text.AlignVCenter
                                    text: place;
                                    //Layout.alignment: Qt.AlignCenter
                                }
                            }
                        }
                    }
                }
            }
        }
    } // ferme colonne
} //ferme appli
