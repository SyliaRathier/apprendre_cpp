#ifndef EDGE_H
#define EDGE_H
#include <QPointF>


class Edge {
public:
    Edge(qint64 fromId, qint64 toId, double cost);
    qint64 fromId() const;
    qint64 toId() const;
    double cost() const;

private:
    qint64 m_fromId;
    qint64 m_toId;
    double m_cost;
};

#endif // EDGE_H
