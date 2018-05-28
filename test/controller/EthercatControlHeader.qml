import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    height: 50
    color: 'lightblue'
    property int border_padding: 3

    property string name_of_device
    property string slave_id_numbers
    property string ethercat_slave_state

    Text {
        id: txt_info
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.margins: border_padding
        text: name_of_device
    }

    Button {
        id: btn_change_state
        anchors.verticalCenter: parent.verticalCenter
        text: "Change State"
        anchors.right: parent.right
        onClicked: ecat_state_control_popup.open()

        Popup {
            id: ecat_state_control_popup
            width: 200
            height: 180
            focus: true
            modal: true
            x: -width
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

            EthercatStateDiagram {
                id: diagram
                anchors.fill: parent
                slave_state: ethercat_slave_state
            }
        }
    }

    Text {
        id: txt_slave_id_numbers
        anchors.right: btn_change_state.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: border_padding
        text: ethercat_slave_state
    }


}
