import QtQuick 2.15

Item {
    id: graphView
    width: 800
    height: 600

    property var nodes: []
    property var edges: []

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);

            // Dessiner les arêtes
            ctx.strokeStyle = "black";
            ctx.lineWidth = 1;
            for (var i = 0; i < edges.length; i++) {
                var edge = edges[i];
                var fromNode = nodes[edge.fromId];
                var toNode = nodes[edge.toId];
                if (fromNode && toNode) {
                    ctx.beginPath();
                    ctx.moveTo(fromNode.x, fromNode.y);
                    ctx.lineTo(toNode.x, toNode.y);
                    ctx.stroke();
                }
            }

            // Dessiner les nœuds
            ctx.fillStyle = "red";
            for (var i = 0; i < nodes.length; i++) {
                var node = nodes[i];
                ctx.beginPath();
                ctx.arc(node.x, node.y, 2, 0, 2 * Math.PI);
                ctx.fill();
            }
        }
    }
}
