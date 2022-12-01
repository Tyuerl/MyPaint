#ifndef REDACTSCENE_H
#define REDACTSCENE_H

#include <QWidget>
#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QKeyEvent>

enum            StateButton
{
                NONE,
                LINE,
                ELLIPSE,
                TEXT,
                ARROW,
                ZOOM,
                PEN,
                CONTRAST
};
enum            StateMouse
{
                NONEPRESSED,
                PRESSED
};
class RedactScene : public QGraphicsScene
{
    Q_OBJECT
public:
            RedactScene();
    int     *stateButton;
    int     *stateMouse;
    QString text;
signals:
    void    signalMousePressCoordinate(QPointF point);
    void    signalMouseReleaseCoordinate(QPointF point);
    void    signalMouseMoveCoordinate(QPointF point);
    void    signalKeyPress();
private slots:
    void    keyPressEvent(QKeyEvent *event) override;
    void    mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void    mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void    mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // REDACTSCENE_H
