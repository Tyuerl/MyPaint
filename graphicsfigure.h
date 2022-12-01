#ifndef GRAPHICSFIGURE_H
#define GRAPHICSFIGURE_H

#include <QPainter>
#include <QWidget>
#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <cmath>
#include "redactscene.h"
class GraphicsFigure : public QObject
{

protected:
    std::vector<QGraphicsItem*> Items;
    QPoint                      startPoint;
    QPoint                      endPoint;
    int                         typeFigure = TypeFigure::NONE;

public:
    // пиксели в миллиметры
    const double    PX_TO_MM = 0.2636;
                    GraphicsFigure();
                    GraphicsFigure(QPoint point);
                    GraphicsFigure(int typee);
                    ~GraphicsFigure();
    int             getType() {return typeFigure;}
    // для того, чтобы потом двигать фигуру, если будет надо
    void            moveFigure(QPoint point);
    // изменение фигуры
    virtual void    changeEndLocation(QPoint point);
    // получение вектора элементом QGraphicItem для удаления их со сцены
    virtual         std::vector<QGraphicsItem*> getVectorNeedDelete();
    // добавление на сцену
    virtual void    addToScene(RedactScene *scenee = nullptr) = 0;
    // изменение цвета фигуры
    virtual void    changeColor(QColor color) = 0;
    enum            TypeFigure
    {

                    NONE,
                    LINE,
                    ELLIPSE,
                    TEXT,
                    ARROW,
                    ZOOM,
                    PEN
    };
};

#endif // GRAPHICSFIGURE_H
