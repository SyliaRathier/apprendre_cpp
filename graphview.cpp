#include "graphview.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QWheelEvent>
#include <QDebug>
#include <QTimer>
#include <QRandomGenerator>
#include "car.h"

GraphView::GraphView(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)), mapOverlay(nullptr), zoomFactor(1.0), proximityRadius(50.0) {
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Timer pour mettre à jour la position des voitures
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GraphView::updateCars);
    timer->start(100); // Mettre à jour toutes les 100 ms
}

void GraphView::setGraph(const Graph &graph, double minLon, double minLat, double scale) {
    this->graph = graph; // Stocker le graphe

    // Ajouter la carte en premier
    // if (mapOverlay) {
    //     scene->addItem(mapOverlay);
    // }

    const QMap<qint64, Node> &nodes = graph.getNodes();
    const QVector<Edge> &edges = graph.getEdges();

    // Ajouter les arêtes
    QPen edgePen(Qt::black);
    edgePen.setWidth(0.5); // Rendre les arêtes moins larges
    for (const Edge &edge : edges) {
        const Node* fromNode = graph.getNodeById(edge.fromId());
        const Node* toNode = graph.getNodeById(edge.toId());
        if (fromNode && toNode) {
            scene->addLine(fromNode->position().x(), fromNode->position().y(), toNode->position().x(), toNode->position().y(), edgePen);
            qDebug() << "Edge drawn:" << edge.fromId() << "to" << edge.toId();
        } else {
            qWarning() << "Node with id" << edge.fromId() << "or" << edge.toId() << "not found.";
        }
    }

    // Ajouter les nœuds
    QPen nodePen(Qt::black);
    nodePen.setWidth(0.5); // Rendre les bords des ellipses moins larges
    QBrush nodeBrush(Qt::red);
    for (const Node &node : nodes) {
        // Rendre les nœuds vraiment petits
        scene->addEllipse(node.position().x() - 1, node.position().y() - 1, 2, 2, nodePen, nodeBrush);
        qDebug() << "Node drawn:" << node.id();
    }

    // Ajouter des voitures
    int numberOfCars = 200; // Nombre fixe de voitures
    double carSpeed = 0.05; // Vitesse des voitures
    QVector<qint64> nodeIds = nodes.keys().toVector(); // Initialiser nodeIds avec les clés des nœuds
    for (int i = 0; i < numberOfCars; ++i) {
        qint64 startNodeId = nodeIds.at(QRandomGenerator::global()->bounded(nodeIds.size())); // Choisir un nœud de départ aléatoire
        cars.append(Car(startNodeId, nodes, edges, carSpeed));
        QGraphicsEllipseItem *carItem = new QGraphicsEllipseItem(-10, -10, 20, 20); // Augmenter la taille de l'ellipse
        carItem->setBrush(Qt::blue); // Initialiser toutes les voitures en bleu
        scene->addItem(carItem);
        carItems.append(carItem);

        // Ajouter un cercle de proximité
        QGraphicsEllipseItem *proximityCircle = new QGraphicsEllipseItem(-proximityRadius, -proximityRadius, 2 * proximityRadius, 2 * proximityRadius);
        proximityCircle->setBrush(QColor(128, 128, 128, 128)); // Gris transparent
        proximityCircle->setPen(Qt::NoPen); // Pas de bordure
        scene->addItem(proximityCircle);
        proximityCircles.append(proximityCircle);
    }

    // Ajuste la vue pour montrer tout le graphe
    adjustView();  // Ajuste la vue pour le graphe
}

void GraphView::updateCars() {
    const QMap<qint64, Node> &nodes = graph.getNodes();
    const QVector<Edge> &edges = graph.getEdges();

    for (int i = 0; i < cars.size(); ++i) {
        cars[i].updatePosition(nodes, edges);
        QPointF pos = cars[i].position();
        // Mettre à jour la position de la voiture sur la scène
        carItems[i]->setPos(pos);
        // Mettre à jour la position du cercle de proximité
        proximityCircles[i]->setPos(pos);
    }

    checkProximityAndColorCars(); // Vérifier la proximité et changer la couleur des voitures
}

void GraphView::checkProximityAndColorCars() {
    // Réinitialiser toutes les voitures en bleu
    for (QGraphicsEllipseItem *carItem : carItems) {
        carItem->setBrush(Qt::blue);
    }

    // Vérifier la proximité des voitures
    for (int i = 0; i < cars.size(); ++i) {
        for (int j = i + 1; j < cars.size(); ++j) {
            QPointF pos1 = cars[i].position();
            QPointF pos2 = cars[j].position();
            double distance = QLineF(pos1, pos2).length();
            if (distance <= 2 * proximityRadius) {
                carItems[i]->setBrush(Qt::green);
                carItems[j]->setBrush(Qt::green);
            }
        }
    }
}

// void GraphView::setMap(const QPixmap &mapImage) {
//     if (mapOverlay) {
//         scene->removeItem(mapOverlay);
//         delete mapOverlay;
//     }
//     mapOverlay = new MapOverlay(mapImage);
//     mapOverlay->setZValue(-1); // Place la carte en arrière-plan
//     scene->addItem(mapOverlay);

//     // Ajuster les dimensions de la scène pour inclure l'image
//     QRectF imageRect = mapOverlay->boundingRect();
//     scene->setSceneRect(imageRect); // Définir la scène pour inclure l'image

//     // Centrer la carte dans la scène
//     mapOverlay->center(scene->sceneRect());
//     adjustView();
// }

void GraphView::adjustView() {
    fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    scale(1.5, 1.5); // Augmenter le zoom de base
}

void GraphView::wheelEvent(QWheelEvent *event) {
    const double scaleFactor = 1.15;  // Facteur de zoom

    if (event->angleDelta().y() > 0) {
        scale(scaleFactor, scaleFactor);  // Zoom avant
    } else {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);  // Zoom arrière
    }
}
