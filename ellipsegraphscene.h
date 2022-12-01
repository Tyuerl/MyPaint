#ifndef ELLIPSEGRAPHSCENE_H
#define ELLIPSEGRAPHSCENE_H
#include "graphicsfigure.h"

class EllipseGraphScene : public GraphicsFigure
{
public:
                                EllipseGraphScene();
                                EllipseGraphScene(QPoint point);
                                ~EllipseGraphScene();
    std::vector<QGraphicsItem*> getVectorNeedDelete() override;
    void                        changeEndLocation(QPoint point) override;
    void                        addToScene(RedactScene *scenee = nullptr) override;
    void                        changeColor(QColor color) override;
    QGraphicsEllipseItem*       ellipse;

private:
};

#endif // ELLIPSEGRAPHSCENE_H
