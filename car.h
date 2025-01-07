#ifndef CAR_H
#define CAR_H

#include <QPointF>
#include <QVector>
#include <QMap>
#include "edge.h"
#include "node.h"

class Car {
public:
    Car(qint64 startNodeId, const QMap<qint64, Node>& nodes, const QVector<Edge>& edges, double speed = 0.01);
    void updatePosition(const QMap<qint64, Node>& nodes, const QVector<Edge>& edges);
    QPointF position() const;
    void setSpeed(double speed); // Ajouté pour définir la vitesse

private:
    QPointF m_position;
    qint64 m_currentNodeId;
    qint64 m_nextNodeId;
    double m_progress; // Progression sur l'arête actuelle (0.0 à 1.0)
    double m_speed; // Vitesse de la voiture

    void chooseNextEdge(const QMap<qint64, Node>& nodes, const QVector<Edge>& edges);
};

#endif // CAR_H
