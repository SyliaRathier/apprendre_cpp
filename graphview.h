#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include "graph.h"
#include "car.h"

class MapOverlay;

class GraphView : public QGraphicsView {
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = nullptr);
    void setGraph(const Graph &graph, double minLon, double minLat, double scale);
    void setMap(const QPixmap &mapImage);
    void adjustView();

protected:
    void wheelEvent(QWheelEvent *event) override;

private slots:
    void updateCars();

private:
    QGraphicsScene *scene;
    MapOverlay *mapOverlay;
    double zoomFactor;
    QVector<Car> cars;
    QVector<QGraphicsEllipseItem*> carItems; // Ajouté pour stocker les éléments graphiques des voitures
    QVector<QGraphicsEllipseItem*> proximityCircles; // Ajouté pour stocker les éléments graphiques des cercles de proximité
    Graph graph; // Ajouté pour stocker le graphe
    double proximityRadius; // Rayon de proximité

    void checkProximityAndColorCars(); // Méthode pour vérifier la proximité et changer la couleur des voitures
};

#endif // GRAPHVIEW_H
