#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QQuickWidget>
#include <QQmlContext>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Configurer le QQuickWidget pour afficher la carte
    QQuickWidget *quickWidget = ui->quickWidget_MapView;
    quickWidget->setSource(QUrl("qrc:/QmlMaps.qml"));
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    // Configurer GraphView
    graphView = new GraphView(this);
    graphView->setStyleSheet("background: transparent;"); // Rendre le fond transparent
    graphView->setFrameStyle(0); // Supprimer le cadre

    // Utiliser un QStackedLayout pour superposer les widgets
    QStackedLayout *stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(quickWidget);
    stackedLayout->addWidget(graphView);
    stackedLayout->setStackingMode(QStackedLayout::StackAll);

    // Ajouter le QStackedLayout au layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(stackedLayout);
    ui->layout_Main->setLayout(mainLayout);

    // Charger le fichier JSON de test directement
    //47.738742, 7.335997
    QString filePath = ":/test.json"; // Chemin du fichier JSON de test
    double minLon = 7.335997; // Coordonnée minimale de longitude de votre zone d'intérêt
    double minLat = 47.738742; // Coordonnée minimale de latitude de votre zone d'intérêt
    double scale = -100000; // Facteur d'échelle pour convertir les coordonnées géographiques en coordonnées de scène
    JsonReader jsonReader;
    if (jsonReader.loadJson(filePath, graph, minLon, minLat, scale)) {
        graphView->setGraph(graph, minLon, minLat, scale);
        graphView->rotateGraph(0);
        graphView->reflectGraph(true, false);
        graphView->adjustView(); // Ajuster le zoom initial
    } else {
        qWarning("Failed to load JSON.");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
