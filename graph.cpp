#include "graph.h"
#include <QDebug>

void Graph::addNode(const Node &node) {
    m_nodes.insert(node.id(), node);
    qDebug() << "Node added to graph:" << node.id();
}

void Graph::addEdge(const Edge &edge) {
    m_edges.append(edge);
    qDebug() << "Edge added to graph:" << edge.fromId() << "to" << edge.toId();
}

const QMap<qint64, Node>& Graph::getNodes() const {
    return m_nodes;
}

const QVector<Edge>& Graph::getEdges() const {
    return m_edges;
}

const Node* Graph::getNodeById(qint64 id) const {
    auto it = m_nodes.find(id);
    if (it != m_nodes.end()) {
        return &it.value();
    }
    return nullptr;
}
