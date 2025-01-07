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
        center: QtPositioning.coordinate(47.7555, 7.317) // Coordonnées centrées sur Mulhouse
        zoomLevel: 15
    }
}
