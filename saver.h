#ifndef SAVER_H
#define SAVER_H

#include <QFile>
#include <QObject>
#include <QTextStream>

class Saver : public QObject
{
    Q_OBJECT
public:
    explicit Saver(QObject *parent = nullptr)
        :QObject(parent){
    }

    Saver(QString fileToSave, QObject *parent = nullptr)
        :m_fileName(fileToSave), QObject(parent){

    }

public slots:
    void saveToFile(QString data){
        QFile file(m_fileName);
        if(file.open(QIODevice::Append)){
            QTextStream stream(&file);
            stream << data << Qt::endl;
        }
        file.close();
    }
private:
    QString m_fileName = "file.txt";
};

#endif // SAVER_H
