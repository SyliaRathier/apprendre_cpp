#include "mapoverlay.h"

MapOverlay::MapOverlay(const QPixmap &mapImage)
    : QGraphicsPixmapItem(mapImage), zoomFactor(1.0) {
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
}

void MapOverlay::setZoom(qreal zoomFactor) {
    this->zoomFactor = zoomFactor;
    QTransform transform;
    transform.scale(zoomFactor, zoomFactor);
    setTransform(transform);
}

void MapOverlay::center(const QRectF &sceneRect) {
    QRectF imageRect = this->boundingRect(); // Dimensions de l'image
    // Calculer la position pour centrer l'image
    // qreal centerX = sceneRect.center().x() - (imageRect.width() * zoomFactor) / 2;
    // qreal centerY = sceneRect.center().y() - (imageRect.height() * zoomFactor) / 2;
    qreal centerX = sceneRect.center().x() ;
    qreal centerY = sceneRect.center().y() ;
    setPos(centerX, centerY);
}


