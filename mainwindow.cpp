#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMatrix>
#include <QPalette>
#include <QTextEdit>
#include <QGraphicsRectItem>
namespace{
    auto imgBackround = QImage("backgroundTachki.jpg");
    auto imgDefault = imgBackround;
    QImage invertimg = imgBackround;
    int count = 0;
    QPoint mainPoint;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new RedactScene();
    scene->stateMouse = &stateMouse;
    scene->stateButton = &stateButton;
    QBrush background = QBrush(imgBackround);
    ui->graphicsView->setBackgroundBrush(background);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали
    //ui->graphicsView-> добваить антиалазинг
    scene->setSceneRect(ui->graphicsView->rect());
    scene->sceneRect().size().toSize();
    ui->graphicsView->setScene(scene);
    connect(scene, &RedactScene::signalMousePressCoordinate,
            this, &MainWindow::slotMousePress);
    connect(scene, &RedactScene::signalMouseReleaseCoordinate,
            this, &MainWindow::slotMouseUp);
    connect(scene, &RedactScene::signalMouseMoveCoordinate,
            this, &MainWindow::slotMouseMove);
    connect(scene, &RedactScene::signalKeyPress,
            this, &MainWindow::slotKeyPress);
    ui->graphicsView->setMouseTracking(true);
}

