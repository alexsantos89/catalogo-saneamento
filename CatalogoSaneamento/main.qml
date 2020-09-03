import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Catálogo Saneamento")

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter

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

    Component.onCompleted: {
        flag_pt.state = "clicked";
    }

    function highlightFlag(lang)
    {
        switch (lang)
        {
        case "en":
            flag_en.state = "clicked";
            flag_pt.state = "default";
            break;
        case "pt":
            flag_pt.state = "clicked";
            flag_en.state = "default";
            break;
        }
    }

}
