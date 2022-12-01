#include "redactscene.h"
#include <QDebug>
RedactScene::RedactScene()
{

}

void RedactScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit signalMouseReleaseCoordinate(event->scenePos());
}

void RedactScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit signalMousePressCoordinate(event->scenePos());

}

void RedactScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        text.clear();
        *stateButton = StateButton::NONE;
    }
    else if (event->key() == Qt::Key_Backspace)
    {
        if (text.length() > 0)
            text.chop(1);
    }
    else if (*stateButton == StateButton::TEXT)
        text += (event->text());
    emit signalKeyPress();
}

void RedactScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalMouseMoveCoordinate(event->scenePos());
}

