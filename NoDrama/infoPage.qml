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
    title: qsTr("Information page")
    color: "#232323"

    onClosing: {
    }

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

            RowLayout{
                Rectangle{
                    Layout.preferredHeight: 100
                    Layout.minimumWidth: 100
                    Layout.preferredWidth: 100

                    color: "#232323"

                    Image {
                        id: logo_
                        width: 100
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/images/logo"
                    }
                }
                Rectangle{
                    Layout.preferredHeight: 100
                    Layout.minimumWidth: 100
                    Layout.preferredWidth: 200

                    color: "#232323"

                    Image {
                        id: logo_arc
                        width: 200
                        fillMode: Image.PreserveAspectFit
                        source: "qrc:/images/logo_arc"
                    }
                }
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
