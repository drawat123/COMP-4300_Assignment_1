#ifndef BACKEND_H
#define BACKEND_H

#include <QMap>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantmap>
#include <QtDebug>
#include <fstream>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

public slots:
    void readFile(QString path);

signals:
    void entitySet(QString entityName, QVariantList entityProperties);
    void startMoving();
};

#endif // BACKEND_H
