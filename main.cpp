#include "galleryModel.h"
#include "saver.h"

#include <QFile>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTextStream>


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);


    qmlRegisterType<ImageViewerModel>("ImageViewer", 1, 0, "ImageViewerModel");
    qmlRegisterUncreatableType<ImageViewer>("ImageViewer", 1, 0, "ImageViewer",
                                            QString("Image viewer should not be created in QML"));


    QFile imagesList("recent_files.cache");
    std::vector<Image> recentFiles;
    if(imagesList.open(QIODevice::ReadOnly)){
        while (!imagesList.atEnd()) {
            QTextStream stream(&imagesList);

            QByteArray line = imagesList.readLine();
            line = line.trimmed();
            qDebug() << "readed: " << QString(line);

            recentFiles.push_back(Image(QString(line)));
        }
    }

    ImageViewer imageViewer(recentFiles);
    Saver saver("recent_files.cache");
    QObject::connect(&imageViewer,
                     &ImageViewer::imagesListUpdated,
                     &saver,
                     [&](Image image){
        saver.saveToFile(image.fullPath);
    });


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("mimageViewer"), &imageViewer);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
