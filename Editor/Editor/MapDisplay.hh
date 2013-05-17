#ifndef MapDisplay_HH
#define MapDisplay_HH

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QScrollArea>
#include <QPoint>
#include <QMouseEvent>
#include <map>

#include "Map.hh"
#include "MapBox.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

class MapDisplay : public QLabel
{
    Q_OBJECT
public:
    explicit MapDisplay(QWidget *parent = 0, Ui::MainWindow *ui = NULL, MainWindow *mw = NULL);
    ~MapDisplay();

public:
    void            initialize(int width, int height, Map *map = NULL);
    void            displayRoom(Room *, QPainter &paint);

public:
    void            paintEvent(QPaintEvent *);
    void            mouseMoveEvent(QMouseEvent *);
    void            mouseReleaseEvent(QMouseEvent *ev);
    void            mousePressEvent(QMouseEvent *ev);
    void            wheelEvent(QWheelEvent *event);
    void            keyPressEvent(QKeyEvent *ev);
    void            keyReleaseEvent(QKeyEvent *ev);
    void            mouseDoubleClickEvent(QMouseEvent *);

public:
//  get
    Map             *getMap() const;

public:
// set

signals:
    
public slots:

private:
    Ui::MainWindow      *m_pUi;
    MainWindow          *m_pMainWindow;
    QScrollArea         *m_pArea;
    QPoint              m_pMouseCoord, m_pSquarePos, m_pReelPos;
    bool                m_bRightButton, m_bLeftButton, m_bCtrlPress, m_bIPress;
    std::map<int, std::map<int, MapBox> > m_mBoxes;
    int                 m_iMapX, m_iMapY;
    float               m_fScale;
    Map                 *m_pMap;
};

#endif // MapDisplay_H
