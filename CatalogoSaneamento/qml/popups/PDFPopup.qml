import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import xyz.aahome89.base 1.0

Popup {
    id: popup
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    property int questionIdNode

    ColumnLayout {
        anchors.fill: parent

        Image {
            id: image1
            anchors.left: parent.left
            anchors.right: parent.right
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            source: "file:///" + applicationDirPath + "/resources/pdf_icon.png"
            fillMode: Image.PreserveAspectFit

        }

        Text {
            id: text1
            anchors.left: parent.left
            anchors.right: parent.right
            text: qsTr("Estes são os catálogos correspondentes:")
        }

        ListView {

            id: pdfListView
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: text1.bottom
            anchors.bottom: text2.top
            Layout.fillHeight: true
            Layout.fillWidth: true

            model: pdfListModelId

            delegate: Text {
                width: ListView.view.width

                text: "<a href='/resources/" + pdfPath + "'>" + pdfName + "</a>"

                onLinkActivated: {
                    Qt.openUrlExternally(applicationDirPath + link)
                    console.log("file:///" + applicationDirPath + "/../resources/" + pdfPath);
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.NoButton // we don't want to eat clicks on the Text
                    cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
                }
            }
        }

        Rectangle {
            Layout.fillHeight: true
        }

        Text {
            id: text2
            anchors.left: parent.left
            anchors.right: parent.right
            text: qsTr("OBS: Necessário possuir Leitor de PDF Instalado.")
        }
    }

    PdfListModel {
        id: pdfListModelId
    }

    function refresh() {
        pdfListModelId.refreshModel(questionIdNode);
        popup.open();
    }
}
