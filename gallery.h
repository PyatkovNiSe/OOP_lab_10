#ifndef GALLERY_H
#define GALLERY_H

#include "qdebug.h"
#include <QObject>
#include <Qstring>

struct Image
{
    QString fileName;
    QString fullPath;

    Image(){}
    Image(QString fullPath) {
        this->fullPath = fullPath;
        auto result = fullPath.lastIndexOf('/', 0);
        auto localSplit = fullPath.split('/');

        qDebug() << "Image: " << fullPath;
        auto substr = localSplit.last();

        qDebug() << "substr: " << substr;
        this -> fileName = substr;
    }
    Image(QString fullPath,QString fileName) {
        this->fullPath = fullPath;
        this->fileName = fileName;
    }
};


class ImageViewer : public QObject
{
    Q_OBJECT
public:
    explicit ImageViewer(QObject *parent = nullptr);
    ImageViewer(std::vector<Image> images,QObject *parent = nullptr);

    Image* currentImage;

    QVector<Image> images() const;

signals:
    void preImagesListUpdated();
    void imageUpdated();
    void postImageUpdated(QString path);
    void imagesListUpdated(Image newImage);

public slots:
    void openImage(int index);
    void openNewImage(QString path);

private:
    std::vector<Image> m_images;
};

#endif
