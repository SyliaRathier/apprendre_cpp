#include "node.h"
#include "utils.h"

Node::Node() : m_id(-1), m_position(0, 0) {
}

Node::Node(qint64 id, double lat, double lon, double minLon, double minLat, double scale)
    : m_id(id), m_position(Utils::convertToSceneCoordinates(lon, lat, minLon, minLat, scale)) {
}

qint64 Node::id() const {
    return m_id;
}

QPointF Node::position() const {
    return m_position;
}
