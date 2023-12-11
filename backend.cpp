#include "backend.h"

Backend::Backend(QQuickItem *parent, QQuickItem *root)
    : QQuickItem{parent}
    , m_Root(root)
{
    /*60 fps = 60 still images in 1000ms
    1 still image: 1000/60 = 16.67*/
    m_Timer.setInterval(16);
    connect(&m_Timer, &QTimer::timeout, this, &Backend::moveShapes);
}

void Backend::readFile(QString path)
{
    QQmlApplicationEngine *engine = qobject_cast<QQmlApplicationEngine *>(qmlEngine(m_Root));
    const QUrl shapeObjectUrl(u"qrc:/1_Assignment1_ShapeBounce/ShapeObject.qml"_qs);

    std::ifstream configFile(path.toStdString());
    if (configFile.is_open()) {
        std::string fontFilePath;
        int fontSize, fR, fG, fB;
        std::string entity;
        while (configFile >> entity) {
            if (entity == "Window") {
                int width, height;

                configFile >> width >> height;

                m_Root->window()->setColor("black");
                m_Root->window()->setWidth(width);
                m_Root->window()->setHeight(height);
            } else if (entity == "Font") {
                configFile >> fontFilePath;
                fontFilePath = "file:/" + fontFilePath;

                configFile >> fontSize;

                configFile >> fR >> fG >> fB;
            } else if (entity == "Circle" || entity == "Rectangle") {
                // https://stackoverflow.com/questions/26704621/how-to-create-a-qqmlcomponent-from-c-at-runtime
                QQmlComponent component(engine, shapeObjectUrl);
                QQuickItem *object = qobject_cast<QQuickItem *>(component.create());

                QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);

                object->setParentItem(m_Root);
                object->setParent(engine);

                object->setProperty("fontColor", QColor(fR, fG, fB));
                object->setProperty("fontSize", fontSize);
                object->setProperty("fontFilePath", QString::fromStdString(fontFilePath));

                m_ShapeObjects.push_back(object);

                std::string name;
                float x, y, sx, sy, width, height, radius = 0;
                int r, g, b;

                configFile >> name;
                object->setProperty("text", QString::fromStdString(name));

                configFile >> x >> y;
                object->setProperty("x", x);
                object->setProperty("y", y);

                configFile >> sx >> sy;
                object->setProperty("sx", sx);
                object->setProperty("sy", sy);

                configFile >> r >> g >> b;
                object->setProperty("color", QColor(r, g, b));

                if (entity == "Circle") {
                    configFile >> radius;
                    width = height = radius;
                } else {
                    configFile >> width >> height;
                }

                object->setProperty("radius", radius);
                object->setProperty("width", width);
                object->setProperty("height", height);
            }
        }

        m_Timer.start();
    }
}

void Backend::moveShapes()
{
    for (int i = 0; i < m_ShapeObjects.size(); i++) {
        QQuickItem *currShape = m_ShapeObjects[i];

        double currShapeSx = currShape->property("sx").toDouble();
        double currShapeSy = currShape->property("sy").toDouble();
        double currShapeNewX = currShape->x() + currShapeSx;
        double currShapeNewY = currShape->y() + currShapeSy;

        if (currShapeNewX <= 0 || (currShapeNewX + currShape->width()) >= m_Root->width()) {
            currShapeNewX = (currShapeNewX <= 0) ? 0 : m_Root->width() - currShape->width();
            currShapeSx *= -1;
        }

        if (currShapeNewY <= 0 || (currShapeNewY + currShape->height()) >= m_Root->height()) {
            currShapeNewY = (currShapeNewY <= 0) ? 0 : m_Root->height() - currShape->height();
            currShapeSy *= -1;
        }

        currShape->setX(currShapeNewX);
        currShape->setY(currShapeNewY);
        currShape->setProperty("sx", currShapeSx);
        currShape->setProperty("sy", currShapeSy);
    }
}
