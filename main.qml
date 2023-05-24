import QtQuick 2.15
import QtQuick.Window 2.15

import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts 1.15
import Qt.labs.platform as Platform

import ImageViewer 1.0



ApplicationWindow  {
    visible: true
    width: 640
    height: 480
    title: qsTr("Image viewer")


    Image {
        id: i_viewedImage
        anchors.fill: parent
        asynchronous: true
        fillMode: Image.PreserveAspectFit
    }


    Component.onCompleted: {
        mimageViewer.postImageUpdated.connect(onImageUpdated);
    }

    function onImageUpdated(value){
        i_viewedImage.source = value;
    }

    menuBar: MenuBar {
        Menu{
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open...")
                icon.name: "document-open"
                onTriggered: fd_imageOpenDialog.open()
            }
            MenuSeparator{}
            Menu{
                id: recentFiles
                title: qsTr("&Recent files")
                enabled : i_recentFilesMenuInstantiator.count > 0

                Instantiator{
                    id: i_recentFilesMenuInstantiator

                    model: ImageViewerModel{
                        imageViewer: mimageViewer
                    }

                    delegate: MenuItem{
                        text: model.fileName
                        onTriggered: mimageViewer.openImage(index)
                    }

                    onObjectAdded: recentFiles.insertItem(index, object)
                    onObjectRemoved: recentFilesSubMenu.removeItem(object)
                }
            }
        }
    }


    FileDialog{
        id: fd_imageOpenDialog
        title: "Select image file"
        currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        nameFilters: [
            "Image files (*.png *.jpeg *.jpg)",
        ]
        onAccepted: mimageViewer.openNewImage(currentFile)
    }
}

