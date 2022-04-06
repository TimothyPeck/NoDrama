import QtQuick 2.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    color: "#232323"

    TextField {
        id: username
        Layout.minimumWidth: 100
        Layout.preferredWidth: 300
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        Layout.alignment: Qt.AlignHCenter
        placeholderText: qsTr("Username")
        background: Rectangle {
                    radius: 10
                    color: "#c9f1fd"
                }
}
