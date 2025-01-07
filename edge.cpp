#include "edge.h"

Edge::Edge(qint64 fromId, qint64 toId, double cost)
    : m_fromId(fromId), m_toId(toId), m_cost(cost) {
}

qint64 Edge::fromId() const {
    return m_fromId;
}

qint64 Edge::toId() const {
    return m_toId;
}

double Edge::cost() const {
    return m_cost;
}
