import QtQuick
import com.company.shapebounce 1.0

Window {
    id: root
    width: 640
    height: 480
    visible: true
    color: "black"
    title: qsTr("Shape Bounce")
    property list<ShapeObject> shapeObjectsList

    Backend {
        id: backend
        property url fontFilePath: ""
        property int fontSize: 12
        property color fontColor: "black"

        onEntitySet: function (entityName, entityProperty) {
            if (entityName === "Window") {
                root.width = entityProperty[0]
                root.height = entityProperty[1]
            } else if (entityName === "Font") {
                backend.fontFilePath = "file:/" + entityProperty[0]
                backend.fontSize = entityProperty[1]
                backend.fontColor = Qt.rgba(entityProperty[2] / 255,
                                            entityProperty[3] / 255,
                                            entityProperty[4] / 255, 1)
            } else {
                let component = Qt.createComponent("ShapeObject.qml")
                let sprite = null
                if (component.status === Component.Ready) {
                    sprite = component.createObject(root, {
                                                        "fontColor": backend.fontColor,
                                                        "fontSize": backend.fontSize,
                                                        "fontFilePath": backend.fontFilePath,
                                                        "text": entityProperty[0],
                                                        "x": entityProperty[1],
                                                        "y": entityProperty[2],
                                                        "sx": entityProperty[3],
                                                        "sy": entityProperty[4],
                                                        "color": Qt.rgba(
                                                                     entityProperty[5] / 255,
                                                                     entityProperty[6] / 255,
                                                                     entityProperty[7] / 255,
                                                                     1)
                                                    })
                    if (sprite === null) {
                        console.log("Error creating object")
                    } else if (entityName === "Circle") {
                        sprite.radius = sprite.width = sprite.height = entityProperty[8]
                    } else {
                        sprite.width = entityProperty[8]
                        sprite.height = entityProperty[9]
                    }
                    root.shapeObjectsList.push(sprite)
                } else if (component.status === Component.Error) {
                    console.log("Error loading component:",
                                component.errorString())
                }
            }
        }

        onStartMoving: {
            timer.start()
        }
    }

    function checkCollision(rect1, rect2) {
        if (rect1.x < rect2.x + rect2.width && rect1.x + rect1.width > rect2.x
                && rect1.y < rect2.y + rect2.height
                && rect1.y + rect1.height > rect2.y) {

            var overlapLeft = rect2.x + rect2.width - rect1.x
            var overlapRight = rect1.x + rect1.width - rect2.x
            var overlapTop = rect2.y + rect2.height - rect1.y
            var overlapBottom = rect1.y + rect1.height - rect2.y

            var minOverlap = Math.min(overlapLeft, overlapRight, overlapTop,
                                      overlapBottom)

            if (minOverlap === overlapLeft) {
                return 'left'
            } else if (minOverlap === overlapRight) {
                return 'right'
            } else if (minOverlap === overlapTop) {
                return 'top'
            } else if (minOverlap === overlapBottom) {
                return 'bottom'
            }
        }
    }

    Timer {
        id: timer
        interval: 16
        repeat: true
        onTriggered: {
            for (var i = 0; i < shapeObjectsList.length; i++) {
                let currShape = shapeObjectsList[i]

                let xCoord = currShape.x + currShape.sx
                if (xCoord <= 0 || (xCoord + currShape.width) >= root.width) {
                    currShape.x = (xCoord <= 0) ? 0 : root.width - currShape.width
                    currShape.sx *= -1
                } else {
                    currShape.x = xCoord
                }

                let yCoord = currShape.y + currShape.sy
                if (yCoord <= 0 || (yCoord + currShape.height) >= root.height) {
                    currShape.y = (yCoord <= 0) ? 0 : root.height - currShape.height
                    currShape.sy *= -1
                } else {
                    currShape.y = yCoord
                }

                let ownRect = Qt.rect(currShape.x, currShape.y,
                                      currShape.width, currShape.height)

                for (var j = 0; j < shapeObjectsList.length; j++) {
                    if (j !== i) {
                        let otherRect = Qt.rect(shapeObjectsList[j].x,
                                                shapeObjectsList[j].y,
                                                shapeObjectsList[j].width,
                                                shapeObjectsList[j].height)

                        let collideSide = checkCollision(ownRect, otherRect)
                        if (collideSide === 'left' || collideSide === 'right') {
                            currShape.x = collideSide
                                    === 'right' ? otherRect.x - currShape.width : otherRect.x
                                                  + otherRect.width
                            currShape.sx *= -1
                        } else if (collideSide === 'top'
                                   || collideSide === 'bottom') {
                            currShape.y = collideSide
                                    === 'bottom' ? otherRect.y - currShape.height : otherRect.y
                                                   + otherRect.height
                            currShape.sy *= -1
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        backend.readFile(
                    "D:/Documents/Programming/C++/Study/Game_Development/1_Assignment1_ShapeBounce/config.txt")
    }
}
