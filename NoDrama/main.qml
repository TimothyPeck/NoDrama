import QtQuick
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import com.myself 1.0

ApplicationWindow {
    id: loginWindow
    property alias loginWindowId : loginWindow
    width: 360
    height: 640
    visible: true
    title: qsTr("NoDrama Login")
    color: "#232323"

    User {
        id: user
    }

    RowLayout{
        id: rowLayout
        anchors.fill: parent
        Layout.alignment: Qt.AlignCenter

        ColumnLayout {

            Layout.alignment: Qt.AlignCenter
            id: inputs
            spacing: 6

            Rectangle{
                Layout.preferredHeight: 200
                Layout.minimumWidth: 100
                Layout.preferredWidth: 300

                color: '#232323'
                Image {
                    id: logo_
                    width: 300
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/images/logo"
                }
            }

            Rectangle{
                height: 75
            }

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

            TextField {
                id: password
                echoMode: TextInput.Password
                Layout.minimumWidth: 100
                Layout.preferredWidth: 300
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                Layout.alignment: Qt.AlignHCenter
                placeholderText: qsTr("Password")
                background: Rectangle {
                    radius: 10
                    color: "#c9f1fd"
                }
            }

            Button {
                 id: createAccountButton
                 Layout.minimumWidth: 150
                 Layout.preferredWidth: 150
                 Layout.minimumHeight: 45
                 Layout.alignment: Qt.AlignHCenter
                 text: qsTr("Create Account")
                 background: Rectangle {
                     radius: 10
                     color: createAccountButton.down?'#b2a7f9':'#a8c6fa'
                 }
                 onClicked: {
                     var component = Qt.createComponent("./createAccount.qml")
                     var window = component.createObject(loginWindow)
                     window.show();
                 }
             }


           Rectangle{
               height: 80
           }

            Button {
                id: loginButton
                Layout.minimumWidth: 100
                Layout.preferredWidth: 200
                Layout.minimumHeight: 60
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Login")
                flat: true
                background: Rectangle {
                    radius: 10
                    color: loginButton.down?'#b2a7f9':'#a8c6fa'
                }
                onClicked: {
                    var id = user.testLoginUsername(username.text, password.text);
                    if(id > -1){
                        currentUser.constructor(user.getUserById(id));
                        var component = Qt.createComponent("./viewParties.qml")
                        var window = component.createObject(loginWindow)
                        window.show();
                    }else {
                        console.log("error");
                    }
                }
            }
        }
    }
}

