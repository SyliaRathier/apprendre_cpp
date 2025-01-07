#ifndef NODE_H
#define NODE_H

#include <QPointF>

class Node {
public:
    Node();
    Node(qint64 id, double lat, double lon, double minLon, double minLat, double scale);
    qint64 id() const;
    QPointF position() const;

private:
    qint64 m_id;
    QPointF m_position;
};

#endif // NODE_H
