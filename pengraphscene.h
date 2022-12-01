#ifndef PENGRAPHSCENE_H
#define PENGRAPHSCENE_H
#include "graphicsfigure.h"

class PenGraphScene : public GraphicsFigure
{
public:
                                PenGraphScene();
                                PenGraphScene(QPoint point);
                                PenGraphScene(QPoint point, RedactScene *scenee);
                                ~PenGraphScene();
    std::vector<QGraphicsItem*> getVectorNeedDelete() override;
    void                        changeEndLocation(QPoint point) override;
    void                        addToScene(RedactScene *scenee = nullptr) override;
    void                        changeColor(QColor color) override;
    QGraphicsEllipseItem*       ellipse;
private:
    std::vector<QGraphicsItem*> lines;
    QPoint                      betweenStartEndPoint;
    RedactScene                 *scene;
};

#endif // PENGRAPHSCENE_H
