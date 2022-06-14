import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import com.myself 1.0

ApplicationWindow {
    id: createAccount
    property alias createAccountId : createAccount
    width: 360
    height: 640
    visible: true
    title: qsTr("NoDrama - Create account")
    color: "#232323"

    User{
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
                id: email
                Layout.minimumWidth: 100
                Layout.preferredWidth: 300
                horizontalAlignment: TextInput.AlignHCenter
                verticalAlignment: TextInput.AlignVCenter
                Layout.alignment: Qt.AlignHCenter
                placeholderText: qsTr("EMail")
                background: Rectangle {
                            radius: 10
                            color: "#c9f1fd"
                        }
            }

            TextField {
                id:password
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

            TextField {
                id:passwordVerif
                echoMode:TextInput.Password
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
                    if(username.text != "" && email.text !="" && password.text!="" && passwordVerif.text!="" && password.text==passwordVerif.text){
                        currentUser.constructor(user.createUser(username.text, password.text, email.text))
                        if(currentUser.getId() > -1){
                            createAccount.close();

                        } else {
                            console.log("error");
                        }
                    }
                }
            }
        }
    }
}
