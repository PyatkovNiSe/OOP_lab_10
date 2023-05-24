#ifndef GALLERYMODEL_H
#define GALLERYMODEL_H

#include <QAbstractListModel>
#include "gallery.h"

class ImageViewerModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ImageViewer *imageViewer READ imageViewer WRITE setImageViewer NOTIFY imageViewerUpdate )
public:
    enum{
        FileNameRole = Qt::UserRole,
        FullPathRole
    };

    explicit ImageViewerModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    ImageViewer *imageViewer() const;
    void setImageViewer(ImageViewer *newImageViewer);

    virtual QHash<int, QByteArray> roleNames() const override;

signals:
    void imageViewerUpdate();

private:
    ImageViewer *m_imageViewer = nullptr;

};

#endif
