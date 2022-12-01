#include "arrowgraphscene.h"

ArrowGraphScene::ArrowGraphScene()
    :LineGraphScene()
{

}

ArrowGraphScene::ArrowGraphScene(QPoint point)
    :LineGraphScene(point)
{
    startPoint = point;
    mainLine = new QGraphicsLineItem();
    firstLine = new QGraphicsLineItem();
    secondLine = new QGraphicsLineItem();
    thirdLine = new QGraphicsLineItem();
    fourthLine = new QGraphicsLineItem();
    firstLine->setTransformOriginPoint(point);
    mainLine->setTransformOriginPoint(point);
    secondLine->setTransformOriginPoint(point);
    thirdLine->setTransformOriginPoint(point);
    fourthLine->setTransformOriginPoint(point);
}

ArrowGraphScene::~ArrowGraphScene()
{
    delete thirdLine;
    delete fourthLine;
}

QLineF *linesForOtrezok(QPoint start, QPoint end, int lenOtrBounds = 5) // заусенчики у отрезка
{
    QLineF *arrayLines = new QLineF[4];
    double sign = 1;
    double lengthX = (start.x() - end.x());
    double lengthY = (start.y() - end.y());
    QPointF startOtr;
    if (lengthX * lengthY < 0)
        sign = -sign;
    double lengthMainLine = sqrt(lengthX * lengthX + lengthY * lengthY);
    if (lengthMainLine < 30)
        lenOtrBounds = 3;
    else if (lengthMainLine > 100)
        lenOtrBounds = 7;


    if (start.x() > end.x())
            sign = -sign;
    startOtr = QPointF((double)start.x() - sign * lenOtrBounds,
                               (double)start.y() - sign * lenOtrBounds * 0.7);
    arrayLines[0] = QLineF(startOtr, start);

    startOtr = QPointF((double)start.x() - sign *lenOtrBounds,
                               (double)start.y() + sign * lenOtrBounds * 0.7);
    arrayLines[1] = QLineF(startOtr, start);

    startOtr = QPointF((double)end.x() - sign * lenOtrBounds,
                               (double)end.y() + sign * lenOtrBounds * 0.7);
    arrayLines[2] = QLineF(startOtr, end);

    startOtr = QPointF((double)end.x() - sign * lenOtrBounds,
                               (double)end.y() - sign *lenOtrBounds * 0.7);
    arrayLines[3] = QLineF(startOtr, end);
    return (arrayLines);
}

void ArrowGraphScene::changeEndLocation(QPoint point)
{
    endPoint = point;
    QLineF * temp;
    arcTangens =  atan(((double)startPoint.y() - (double)endPoint.y())
                      / ((double)startPoint.x() - (double)endPoint.x())) * 180 / 3.1415;
    pifagor = sqrt(abs(startPoint.x() - endPoint.x()) * abs(startPoint.x() - endPoint.x())
                   + abs(startPoint.y() - endPoint.y()) * abs(startPoint.y() - endPoint.y()));
    if (endPoint.x() < startPoint.x())
        pifagor = -pifagor;
    if (startPoint.x() != endPoint.x())
       temp = linesForOtrezok(startPoint, QPoint(startPoint.x() + pifagor, startPoint.y()));
    else
         temp = linesForOtrezok(startPoint, QPoint(startPoint.x() - pifagor, startPoint.y()));

    mainLine->setRotation(arcTangens);
    firstLine->setRotation(arcTangens);
    secondLine->setRotation(arcTangens);
    thirdLine->setRotation(arcTangens);
    fourthLine->setRotation(arcTangens);

    firstLine->setLine(temp[0]);
    secondLine->setLine(temp[1]);
    thirdLine->setLine(temp[2]);
    fourthLine->setLine(temp[3]);
    if (startPoint.x() != endPoint.x())
        mainLine->setLine(QLineF(startPoint, QPointF(startPoint.x() + pifagor, startPoint.y())));
    else
        mainLine->setLine(QLineF(startPoint, QPointF(startPoint.x() - pifagor, startPoint.y())));

    delete temp;
}

std::vector<QGraphicsItem *> ArrowGraphScene::getVectorNeedDelete()
{
    std::vector<QGraphicsItem*> result;
    result.push_back(mainLine);
    result.push_back(firstLine);
    result.push_back(secondLine);
    result.push_back(thirdLine);
    result.push_back(fourthLine);
    return(result);
}

void ArrowGraphScene::addToScene(RedactScene *scenee)
{
    scenee->addItem(mainLine);
    scenee->addItem(firstLine);
    scenee->addItem(secondLine);
    scenee->addItem(thirdLine);
    scenee->addItem(fourthLine);
}

void ArrowGraphScene::changeColor(QColor color)
{
    mainLine->setPen(QPen(color));
    firstLine->setPen(QPen(color));
    secondLine->setPen(QPen(color));
    thirdLine->setPen(QPen(color));
    fourthLine->setPen(QPen(color));
}

