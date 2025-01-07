#ifndef GRAPH_H
#define GRAPH_H

#include <QMap>
#include <QVector>
#include "node.h"
#include "edge.h"

class Graph {
public:
    void addNode(const Node &node);
    void addEdge(const Edge &edge);
    const QMap<qint64, Node>& getNodes() const;
    const QVector<Edge>& getEdges() const;
    const Node* getNodeById(qint64 id) const;

private:
    QMap<qint64, Node> m_nodes;
    QVector<Edge> m_edges;
};

#endif // GRAPH_H
