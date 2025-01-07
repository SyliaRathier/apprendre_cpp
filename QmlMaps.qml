import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15

Rectangle {
    anchors.fill: parent

    Map {
        id: mapView
        anchors.fill: parent
        plugin: Plugin {
            name: "osm" // Utilisation d'OpenStreetMap
        }
        center: QtPositioning.coordinate(47.738742, 7.335997) // Coordonnées initiales centrées sur Mulhouse
        zoomLevel: 15

    }
}
