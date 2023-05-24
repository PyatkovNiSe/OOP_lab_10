#include "galleryModel.h"

ImageViewerModel::ImageViewerModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant ImageViewerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int ImageViewerModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !m_imageViewer)
        return 0;
    return m_imageViewer->images().size();
}

QVariant ImageViewerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_imageViewer)
        return QVariant();

    const Image img = m_imageViewer->images().at(index.row());
    switch (role) {
    case FileNameRole:
        return QVariant(img.fileName);
        break;
    case FullPathRole:
        return QVariant(img.fullPath);
        break;
    }

    return QVariant();
}

ImageViewer *ImageViewerModel::imageViewer() const
{
    return m_imageViewer;
}

void ImageViewerModel::setImageViewer(ImageViewer *newImageViewer)
{
    beginResetModel();
    if(m_imageViewer)
        m_imageViewer->disconnect(this);

    m_imageViewer = newImageViewer;
    if(m_imageViewer){
        connect(m_imageViewer, &ImageViewer::preImagesListUpdated, this,
                                      [=](){
            const int index = m_imageViewer->images().size();
            beginInsertRows(QModelIndex(), index, index);
        });

        connect(m_imageViewer, &ImageViewer::imagesListUpdated, this,
                                      [=](){
            endInsertRows();
        });
    }

    emit imageViewerUpdate();

    endResetModel();
}

QHash<int, QByteArray> ImageViewerModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[FullPathRole] = "fullPath";
    names[FileNameRole] = "fileName";
    return names;
}
