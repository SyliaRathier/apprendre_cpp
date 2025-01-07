#include "utils.h"

QPointF Utils::convertToSceneCoordinates(double lon, double lat, double minLon, double minLat, double scale) {
    return QPointF((lon - minLon) * scale, (lat - minLat) * scale);
}
