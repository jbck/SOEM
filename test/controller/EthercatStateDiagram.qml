import QtQuick 2.10
import QtQuick.Controls 2.3

Item {
    property int button_spacing: 3
    property int button_height: 30
    property int slave_id: 1
    property string slave_state: "NONE"

    Timer {
        interval: 200
        running: true
        repeat: true
        onTriggered: slaveinfo.recordDeviceState(1)
    }

    Button {
        id: btn_state_init
        height: button_height
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        text: 'INIT'
        font.bold: true
        onClicked: slaveinfo.setDeviceState(slave_id, 0x01)
        background: Rectangle {
            color: (slave_state == parent.text) ? 'pink' : 'lightgray'
        }
    }

    Button {
        id: btn_state_boot
        width: 80; height: button_height
        anchors.top: btn_state_init.bottom
        anchors.topMargin: button_spacing
        anchors.left: parent.left
        text: 'BOOT'
        font.bold: true
        onClicked: slaveinfo.setDeviceState(slave_id, 0x03)
        background: Rectangle {
            color: (slave_state == parent.text) ? 'lightblue' : 'lightgray'
        }
    }

    Button {
        id: btn_state_preop
        width: 90; height: button_height
        anchors.top: btn_state_init.bottom
        anchors.topMargin: button_spacing
        anchors.right: parent.right
        text: 'PREOP'
        font.bold: true
        onClicked: slaveinfo.setDeviceState(slave_id, 0x02)
        background: Rectangle {
            color: (slave_state == parent.text) ? 'lightyellow' : 'lightgray'
        }
    }

    Button {
        id: btn_state_safeop
        width: 90; height: button_height
        anchors.top: btn_state_preop.bottom
        anchors.topMargin: button_spacing
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: btn_state_preop.left
        anchors.leftMargin: -20
        text: 'SAFEOP'
        font.bold: true
        onClicked: slaveinfo.setDeviceState(slave_id, 0x04)
        background: Rectangle {
            color: (slave_state == parent.text) ? 'lightyellow' : 'lightgray'
        }
    }

    Button {
        id: btn_state_op
        height: button_height
        anchors.top: btn_state_safeop.bottom
        anchors.topMargin: button_spacing
        anchors.right: parent.right
        anchors.left: btn_state_boot.right
        anchors.leftMargin: button_spacing
        text: 'OP'
        font.bold: true
        onClicked: slaveinfo.setDeviceState(slave_id, 0x08)
        background: Rectangle {
            color: (slave_state == parent.text) ? 'lightgreen' : 'lightgray'
        }
    }
}
