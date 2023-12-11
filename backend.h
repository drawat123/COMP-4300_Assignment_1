#ifndef BACKEND_H
#define BACKEND_H

#include <QMap>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickWindow>
#include <QString>
#include <QTimer>
#include <QVariant>
#include <QVariantmap>
#include <QtDebug>
#include <fstream>
#include <vector>

enum class CollisionDirection { none, left, right, top, bottom };

class Backend : public QQuickItem
{
    Q_OBJECT
public:
    explicit Backend(QQuickItem *parent = nullptr, QQuickItem *root = nullptr);

public slots:
    void readFile(QString path);

signals:
    void entitySet(QString entityName, QVariantList entityProperties);

private slots:
    void moveShapes();

private:
    std::vector<QQuickItem *> m_ShapeObjects;
    QTimer m_Timer;
    QQuickItem *m_Root;
};

#endif // BACKEND_H