QImage ChangeContrast(QImage image, int contrast = 100)
{
   auto newImage = image.copy();
   QRgb c = 0;
   int r; int g; int b;
   for (int i = 0; i < newImage.width(); ++i)
   {
       for (int j = 0; j < newImage.height(); ++j)
       {
            c = QRgb(newImage.pixel(i,j));
            QColor col(c);
            col.getRgb(&r,&g,&b);
            r = qBound<int>(0, int(( r - 127 ) * contrast / 100 ) + 127, 255 );
            g = qBound<int>(0, int(( g - 127 ) * contrast / 100 ) + 127, 255 );
            b = qBound<int>(0, int(( b - 127 ) * contrast / 100 ) + 127, 255 );
           newImage.setPixel(i,j,qRgb(r,g,b));
       }
   }
   return(newImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotMousePress(QPointF point)
{

    stateMouse = StateMouse::PRESSED;
    if (allItems.size() > 0 && allItems.back()->getType() == TEXT)
        ((TextGraphScene *)(allItems.back()))->deleteRect();
    if (stateButton == StateButton::NONE)
        return;
    mainPoint = point.toPoint();
    switch (stateButton) {
    case (StateButton::LINE):
        allItems.push_back(new LineGraphScene(point.toPoint()));
        break;
    case (StateButton::ELLIPSE):
        allItems.push_back(new EllipseGraphScene(point.toPoint()));
        break;
    case (StateButton::ARROW):
        allItems.push_back(new ArrowGraphScene(point.toPoint()));
        break;
    case(StateButton::PEN):
        allItems.push_back(new PenGraphScene(point.toPoint(), scene));
        break;
    case(StateButton::ZOOM):
    {
        zoom->changeZoom();
        zoom->changeEndLocation(point.toPoint(), ui->graphicsView);
        break;
    }
    case(StateButton::TEXT):
        scene->text.clear();
        allItems.push_back(new TextGraphScene(point.toPoint()));
        break;
    case(StateButton::CONTRAST):
        //
    default:
        return;
    }
    if (stateButton != ZOOM)
        allItems.back()->addToScene(scene);
    return;
}


void MainWindow::slotMouseUp(QPointF point)
{
    Q_UNUSED(point);

    stateMouse = StateMouse::NONEPRESSED;
}

//
//
//метод для высчитывания значения для изменения контрастности
void MainWindow::contrast(QPoint point) // height 600 weight 800
{
    double contr = point.x() - 400 + 100;
    if (contr < 100 && contr > 0)
        contr =  contr * 0.2 + 80 ;
    if (contr <= 0)
        contr = point.x() * 0.2;
    imgBackround = ChangeContrast(imgDefault, contr);
    ui->graphicsView->setBackgroundBrush(QBrush(imgBackround));
}


void MainWindow::slotMouseMove(QPointF point)
{
    if (stateButton == StateButton::CONTRAST && stateMouse == StateMouse::PRESSED)
        contrast(point.toPoint());
    else if (stateButton == StateButton::ZOOM)
    {
        zoom->changeEndLocation(point.toPoint(), ui->graphicsView);
    }
    else if (stateMouse == StateMouse::PRESSED
            && stateButton != StateButton::NONE
            && allItems.size() != 0)
    {
        allItems.back()->changeEndLocation(point.toPoint());
    }
}


//
// изменение написанного текста
//

void MainWindow::slotKeyPress()
{
    if (stateButton == StateButton::TEXT)
        ((TextGraphScene *)(allItems.back()))->text->setPlainText(scene->text);
    else
    {
        ((TextGraphScene *)(allItems.back()))->deleteRect();
    }
}


// кнопка очистки
void MainWindow::on_pushButton_4_clicked()
{
    if (stateButton == ZOOM)
        zoom->setVisible(false);
    if (allItems.empty())
        return;
    allItems.clear();
    stateButton = NONE;
    scene->clear();
    scene->update();
    if (zoom)
        zoom->createNewPixMap();
}

//убираем последнее действие
void MainWindow::on_pushButton_5_clicked()
{
    if (stateButton == ZOOM)
        zoom->setVisible(false);
    if (allItems.empty())
        return ;
    auto items = allItems.back()->getVectorNeedDelete();
    for (size_t i = 0; i < items.size(); i++)
    {
        scene->removeItem(items[i]);
    }
    allItems.pop_back();
    scene->update();
}

// добавить линию
void MainWindow::on_pushButton_clicked() // clicked line
{
    if (allItems.size() > 0 && allItems.back()->getType() == TEXT)
        ((TextGraphScene *)(allItems.back()))->deleteRect();
    if (stateButton == ZOOM)
        zoom->setVisible(false);
    stateButton = LINE;
}

//добавить зум
void MainWindow::on_pushButton_2_clicked()
{
    if (allItems.size() > 0 && allItems.back()->getType() == TEXT)
        ((TextGraphScene *)(allItems.back()))->deleteRect();
    if (stateButton == ZOOM)
        zoom->setVisible(false);
    stateButton = ELLIPSE;
}

//добавить стрелку
void MainWindow::on_pushButton_3_clicked()
{
    if (allItems.size() > 0 && allItems.back()->getType() == TEXT)
        ((TextGraphScene *)(allItems.back()))->deleteRect();
    if (stateButton == ZOOM)
        zoom->setVisible(false);
    stateButton = ARROW;
}

// зум
void MainWindow::on_pushButton_6_clicked()
{
    if (allItems.size() > 0 && allItems.back()->getType() == TEXT)
        ((TextGraphScene *)(allItems.back()))->deleteRect();
    stateButton = ZOOM;
    if (zoom == Q_NULLPTR)
    {
        zoom = new ZoomGraphSene();
        scene->addItem(zoom->zoom);
    }
    zoom->zoom->setVisible(true);

}

// карандаш
void MainWindow::on_pushButton_7_clicked()
{
   if (stateButton == ZOOM)
       zoom->setVisible(false);
   if (allItems.size() > 0 && allItems.back()->getType() == TEXT)
       ((TextGraphScene *)(allItems.back()))->deleteRect();
   stateButton = PEN;

}


//текст
void MainWindow::on_pushButton_8_clicked()
{
    if (stateButton == ZOOM)
        zoom->setVisible(false);
    if (allItems.size() > 0 && allItems.back()->getType() == TEXT)
        ((TextGraphScene *)(allItems.back()))->deleteRect();
    stateButton = TEXT;
}

// инвертирование
void MainWindow::on_pushButton_9_clicked()
{
    if (++count % 2 == 1)
        for(std::size_t i = 0; i < allItems.size(); i++)
            allItems[i]->changeColor(Qt::white);
    else
        for(std::size_t i = 0; i < allItems.size(); i++)
            allItems[i]->changeColor(Qt::black);
    imgBackround.invertPixels();
    ui->graphicsView->setBackgroundBrush(QBrush(imgBackround));
}

// контраст
void MainWindow::on_pushButton_10_clicked()
{
    if (stateButton == ZOOM)
        zoom->setVisible(false);
    stateButton = CONTRAST;
    /*imgBackround = ChangeContrast(imgBackround, ui->textEdit->toPlainText().toInt());
    ui->graphicsView->setBackgroundBrush(QBrush(imgBackround)); */
}


// восстановить изначальный бекграунд
void MainWindow::on_pushButton_11_clicked()
{
    if (stateButton == ZOOM)
        zoom->setVisible(false);
    imgBackround = imgDefault;
    ui->graphicsView->setBackgroundBrush(imgDefault);
}
