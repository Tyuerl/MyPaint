#ifndef TEXTGRAPHSCENE_H
#define TEXTGRAPHSCENE_H
#include "graphicsfigure.h"
#include "redactscene.h"
class TextGraphScene: public GraphicsFigure
{
public:
                                TextGraphScene();
                                TextGraphScene(QPoint point);
                                ~TextGraphScene();
    std::vector<QGraphicsItem*> getVectorNeedDelete() override;
    void                        changeEndLocation(QPoint point) override;
    void                        deleteRect();
    void                        addToScene(RedactScene *scenee = nullptr) override;
    void                        changeColor(QColor color) override;
    bool                        flag = true;
    QGraphicsTextItem *         text;
    QGraphicsRectItem *         rect;
    RedactScene                 *scene;
};

#endif // TEXTGRAPHSCENE_H
