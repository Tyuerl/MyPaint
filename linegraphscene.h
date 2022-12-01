#ifndef LINEGRAPHSCENE_H
#define LINEGRAPHSCENE_H

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QGraphicsLineItem>
#include "graphicsfigure.h"
class LineGraphScene : public GraphicsFigure
{
protected:
    double arcTangens;
    double pifagor;
    QString length;

public:
                                        LineGraphScene();
                                        LineGraphScene(QPoint point);
                                        ~LineGraphScene();
    virtual std::vector<QGraphicsItem*> getVectorNeedDelete() override;
    virtual void                        changeEndLocation(QPoint point) override;
    double                              getAlfa() {return arcTangens;}
    void                                addToScene(RedactScene *scenee = nullptr) override;
    void                                changeColor(QColor color) override;

// плохо конечно, что паблик, но писать еще 4 геттера не сильно хотелось
    QGraphicsLineItem *firstLine;
    QGraphicsLineItem *secondLine;
    QGraphicsLineItem *mainLine;
    QGraphicsTextItem *text;
    QPointF     size;
signals:
    void        signalTEmp(QPointF point);
private slots:
    //void        mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // LINEGRAPHSCENE_H
