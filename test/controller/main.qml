import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.0


import com.synapticon.somanet.ethercat.slaveinfo 1.0

Window {
    visible: true
    width: 400
    height: 250
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

    Rectangle {
        id: txt_info
        height: 30
        anchors.top: network_interface.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        color: 'gray'
        Text {
            text: slaveinfo.name
            color: 'white'
            anchors.left: parent.left
            anchors.leftMargin: border_padding
            anchors.verticalCenter: parent.verticalCenter
        }
        Text {
            text: slaveinfo.state
            color: 'white'
            font.bold: true
            anchors.right: parent.right
            anchors.rightMargin: border_padding
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    EthercatStateDiagram {
        id: diagram
        slave_state: slaveinfo.state
        anchors.top: txt_info.bottom
        anchors.left: txt_info.left
        anchors.bottom: parent.bottom
        anchors.right: txt_info.right
        anchors.margins: border_padding
    }
}
