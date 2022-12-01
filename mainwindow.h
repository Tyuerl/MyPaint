#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "redactscene.h"
#include "linegraphscene.h"
#include "ellipsegraphscene.h"
#include "arrowgraphscene.h"
#include "zoomgraphsene.h"
#include "pengraphscene.h"
#include "textgraphscene.h"
#include <QWidget>
#include <QMainWindow>
#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>

#include <QTimer>
#
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
                                    MainWindow(QWidget *parent = nullptr);
                                    ~MainWindow();
    void                            drawLine();
private:
    Ui::MainWindow                  *ui;
    QTimer                          *timerPaint;
    RedactScene                     *scene;
    int                             stateButton = StateButton::NONE;
    int                             stateMouse = StateMouse::NONEPRESSED;
    ZoomGraphSene                   *zoom = nullptr;
    std::vector<GraphicsFigure *>   allItems;
    enum                            StateButton
    {
                                    NONE,
                                    LINE,
                                    ELLIPSE,
                                    TEXT,
                                    ARROW,
                                    ZOOM,
                                    PEN,
                                    CONTRAST
    };
    enum                            StateMouse
    {
                                    NONEPRESSED,
                                    PRESSED
    };

public slots:
    void    slotMousePress(QPointF point);
    void    slotMouseUp(QPointF point);
    void    slotMouseMove(QPointF point);
    void    slotKeyPress();
    void    contrast(QPoint point);
private slots:
    void    on_pushButton_4_clicked();
    void    on_pushButton_5_clicked();
    void    on_pushButton_clicked();
    void    on_pushButton_2_clicked();
    void    on_pushButton_3_clicked();
    void    on_pushButton_6_clicked();
    void    on_pushButton_7_clicked();
    void    on_pushButton_8_clicked();
    void    on_pushButton_9_clicked();
    void    on_pushButton_10_clicked();
    void    on_pushButton_11_clicked();
};
#endif // MAINWINDOW_H
