import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import com.myself 1.0

ApplicationWindow {
    id: viewParties
    width: 360
    height: 640
    visible: true
    title: qsTr("My parties")
    color: "#232323"

    Party{
        id: party
    }

    User{
        id: user
    }

    ListModel {

        id: partyModel

        function createListParty(part){
            console.log("Current party id: " + part)
            currentParty.constructor(party.getPartyById(part))
            console.log(currentParty.getHost())
            if(currentParty.getHost() !== undefined){
                console.log("Current party name: " + currentParty.getPartyName())
                //tmpUser = currentParty.getHost()
                console.log(currentParty.getHost())
                return{
                    name: currentParty.getPartyName(),
                    date: currentParty.getPartyDate(),
                    time: currentParty.getPartyDate(),
                    organiser: tmpUser.getUsername(),
                    place: currentParty.getPartyLocation()
                };
            }else{
                return{
                    name: "Error getting parties",
                    date: "",
                    time: "",
                    organiser: "",
                    place: ""
                }
            }
        }

        Component.onCompleted: {
            var parties = party.getPartyIdsForUser(currentUser)
            for(let i=0; i<parties.length; i++){
                append(createListParty(parties[i]))
            }
        }
    }

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
                var component=Qt.createComponent("./createParty.qml");
                var window = component.createObject(viewParties);
                window.show();
            }
        }

        Button{
            id: viewInfo
            Layout.minimumWidth: 25
            Layout.preferredWidth: 25
            Layout.minimumHeight: 25
            Layout.alignment: Qt.AlignRight
            text: qsTr("?")

            background: Rectangle {
                radius: 10
                color: viewInfo.down?'#b2a7f9':'#a8c6fa'
            }

            onClicked: {
                var component=Qt.createComponent("./infoPage.qml")
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
                model: partyModel
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
