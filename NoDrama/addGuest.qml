import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 360
    height: 640
    visible: true
    title: qsTr("Add guests")
    color: "#232323"

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        //Layout.alignment: Qt.AlignHCenter
        //spacing: 5

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
                placeholderText: qsTr("Search...")
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
                                width:40 ;
                                height:40;
                                color: "lightblue" ;
                                border.color: "lightsteelblue";
                                border.width:0.5
                            }
                            text: "+"
                            height: 40
                            width: 40
                        }
                    }

                }
            }
        }
    }
}


