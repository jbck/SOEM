import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.0


import com.synapticon.somanet.ethercat.slaveinfo 1.0

Window {
    visible: true
    width: 640
    height: 480
    color: 'whitesmoke'
    title: qsTr("OBLAC Mini")

    property int border_padding: 3

    SlaveInfo {
        id: slaveinfo
    }

    Rectangle {
        id: network_interface
        height: 30
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        ComboBox {
            id: network_names
            model: slaveinfo.networkNames
            onCurrentTextChanged: slaveinfo.connect(network_names.currentText)
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: border_padding
        }

        Button {
            id: do_something
            text: "do something"
            onClicked: slaveinfo.sdoRead(1,1)
            anchors.left: network_names.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: border_padding
        }

        Text {
            id: txt_slave_number
            text: slaveinfo.title
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: border_padding
        }
    }

    EthercatControlHeader {
        id: ethercat_control_header
        name_of_device: slaveinfo.name
        slave_id_numbers: slaveinfo.title
        ethercat_slave_state: slaveinfo.state

        anchors.top: network_interface.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }

}
