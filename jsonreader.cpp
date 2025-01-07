#include "jsonreader.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include "utils.h"

JsonReader::JsonReader(QObject *parent) : QObject(parent) {
}

bool JsonReader::loadJson(const QString &filePath, Graph &graph, double minLon, double minLat, double scale) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file.");
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        qWarning("Failed to parse JSON or JSON document is not an object.");
        return false;
    }

    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray elements = jsonObj["elements"].toArray();
    for (const QJsonValue &value : elements) {
        QJsonObject element = value.toObject();
        if (element["type"] == "node") {
            parseNode(element, graph, minLon, minLat, scale);
        }
    }

    for (const QJsonValue &value : elements) {
        QJsonObject element = value.toObject();
        if (element["type"] == "way") {
            parseWay(element, graph);
        }
    }

    return true;
}

void JsonReader::parseNode(const QJsonObject &node, Graph &graph, double minLon, double minLat, double scale) {
    qint64 id = node["id"].toVariant().toLongLong();
    double lat = node["lat"].toDouble();
    double lon = node["lon"].toDouble();
    graph.addNode(Node(id, lat, lon, minLon, minLat, scale));
    qDebug() << "Node added:" << id << lat << lon;
}

void JsonReader::parseWay(const QJsonObject &way, Graph &graph) {
    QJsonArray nodesArray = way["nodes"].toArray();
    for (int i = 0; i < nodesArray.size() - 1; ++i) {
        qint64 fromId = nodesArray[i].toVariant().toLongLong();
        qint64 toId = nodesArray[i + 1].toVariant().toLongLong();

        double cost = 1.0; // Assuming cost is 1 for simplicity
        graph.addEdge(Edge(fromId, toId, cost));
        qDebug() << "Edge added:" << fromId << "to" << toId;
    }
}
