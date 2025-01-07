#ifndef MAPOVERLAY_H
#define MAPOVERLAY_H

#include <QGraphicsPixmapItem>

class MapOverlay : public QGraphicsPixmapItem {
public:
    MapOverlay(const QPixmap &mapImage);
    void setZoom(qreal zoomFactor);
    void center(const QRectF &sceneRect);

private:
    qreal zoomFactor;
};

#endif // MAPOVERLAY_H
