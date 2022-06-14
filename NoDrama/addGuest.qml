import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import com.myself 1.0
//import "createParty.qml"

ApplicationWindow {
    width: 360
    height: 640
    visible: true
    title: qsTr("Add guests")
    color: "#232323"
    onClosing: {
        createPartyId.updateList();
    }

    User {
        id: user
    }

    ListModel {
        id: friendsListModel
        Component.onCompleted: {
            updateList();
        }
    }


    function createListElement(n,a)
    {
        return {
            name : n,
            isAdded : a
        }
    }

    function updateList()
    {
        friendsListModel.clear();
        lineEdit.text = "";

        var friends = currentUser.getFriendsForDisplay();

        for(var i = 0; i < friends.length; i++)
        {
            for(var friend in friends[i])
            {
                var isInList = false;
                if(currentParty.isFriendInGuest(friend))
                {
                    friendsListModel.append(createListElement(friend, "-"));
                } else
                {
                    friendsListModel.append(createListElement(friend, "+"));
                }
            }
        }
    }

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
            contentWidth: 360
            contentHeight: 610
            Layout.alignment: Qt.AlignHCenter

            ListView{
                anchors.fill: parent
                focus: true
                model: friendsListModel
                delegate:
                    Item {
                    id: wrapper
                    width: searchBar.width;
                    height: 40

                    Row{
                        Label {
                            id: friendName
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
                            text: isAdded
                            height: 40
                            width: 40
                            onClicked: {
                                currentParty.addOrRemoveGuest(name);
                                updateList();
                            }
                        }
                    }
                }
            }
        }
    }
}

