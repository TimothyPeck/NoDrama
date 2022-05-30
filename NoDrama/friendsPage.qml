import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 360
    height: 640
    visible: true
    title: qsTr("Friends")
    color: "#232323"

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent

        // Search bar
        Rectangle {
            id: searchBar
            width: 360
            height: 30
            color: "#ffffff"
            radius: 6
            border.color: "#cccccc"
            property alias placeholderText: lineEdit.placeholderText
            property alias text: lineEdit.text
            Layout.alignment: Qt.AlignCenter

            TextField {
                id: lineEdit
                placeholderText: qsTr("Search user or friend...")
                background: Item {}
                font.pixelSize: 14
                font.bold: false
            }
        }

        // Scroll view of the list of predetermined guests
        ScrollView
        {
            width: 360
            height: 610
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            //anchors.left: searchBar.left
            //anchors.top: searchBar.bottom
            contentWidth: 360
            contentHeight: 610
            Layout.alignment: Qt.AlignHCenter

            ListView{
                anchors.fill: parent
                focus: true
                model: UsersList { }
                delegate:
                    Item {
                    id: wrapper
                    width: searchBar.width;
                    height: 40

                    Row{
                        Label {
                            leftPadding: 15
                            verticalAlignment: Text.AlignVCenter
                            text: name;
                            background: Rectangle {
                                color: "white";
                                border.color: "#cccccc";
                                border.width:0.5
                            }
                            width: searchBar.width-40
                            height: 40
                        }

                        Button {
                            background: Rectangle{
                                width: 40;
                                height: 40;
                                color: "lightblue" ;
                                border.color: "lightsteelblue";
                                border.width: 0.5
                            }

                            ComboBox {
                                id: affinity
                                width: 40
                                height: 40
                                model: 11
                                //Layout.alignment: Qt.AlignCenter
                                delegate: ItemDelegate {
                                    text: index
                                }
                            }
                        }

                    }

                }
            }
        }
    }
}

