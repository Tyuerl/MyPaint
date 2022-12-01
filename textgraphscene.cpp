#include "textgraphscene.h"

TextGraphScene::TextGraphScene()
    :GraphicsFigure()
{
    text = new QGraphicsTextItem();
    rect = new QGraphicsRectItem(QRect(0, 0, 200, 100));
    typeFigure = TEXT;
}

TextGraphScene::TextGraphScene(QPoint point)
    :GraphicsFigure(point)
{
    typeFigure = TEXT;
    text = new QGraphicsTextItem();
    text->setPos(point);
    rect = new QGraphicsRectItem(QRect(point.x(), point.y(), 200, 100));
}

TextGraphScene::~TextGraphScene()
{
    delete text;
    delete rect;
}

std::vector<QGraphicsItem *> TextGraphScene::getVectorNeedDelete()
{
    std::vector<QGraphicsItem *> result;
    result.push_back(text);
    result.push_back(rect);
    return (result);
}

void TextGraphScene::changeEndLocation(QPoint point)
{
    endPoint = point;
    rect->setRect(QRect(startPoint, endPoint));
    text->setPos(startPoint);
    text->setTextWidth(point.x() - startPoint.x());
    text->setPlainText(scene->text);
}

void TextGraphScene::deleteRect()
{
    if (flag == true)
        scene->removeItem(rect);
    flag = false;
}

void TextGraphScene::addToScene(RedactScene *scenee)
{
    scene = scenee;
    scenee->addItem(text);
    scenee->addItem(rect);
}

void TextGraphScene::changeColor(QColor color)
{
    rect->setPen(color);
    text->setDefaultTextColor(color);
}
