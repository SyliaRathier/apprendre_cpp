#ifndef JSONREADER_H
#define JSONREADER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include "graph.h"
#include "node.h"
#include "edge.h"

class JsonReader : public QObject {
    Q_OBJECT

public:
    JsonReader(QObject *parent = nullptr);
    bool loadJson(const QString &filePath, Graph &graph, double minLon, double minLat, double scale);

private:
    void parseNode(const QJsonObject &node, Graph &graph, double minLon, double minLat, double scale);
    void parseWay(const QJsonObject &way, Graph &graph);
};

#endif // JSONREADER_H
