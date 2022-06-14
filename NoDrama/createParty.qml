
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import com.myself 1.0

ApplicationWindow {
    property alias createPartyId : createPartyWindow
    id: createPartyWindow
    width: 360
    height: 640
    visible: true
    title: qsTr("Create party")
    color: "#232323"

    ListModel {
        id: guestsListModel
        Component.onCompleted: {
            updateList();
        }

    }
    function createListElement(n)
    {
        return {
            name : n
        }
    }

    function updateList()
    {
        guestsListModel.clear();

        var guests = currentParty.getGuestsForDisplay();

        for(var i = 0; i < guests.length; i++)
        {
            guestsListModel.append(createListElement(guests[i]));
        }
    }

    ColumnLayout{
        spacing: 8
        anchors.topMargin: 30
        anchors.bottomMargin: 50
        anchors.fill: parent
        Layout.alignment: Qt.AlignHCenter

        // Party name
        TextField {
            id: partyname
            Layout.preferredWidth: 280
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
            Layout.alignment: Qt.AlignHCenter
            Label {
                anchors.leftMargin: 40
                text: "Max number of people"
                color: "#c9f1fd"
            }
            SpinBox {
                Layout.alignment: Qt.AlignRight
                width: 20
                id: nbpeople
                from: 1
            }
        }

        // Minimum affinity
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            Label {
                text: "Minimum affinity"
                color: "#c9f1fd"
            }
            ComboBox {
                id: minaffinity
                width: 20
                model: 11
                delegate: ItemDelegate {
                    text: index
                }
            }
        }

        // Date et heure
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            TextField {
                id: date
                Layout.preferredWidth: 210
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                Layout.alignment: Qt.AlignHCenter
                placeholderText: qsTr("Date et heure")
                background: Rectangle {
                    radius: 10
                    color: "#c9f1fd"
                }
            }
            TextField {
                id: time
                Layout.preferredWidth: 70
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                Layout.alignment: Qt.AlignHCenter
                placeholderText: qsTr("Time")
                background: Rectangle {
                    radius: 10
                    color: "#c9f1fd"
                }
                onEditingFinished:
                {
                    currentParty.setTime(time.text);
                }
            }
        }

        // Location
        TextField {
            id: location
            Layout.preferredWidth: 280
            horizontalAlignment: TextInput.AlignHCenter
            verticalAlignment: TextInput.AlignVCenter
            Layout.alignment: Qt.AlignHCenter
            placeholderText: qsTr("Location")
            background: Rectangle {
                radius: 10
                color: "#c9f1fd"
            }
        }

        Button {
            id: addguest
            Layout.preferredWidth: 280
            Layout.minimumHeight: 30
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Add guest")
            background: Rectangle {
                radius: 10
                color: addguest.down?'#b2a7f9':'#a8c6fa'
            }
            onClicked: {
                var component=Qt.createComponent("./addGuest.qml");
                var window = component.createObject(viewParties);
                createPartyWindow.hide();
                window.show();
            }
        }

        // Scroll view of the list of predetermined guests
        ScrollView
        {
            id: guestsScrollView
            anchors.top: addguest.bottom
            anchors.topMargin: 3
            width: 280
            height: 300
            contentWidth: 280
            contentHeight: 300
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            Layout.alignment: Qt.AlignHCenter

            ListView {
                anchors.fill: parent
                focus: true
                model: guestsListModel
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
                                color: wrapper.ListView.isCurrentItem ? "lightsteelblue" : "white"
                                border.color: "#cccccc";
                                border.width:0.5
                            }
                            width: 240
                            height: 40
                        }

                        Button {
                            background: Rectangle{
                                color: wrapper.ListView.isCurrentItem ? "lightsteelblue" : "lightblue"
                                border.color: "lightsteelblue"
                                border.width:0.5
                            }
                            text: qsTr("-")
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

        // Create party button
        Button {
            id: createParty
            Layout.preferredWidth: 280
            Layout.minimumHeight: 30
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Calculate")
            background: Rectangle {
                radius: 10
                color: createParty.down?'#b2a7f9':'#a8c6fa'
            }
            onClicked: {
                currentParty.setHost(currentUser);
                currentParty.setName(partyname.text);
                currentParty.setMaxP(nbpeople.value);
                currentParty.setMinAffi(minaffinity.currentValue);
                currentParty.setDate(date.text);
                currentParty.setTime(time.text);
                currentParty.setLoc(location.text);

                currentParty.determineGuests();
                updateList();
            }
        }

        Button
        {
            id: validateParty
            Layout.preferredWidth: 280
            Layout.minimumHeight: 30
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Validate party")
            background: Rectangle {
                radius: 10
                color: createParty.down?'#b2a7f9':'#a8c6fa'
            }
            onClicked: {
                currentParty.setHost(currentUser);
                currentParty.setName(partyname.text);
                currentParty.setMaxP(nbpeople.value);
                currentParty.setMinAffi(minaffinity.currentValue);
                currentParty.setDate(date.text);
                currentParty.setTime(time.text);
                currentParty.setLoc(location.text);

                currentParty.createParty();
                viewPartiesId.updatePartiesList();
                createPartyWindow.close();
            }
        }
    }
}




