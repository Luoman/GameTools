#ifndef ROOMDISPLAY_H
#define ROOMDISPLAY_H

#include <QScrollArea>
#include <QLabel>

#include "Room.hh"
#include "MapBox.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

class RoomDisplay : public QLabel
{
    Q_OBJECT
public:
    explicit RoomDisplay(QWidget *parent = 0, Ui::MainWindow *ui = NULL, MainWindow *mw = NULL);
    

public:
    void            updateImage(int x, int y);
    void            initialize(QScrollArea *area, Room *room);
    void            overview(QPainter &);

signals:
    
public slots:
    

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
    QPoint          &getCurrentBoxPos();
    Room            *getRoom() const;

private:
    QScrollArea     *m_pArea;
    Ui::MainWindow  *m_pUi;
    MainWindow      *m_pMainWindow;
    QPoint          m_pMouseCoord, m_pSquarePos, m_pReelPos, m_pCurrentBoxPos;
    bool            m_bRightButton, m_bLeftButton, m_bCtrlPress, m_bIPress;
    std::map<int, std::map<int, MapBox> > m_mBoxes;
    int             m_iMapX, m_iMapY;
    float           m_fScale;
    Room            *m_pRoom;
};

#endif // ROOMDISPLAY_H
