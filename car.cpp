#include "car.h"
#include <QRandomGenerator>
#include <QDebug>

Car::Car(qint64 startNodeId, const QMap<qint64, Node>& nodes, const QVector<Edge>& edges, double speed)
    : m_currentNodeId(startNodeId), m_nextNodeId(-1), m_progress(0.0), m_speed(speed) {
    m_position = nodes.value(startNodeId).position();
    chooseNextEdge(nodes, edges);
}

void Car::updatePosition(const QMap<qint64, Node>& nodes, const QVector<Edge>& edges) {
    if (m_nextNodeId == -1) return;

    const Node& fromNode = nodes.value(m_currentNodeId);
    const Node& toNode = nodes.value(m_nextNodeId);

    m_progress += m_speed;
    if (m_progress >= 1.0) {
        m_progress = 0.0; // Réinitialiser la progression
        m_currentNodeId = m_nextNodeId; // Mettre à jour le nœud actuel
        m_position = toNode.position(); // Mettre à jour la position de la voiture
        chooseNextEdge(nodes, edges); // Choisir le prochain edge
    } else {
        QPointF fromPos = fromNode.position();
        QPointF toPos = toNode.position();
        m_position = fromPos + (toPos - fromPos) * m_progress;
    }
}

void Car::chooseNextEdge(const QMap<qint64, Node>& nodes, const QVector<Edge>& edges) {
    QVector<Edge> possibleEdges;
    for (const Edge& edge : edges) {
        if (edge.fromId() == m_currentNodeId) {
            possibleEdges.append(edge);
        }
    }

    if (possibleEdges.isEmpty()) {
        qWarning() << "No edges found for node" << m_currentNodeId;
        m_nextNodeId = -1;
        return;
    }

    int randomIndex = QRandomGenerator::global()->bounded(possibleEdges.size());
    m_nextNodeId = possibleEdges[randomIndex].toId();
}

QPointF Car::position() const {
    return m_position;
}

void Car::setSpeed(double speed) {
    m_speed = speed;
}
