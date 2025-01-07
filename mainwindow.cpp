#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QQuickWidget>
#include <QQmlContext>
#include <QFileDialog>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Configurer le QQuickWidget pour afficher la carte
    QQuickWidget *quickWidget = ui->quickWidget_MapView;
    quickWidget->setSource(QUrl("qrc:/QmlMaps.qml"));
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    // Configurer GraphView
    graphView = new GraphView(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(graphView);
    ui->layout_Main->setLayout(layout);

    // Charger le fichier JSON de test directement
    QString filePath = ":/test.json"; // Chemin du fichier JSON de test
    double minLon = 7.317; // Coordonnée minimale de longitude de votre zone d'intérêt
    double minLat = 47.7555; // Coordonnée minimale de latitude de votre zone d'intérêt
    double scale = 100000; // Facteur d'échelle pour convertir les coordonnées géographiques en coordonnées de scène
    JsonReader jsonReader;
    if (jsonReader.loadJson(filePath, graph, minLon, minLat, scale)) {
        graphView->setGraph(graph, minLon, minLat, scale);
        graphView->adjustView(); // Ajuster le zoom initial
    } else {
        qWarning("Failed to load JSON.");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
