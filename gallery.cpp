#include "gallery.h"
#include "qdebug.h"

ImageViewer::ImageViewer(QObject *parent)
    : QObject{parent}
{

}

ImageViewer::ImageViewer(std::vector<Image> images, QObject *parent)
  : QObject{parent}, m_images(images)
{

}

QVector<Image> ImageViewer::images() const
{
    return QVector<Image>(m_images.begin(), m_images.end());
}

void ImageViewer::openImage(int index)
{
    auto& img = m_images.at(index);

    if(currentImage != &img){
        currentImage = &img;
        emit postImageUpdated(currentImage->fullPath);
    }
}

void ImageViewer::openNewImage(QString path)
{
    Image img(path);
    emit preImagesListUpdated();
    qDebug() << "Image openned";

    m_images.push_back(img);
    emit imagesListUpdated(img);

    // image setter
    emit imageUpdated();
    currentImage = &m_images.back();
    emit postImageUpdated(currentImage->fullPath);
}
