#include "linegraphscene.h"
#include "graphicsfigure.h"

#include <QBrush>
LineGraphScene::LineGraphScene()
    :GraphicsFigure()
{
    typeFigure = LINE;
    mainLine = new QGraphicsLineItem();
    firstLine = new QGraphicsLineItem();
    secondLine = new QGraphicsLineItem();
    text = new QGraphicsTextItem();
}

LineGraphScene::LineGraphScene(QPoint point)
    :GraphicsFigure(point)
{
    typeFigure = LINE;
    mainLine = new QGraphicsLineItem();
    firstLine = new QGraphicsLineItem();
    secondLine = new QGraphicsLineItem();
    text = new QGraphicsTextItem();

}

LineGraphScene::~LineGraphScene()
{
    delete mainLine;
    delete firstLine;
    delete secondLine;
    delete text;
}

std::vector<QGraphicsItem*> LineGraphScene::getVectorNeedDelete()
{
    std::vector<QGraphicsItem*> result;
    result.push_back(mainLine);
    result.push_back(firstLine);
    result.push_back(secondLine);
    result.push_back(text);

    return(result);
}

QLineF lineForOtrezok(QPoint start, QPoint end, int lenOtrBounds = 5) // заусенчики у отрезка
{
    double lengthX = abs(start.x() - end.x());
    double lengthY = abs(start.y() - end.y());
    double lengthMainLine = sqrt(lengthX * lengthX + lengthY * lengthY);
    if (lengthMainLine < 30)
        lenOtrBounds = 3;
    else if (lengthMainLine > 100)
        lenOtrBounds = 7;
    QPointF startOtr;
    QPointF endOtr;
    if ((start.x() - end.x()) *(start.y() - end.y()) > 0)
    {

        startOtr = QPointF((double)start.x() + lengthY * lenOtrBounds / lengthMainLine,
                                   (double)start.y() - lengthX * lenOtrBounds / lengthMainLine);
        endOtr = QPointF((double)start.x() - lengthY * lenOtrBounds / lengthMainLine,
                                 (double)start.y() + lengthX * lenOtrBounds / lengthMainLine);
    }
    else
    {
        startOtr = QPointF((double)start.x() + lengthY * lenOtrBounds / lengthMainLine,
                                   (double)start.y() + lengthX * lenOtrBounds / lengthMainLine);
        endOtr = QPointF((double)start.x() - lengthY * lenOtrBounds / lengthMainLine,
                                 (double)start.y() - lengthX * lenOtrBounds / lengthMainLine);
    }
    return QLineF(startOtr, endOtr);
}


void LineGraphScene::changeEndLocation(QPoint point)
{
    endPoint = point;
    arcTangens =  atan(((double)startPoint.y() - (double)endPoint.y())
                      / ((double)startPoint.x() - (double)endPoint.x())) * 180 / 3.1415;
    pifagor = sqrt(abs(startPoint.x() - endPoint.x()) * abs(startPoint.x() - endPoint.x())
                   + abs(startPoint.y() - endPoint.y()) * abs(startPoint.y() - endPoint.y()));
    if (endPoint.x() < startPoint.x())
        pifagor = -pifagor;
    length = QString::number(int(pifagor * PX_TO_MM)) + " mm";

    mainLine->setLine(QLine(startPoint, endPoint));
    secondLine->setLine(lineForOtrezok(endPoint, startPoint));
    firstLine->setLine(lineForOtrezok(startPoint, endPoint));
    text->setPos(startPoint.x() + (endPoint.x() - startPoint.x()) / 2, startPoint.y() + (endPoint.y() -  startPoint.y()) / 2);
    text->setPlainText(length);
    text->setRotation(arcTangens);
}

void LineGraphScene::addToScene(RedactScene *scenee)
{
    scenee->addItem(mainLine);
    scenee->addItem(firstLine);
    scenee->addItem(secondLine);
    scenee->addItem(text);
}

void LineGraphScene::changeColor(QColor color)
{
    mainLine->setPen(QPen(color));
    firstLine->setPen(QPen(color));
    secondLine->setPen(QPen(color));
    text->setDefaultTextColor(color);
}

