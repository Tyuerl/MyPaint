#include "ellipsegraphscene.h"

EllipseGraphScene::EllipseGraphScene()
    :GraphicsFigure()
{
    ellipse = new QGraphicsEllipseItem();
}

EllipseGraphScene::EllipseGraphScene(QPoint point)
    :GraphicsFigure(point)
{
    startPoint = point;
    ellipse = new QGraphicsEllipseItem();

}

EllipseGraphScene::~EllipseGraphScene()
{
    delete ellipse;
}

std::vector<QGraphicsItem *> EllipseGraphScene::getVectorNeedDelete()
{
    std::vector<QGraphicsItem *> res;
    res.push_back(ellipse);
    return (res);
}

void EllipseGraphScene::changeEndLocation(QPoint point)
{
    endPoint = point;
    ellipse->setRect(QRect(startPoint, endPoint));
}

void EllipseGraphScene::addToScene(RedactScene *scenee)
{

    scenee->addItem(ellipse);
}

void EllipseGraphScene::changeColor(QColor color)
{
    ellipse->setPen(QPen(color));
}
