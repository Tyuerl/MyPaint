#ifndef ARROWGRAPHSCENE_H
#define ARROWGRAPHSCENE_H
#include "linegraphscene.h"

class ArrowGraphScene: public LineGraphScene
{
public:
                                ArrowGraphScene();
                                ArrowGraphScene(QPoint point);
                                ~ArrowGraphScene();
    void                        changeEndLocation(QPoint point) override;
    std::vector<QGraphicsItem*> getVectorNeedDelete() override;
    void                        addToScene(RedactScene *scenee = nullptr) override;
    void                        changeColor(QColor color) override;
    QGraphicsLineItem           *thirdLine;
    QGraphicsLineItem           *fourthLine;
};

#endif // ARROWGRAPHSCENE_H
