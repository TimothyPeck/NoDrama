import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import com.myself 1.0

ApplicationWindow {
    id: friendsPage
    width: 360
    height: 640
    visible: true
    title: qsTr("Friends")
    color: "#232323"

    onClosing: {
        var component = Qt.createComponent("./viewParties.qml")
        var window = component.createObject(friendsPage)
        window.show()
    }

    User {
        id: user
    }

    ListModel {
        id: usersListModel
        Component.onCompleted: {
            updateList();
        }
    }
    function createListElement(n, a){
        return {
            name: n,
            affi: a
        }
    }
    function justOneElement(n, a){
        if(n !== null){
            a = (a === null ? "" : a);
            //console.log(n);
            //console.log(a);
            usersListModel.clear();
            usersListModel.append(createListElement(n,a));
        }
    }
    function updateList(){
        console.log("update")
        usersListModel.clear();
        var friends = currentUser.getFriendsForDisplay();
        lineEdit.text = "";
        for(var i = 0; i < friends.length; i++)
        {
            for(var friend in friends[i])
            {
                console.log(friend + " : " + friends[i][friend]);
                usersListModel.append(createListElement(friend, friends[i][friend].toString()));
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
                placeholderText: qsTr("Search user or friend...")
                background: Item {}
                font.pixelSize: 14
                font.bold: false
                onEditingFinished: {
                    var user_ = user.getUserByUsername(lineEdit.text);
                    //console.log(user_.getUsername());
                    if(user_ !== null)
                    {
                        justOneElement(user_.getUsername(), null);
                    }
                }
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
                model: usersListModel
                delegate:
                    Item {
                    id: wrapper
                    width: searchBar.width;
                    height: 40

                    Row{
                        Label {
                            id: labelName
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
                                displayText: affi
                                model: ['', 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
                                onActivated: {
                                    //console.log("label name : " + labelName.text)
                                    //console.log("value : " + currentValue)

                                    currentUser.addFriendOrUpdateAffinity(labelName.text, currentValue);
                                    console.log("now update");
                                    updateList();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

