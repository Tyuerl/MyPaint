#ifndef ZOOMGRAPHSENE_H
#define ZOOMGRAPHSENE_H
#include "graphicsfigure.h"

class ZoomGraphSene : public GraphicsFigure
{
private:
    QPixmap pixMap;
    int count;
    int x2x4 = 2;

public:
                                ZoomGraphSene();
                                ZoomGraphSene(QPoint point);
                                ~ZoomGraphSene();
    std::vector<QGraphicsItem*> getVectorNeedDelete() override;
    void                        changeEndLocation(QPoint point, QGraphicsView *mainView);
    void                        setVisible(bool flag) {zoom->setVisible(flag);};
    void                        changeZoom();
    void                        createNewPixMap();
    void addToScene(RedactScene *scenee = nullptr) override;
    QGraphicsPixmapItem         *zoom;
    void changeColor(QColor color) override;
};

#endif // ZOOMGRAPHSENE_H
