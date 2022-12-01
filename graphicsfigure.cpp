#include "graphicsfigure.h"


GraphicsFigure::GraphicsFigure()
    :QObject()
{
    startPoint = QPoint(0, 0);
    endPoint = QPoint(1, 1);
}

GraphicsFigure::GraphicsFigure(int typee)
{
    startPoint = QPoint(0, 0);
    endPoint = QPoint(1, 1);
    typeFigure = typee;
}

GraphicsFigure::~GraphicsFigure()
{

}

GraphicsFigure::GraphicsFigure(QPoint point)
    : QObject()
{
    this->startPoint = point;
    this->endPoint = point;
}

void GraphicsFigure::changeEndLocation(QPoint point)
{
    endPoint = point;
}

std::vector<QGraphicsItem *> GraphicsFigure::getVectorNeedDelete()
{
    std::vector<QGraphicsItem *> t;
    return (t);
}
