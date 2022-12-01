#include "zoomgraphsene.h"

namespace{
    //QPointF last;
    //QList<QGraphicsItem> *lineT;
    constexpr int HEIGHT_ZOOM = 40;
    constexpr int WEIGHT_ZOOM = 70;
}

ZoomGraphSene::ZoomGraphSene()
    :GraphicsFigure()
{
    zoom = new QGraphicsPixmapItem();
    zoom->setZValue(100);
    count = 0;
}

ZoomGraphSene::ZoomGraphSene(QPoint point)
    :GraphicsFigure(point)
{
    zoom = new QGraphicsPixmapItem();
    zoom->setZValue(100);
    zoom->setPos(point);
    count = 0;
}

ZoomGraphSene::~ZoomGraphSene()
{
    delete zoom;
}

std::vector<QGraphicsItem *> ZoomGraphSene::getVectorNeedDelete()
{
    std::vector<QGraphicsItem *> result;
    result.push_back(zoom);
    return result;
}

void ZoomGraphSene::changeEndLocation(QPoint point, QGraphicsView *mainView)
{
    startPoint = point;
    if (zoom != nullptr)
    {
        zoom->setVisible(false);
    }
    if (point.x() < 70 / x2x4)
        pixMap = mainView->grab(QRect(point.x(), point.y() - HEIGHT_ZOOM / x2x4,
                                      70 * 2 / x2x4, HEIGHT_ZOOM * 2 / x2x4));
    else
        pixMap = mainView->grab(QRect(point.x() - WEIGHT_ZOOM / x2x4, point.y() - HEIGHT_ZOOM / x2x4,
                                      WEIGHT_ZOOM * 2 / x2x4, HEIGHT_ZOOM * 2 / x2x4));
    pixMap = pixMap.scaled(pixMap.width() * x2x4, pixMap.height() * x2x4, Qt::KeepAspectRatioByExpanding);

    zoom->setPixmap(pixMap);
    zoom->setPos(point.x() + 5, point.y() + 5);
    zoom->setVisible(true);
}

void ZoomGraphSene::changeZoom()
{
    if (x2x4 == 2)
        x2x4 = 4;
    else
        x2x4 = 2;
}

void ZoomGraphSene::createNewPixMap()
{
    zoom = new QGraphicsPixmapItem();
    zoom->setZValue(100);
}

void ZoomGraphSene::addToScene(RedactScene *scenee)
{
    Q_UNUSED(scenee);
    int t;
    t = 't';
    //что?
}

void ZoomGraphSene::changeColor(QColor color)
{
    Q_UNUSED(color);
    std::string yu;
    yu = "чето да делает";
}


