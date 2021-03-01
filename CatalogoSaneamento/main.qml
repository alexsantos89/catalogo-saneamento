import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import xyz.aahome89.base 1.0
import "qml/popups"
import QtQuick.Dialogs 1.2

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Catálogo Saneamento")

    property QuestionNode lastNode


    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            id: language
            anchors.horizontalCenter: parent.horizontalCenter
            //Layout.fillWidth: true
            //Layout.fillHeight: true

            Button {
                text: "EN"
                Layout.preferredWidth: 76
                Layout.preferredHeight: 53

                background: Rectangle {
                    id: flag_en
                    color: "grey"
                    radius: 5

                    states: [
                        State {
                            name: "default"
                            PropertyChanges {
                                target: flag_en;
                                color: "grey"
                            }
                        },
                        State {
                            name: "clicked"
                            PropertyChanges {
                                target: flag_en;
                                color: "#60BD51"
                            }
                        }
                    ]
                }

                onClicked: {
                    onClicked: trans.selectLanguage("en");
                    highlightFlag("en");
                }
            }

            Button {
                text: "PT"
                Layout.preferredWidth: 76
                Layout.preferredHeight: 53

                background: Rectangle {
                    id: flag_pt
                    color: "grey"
                    radius: 5

                    states: [
                        State {
                            name: "default"
                            PropertyChanges {
                                target: flag_pt;
                                color: "grey"
                            }
                        },
                        State {
                            name: "clicked"
                            PropertyChanges {
                                target: flag_pt;
                                color: "#60BD51"
                            }
                        }
                    ]
                }

                onClicked: {
                    onClicked: trans.selectLanguage("pt");
                    highlightFlag("pt");
                }
            }
        }

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            anchors.top: language.bottom
            anchors.bottom: pane.top
            //Layout.margins: pane.leftPadding + messageField.leftPadding
            Layout.margins: 40
            displayMarginBeginning: 40
            displayMarginEnd: 40
            clip: true
            verticalLayoutDirection: ListView.TopToBottom
            spacing: 12
            model: questionModel
            onCountChanged: function () {
                listView.positionViewAtEnd();
                listView.currentIndex = listView.count - 1;
            }
            delegate: Column {
                anchors.right: sentByMe ? parent.right : undefined
                spacing: 6

                readonly property bool sentByMe: index % 2 == 1

                Row {
                    id: messageRow
                    spacing: 6
                    anchors.right: sentByMe ? parent.right : undefined

                    Rectangle {
                        id: avatar
                        width: height
                        height: parent.height
                        color: "grey"
                        //visible: !sentByMe
                        visible: false
                    }

                    Rectangle {
                        width: Math.min(messageText.implicitWidth + 24,
                            listView.width - (!sentByMe ? avatar.width + messageRow.spacing : 0))
                        height: messageText.implicitHeight + 24
                        color: sentByMe ? "lightgrey" : "steelblue"

                        Label {
                            id: messageText
                            text: model.questionText
                            color: sentByMe ? "black" : "white"
                            anchors.fill: parent
                            anchors.margins: 12
                            wrapMode: Label.Wrap
                        }
                    }
                }

            }

            ScrollBar.vertical: ScrollBar {}
        }

        Pane {
            id: pane
            Layout.fillWidth: true

            RowLayout {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.leftMargin: 5


                Button {
                    id: resetButton
                    text: qsTr("Reset")
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    //enabled: messageField.length > 0
                    onClicked: function () {
                        questionModel.refreshModel();
                        lastNode = rootNode.get_rootNode();
                        questionModel.appendQuestion(lastNode);
                        noButton.enabled = true;
                        yesButton.enabled = true;
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                }

                Button {
                    id: yesButton
                    text: qsTr("Sim")
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    //enabled: messageField.length > 0
                    onClicked: function () {
                        lastNode = lastNode.p_left;
                        var newQuestionNode = createQuestionNode();
                        newQuestionNode.set_text("Sim","Yes");
                        questionModel.appendQuestion(newQuestionNode);
                        questionModel.appendQuestion(lastNode);
                        if (lastNode.p_left == undefined)
                            showPopup()
                    }
                }

                Button {
                    id: noButton
                    text: qsTr("Não")
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    //enabled: messageField.length > 0
                    onClicked: function () {
                        lastNode = lastNode.p_right
                        var newQuestionNode = createQuestionNode();
                        newQuestionNode.set_text("Não","No");
                        questionModel.appendQuestion(newQuestionNode);
                        questionModel.appendQuestion(lastNode);
                        if (lastNode.p_right == undefined)
                            showPopup()
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        flag_pt.state = "clicked";
        rootNode.start_model();
        lastNode = rootNode.get_rootNode();
        questionModel.appendQuestion(lastNode);
    }

    function highlightFlag(lang)
    {
        switch (lang)
        {
        case "en":
            flag_en.state = "clicked";
            flag_pt.state = "default";
            rootNode.set_language(QuestionNode.English);
            questionModel.refreshLanguage();
            break;
        case "pt":
            flag_pt.state = "clicked";
            flag_en.state = "default";
            rootNode.set_language(QuestionNode.Portuguese);
            questionModel.refreshLanguage();
            break;
        }
    }

    function createQuestionNode() {
        var component = Qt.createComponent("qrc:/qml/principais/MyQuestionNode.qml");
        var question = component.createObject();

        if (question === null) {
            // Error Handling
            console.log("Error creating object");
        }

        return question;
    }

    QuestionNode {
        id: rootNode
    }

    QuestionListModel{
        id: questionModel
    }

    PDFPopup {
        id: popup
        x: Math.round((mainWindow.width - width) / 2)
        y: Math.round((mainWindow.height - height) / 2)
    }

    function showPopup() {
        noButton.enabled = false;
        yesButton.enabled = false;
        popup.questionIdNode = lastNode.p_id;
        popup.refresh();
    }

}
