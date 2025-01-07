#ifndef UTILS_H
#define UTILS_H

#include <QPointF>

class Utils {
public:
    static QPointF convertToSceneCoordinates(double lon, double lat, double minLon, double minLat, double scale);
};

#endif // UTILS_H
