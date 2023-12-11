#include "backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
{}

void Backend::readFile(QString path)
{
    std::ifstream configFile(path.toStdString());
    if (configFile.is_open()) {
        std::string entity;
        while (configFile >> entity) {
            if (entity == "Window") {
                int width, height;
                QVariantList list;

                configFile >> width >> height;
                list.push_back(width);
                list.push_back(height);

                emit entitySet(QString::fromStdString(entity), list);
            } else if (entity == "Font") {
                std::string fontFile;
                int fontSize, r, g, b;
                QVariantList list;

                configFile >> fontFile;
                list.push_back(QString::fromStdString(fontFile));

                configFile >> fontSize;
                list.push_back(fontSize);

                configFile >> r >> g >> b;
                list.push_back(r);
                list.push_back(g);
                list.push_back(b);

                emit entitySet(QString::fromStdString(entity), list);
            } else if (entity == "Circle") {
                std::string name;
                float x, y, sx, sy, radius;
                int r, g, b;
                QVariantList list;

                configFile >> name;
                list.push_back(QString::fromStdString(name));

                configFile >> x >> y;
                list.push_back(x);
                list.push_back(y);

                configFile >> sx >> sy;
                list.push_back(sx);
                list.push_back(sy);

                configFile >> r >> g >> b;
                list.push_back(r);
                list.push_back(g);
                list.push_back(b);

                configFile >> radius;
                list.push_back(radius);

                emit entitySet(QString::fromStdString(entity), list);
            } else if (entity == "Rectangle") {
                std::string name;
                float x, y, sx, sy, width, height;
                int r, g, b;
                QVariantList list;

                configFile >> name;
                list.push_back(QString::fromStdString(name));

                configFile >> x >> y;
                list.push_back(x);
                list.push_back(y);

                configFile >> sx >> sy;
                list.push_back(sx);
                list.push_back(sy);

                configFile >> r >> g >> b;
                list.push_back(r);
                list.push_back(g);
                list.push_back(b);

                configFile >> width >> height;
                list.push_back(width);
                list.push_back(height);

                emit entitySet(QString::fromStdString(entity), list);
            }
        }
        emit startMoving();
    }
}
