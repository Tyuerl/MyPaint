#include "pengraphscene.h"

namespace  {
    int counterOfLines = 0;
}

PenGraphScene::PenGraphScene()
    :GraphicsFigure()
{

}

PenGraphScene::~PenGraphScene()
{
    lines.clear();
}



PenGraphScene::PenGraphScene(QPoint point)
    :GraphicsFigure(point)
{
  betweenStartEndPoint = point;
}

PenGraphScene::PenGraphScene(QPoint point, RedactScene *scenee)
    :GraphicsFigure(point)
{
  betweenStartEndPoint = point;
  scene = scenee;
}


std::vector<QGraphicsItem *> PenGraphScene::getVectorNeedDelete()
{
    return(lines);
}

void PenGraphScene::changeEndLocation(QPoint point)
{
    betweenStartEndPoint = endPoint;
    endPoint = point;
    lines.push_back(new QGraphicsLineItem(QLineF(betweenStartEndPoint, endPoint)));
    addToScene(scene);
}

void PenGraphScene::addToScene(RedactScene *scenee)
{
    if (lines.empty())
        return;
    if (scenee ==nullptr)
        scene->addItem(lines.back());
    else
        scenee->addItem(lines.back());
}

void PenGraphScene::changeColor(QColor color)
{
    for(size_t i = 0; i < lines.size(); i++)
        ((QGraphicsLineItem *)lines[i])->setPen(color);

}
