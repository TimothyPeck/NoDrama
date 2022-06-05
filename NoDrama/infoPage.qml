import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import com.myself 1.0

ApplicationWindow {
    id: loginWindow
    width: 640
    height: 640
    visible: true
    title: qsTr("Hello World")
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

            Image {
                id: logo
                source: ":/images/images/NoDramaTranparent.PNG"
            }

            RowLayout{
                Text {
                    id: userActiveText
                    text: qsTr("Current user: ")
                    font.pointSize: 25
                    color: 'white'
                }

                Text {
                    id: userActive
                    text: currentUser.getUsername()
                    font.pointSize: 20
                    color: 'white'
                }

                onParentChanged: {
                    //console.log(loggedUser.username)
                }
            }

            Text {
                id: infoHeader
                text: qsTr("NoDrama Team")
                font.pointSize: 50
                color: 'white'
            }

            Text {
                id: memberOne
                text: qsTr("Michel Jeanne")
                font.pointSize: 25
                color: 'white'
            }

            Text {
                id: memberTwo
                text: qsTr("Peck Timothy")
                font.pointSize: 25
                color: 'white'
            }

            Text {
                id: memberThree
                text: qsTr("Tan Dorian")
                font.pointSize: 25
                color: 'white'
            }
        }
    }
}
