#include        "MapDisplay.hh"

#include        "TextureArea.h"
#include        "Convert.hh"
#include        "ImageManager.h"

#include        <iostream>
#include        <QScrollBar>
#include        <string>

MapDisplay::MapDisplay(QWidget *parent, Ui::MainWindow *ui, MainWindow *mw) :
    QLabel(parent), m_pUi(ui), m_pMainWindow(mw)
{
    m_pMap = NULL;
}

MapDisplay::~MapDisplay()
{
    if (m_pMap != NULL)
        delete m_pMap;
}

void            MapDisplay::mouseMoveEvent(QMouseEvent *event)
{
    QPoint      mouseSensitivity(m_pMouseCoord.x() - event->globalX(), m_pMouseCoord.y() - event->globalY()), prevPos((event->pos().x()) / (RES * m_fScale), (event->pos().y()) / (RES * m_fScale));
    bool        b_update = false;

    m_pReelPos = QPoint((event->pos().x()) / (RES * m_fScale), (event->pos().y()) / (RES * m_fScale));
    mouseSensitivity *= 2;
    if (m_bRightButton == true)
    {
        if (m_pMouseCoord.y() != 0)
        {
            m_pArea->verticalScrollBar()->setValue(m_pArea->verticalScrollBar()->value() + mouseSensitivity.y());
            b_update = true;
        }
        if (m_pMouseCoord.x() != 0)
        {
            m_pArea->horizontalScrollBar()->setValue(m_pArea->horizontalScrollBar()->value() + mouseSensitivity.x());
            b_update = true;
        }
    }
    if (prevPos.x() != m_pSquarePos.x() || prevPos.y() != m_pSquarePos.y())
    {
        m_pSquarePos.setY(prevPos.y());
        m_pSquarePos.setX(prevPos.x());
        if (m_pSquarePos.x() < 0)
            m_pSquarePos.setX(0);
        if (m_pSquarePos.y() < 0)
            m_pSquarePos.setY(0);
        if (m_pSquarePos.x() >= m_pMap->getWidth())
            m_pSquarePos.setX(m_pMap->getWidth() - 1);
        if (m_pSquarePos.y() >= m_pMap->getHeight())
            m_pSquarePos.setY(m_pMap->getHeight() - 1);
        b_update = true;
    }
    m_pMouseCoord.setX(event->globalX());
    m_pMouseCoord.setY(event->globalY());
    if (b_update == true)
        update();
}

void            MapDisplay::mouseReleaseEvent(QMouseEvent *ev)
{
    m_pMouseCoord.setX(0);
    m_pMouseCoord.setY(0);
    if (ev->button() == Qt::RightButton)
    {
        m_bRightButton = false;
        setCursor(Qt::CrossCursor);
    }
    if (ev->button() == Qt::LeftButton)
        m_bLeftButton = false;
}

void            MapDisplay::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        m_bRightButton = true;
        setCursor(Qt::ClosedHandCursor);
    }
    if (event->button() == Qt::LeftButton)
    {
        if (m_pUi->tabEdit->currentIndex() == 0)
            update();
        m_bLeftButton = true;
    }
}

void            MapDisplay::wheelEvent(QWheelEvent *event)
{
    if (event->orientation() == Qt::Vertical && m_bCtrlPress == true)
    {
        m_fScale += (float)(event->delta()) / 240;
        std::cout << m_fScale << std::endl;
        if (m_fScale <= 0.5)
            m_fScale = 0.5;
        else if (m_fScale >= 5)
            m_fScale = 5;
        setGeometry(0, 0, m_pMap->getWidth() * (RES * m_fScale), m_pMap->getHeight() * (RES * m_fScale));
        update();
    }
}

void            MapDisplay::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Control)
        m_bCtrlPress = true;
    if (ev->key() == Qt::Key_I)
    {
        m_bIPress = !m_bIPress;
        update();
    }
}

void            MapDisplay::keyReleaseEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Control)
        m_bCtrlPress = false;
}

void            MapDisplay::paintEvent(QPaintEvent *)
{
    QPainter    p(this);
    QPen        pen(QColor(0, 0, 0, 128), 2);
    QFont       font = p.font();
    std::map<int, std::map<int, Room *> >::iterator itX;
    std::map<int, Room *>::iterator     itY;

    font.setPointSize ( 10 );
    for (itX = m_pMap->getRooms().begin(); itX != m_pMap->getRooms().end(); ++itX)
        for (itY = itX->second.begin(); itY != itX->second.end(); ++itY)
            if (itY->second != NULL)
                displayRoom(itY->second, p);
    p.setPen(pen);
    p.setFont(font);
    if (m_bIPress == true)
    {
        p.fillRect(QRect(m_pArea->horizontalScrollBar()->value(), m_pArea->verticalScrollBar()->value(), 120, 40), QBrush(QColor(128, 128, 255, 200)));
        p.drawText(QPoint(m_pArea->horizontalScrollBar()->value() + 10, m_pArea->verticalScrollBar()->value() + 15), std::string("room - x : " + intToString(m_pSquarePos.x() / ROOM_WIDTH) + " y : " + intToString(m_pSquarePos.y() / ROOM_HEIGHT)).c_str());
        p.drawText(QPoint(m_pArea->horizontalScrollBar()->value() + 10, m_pArea->verticalScrollBar()->value() + 35), std::string("res : " + intToString(m_fScale * RES) + " x " + intToString(m_fScale * RES)).c_str());
    }
}

void            MapDisplay::displayRoom(Room *room, QPainter &paint)
{
    int         posX = room->getPosX(), posY = room->getPosY(), x = 0, y = 0;
    QPen        pen(QColor(255, 255, 255, 255), 5);

    paint.setPen(pen);
    paint.drawRect(posX * (RES * m_fScale) * ROOM_WIDTH, posY * (RES * m_fScale) * ROOM_HEIGHT, ROOM_WIDTH * RES * m_fScale, ROOM_HEIGHT * RES * m_fScale);
    for (x = 0; x < ROOM_WIDTH; ++x)
        for (y = 0; y < ROOM_HEIGHT; ++y)
        {
            paint.drawPixmap(QRect(x * (RES * m_fScale) + (posX * ROOM_WIDTH * (RES * m_fScale)), y * (RES * m_fScale) + (posY * ROOM_HEIGHT * (RES * m_fScale)), RES * m_fScale, RES * m_fScale), room->getBoxes()[x][y].getFirstImage()->m_iImage);
            if (room->getState(x, y) == "monster")
                paint.drawPixmap(QRect(x * (RES * m_fScale) + (posX * ROOM_WIDTH * (RES * m_fScale)), y * (RES * m_fScale) + (posY * ROOM_HEIGHT * (RES * m_fScale)), (RES * m_fScale), (RES * m_fScale)), ImageManager::getSingleton()->getMonsterImage(room->getMonster(x, y).getName()));
        }
}

void            MapDisplay::initialize(int width, int height, Map *map)
{
    m_pMouseCoord = QPoint(0, 0);
    m_pSquarePos = QPoint(0, 0);
    if (m_pMap != NULL)
        delete m_pMap;
    if (map == NULL)
    {
        m_pMap = new Map;
        m_pMap->createMap(width, height);
    }
    else
        m_pMap = map;
    m_fScale = 0.5;
    m_pArea = m_pUi->mapArea;
    m_bLeftButton = false;
    m_bRightButton = false;
    m_bCtrlPress = false;
    m_bIPress = true;
    setFocusPolicy(Qt::StrongFocus);
    setGeometry(0, 0, width * (RES * m_fScale), height * (RES * m_fScale));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMouseTracking(true);
}

void            MapDisplay::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_pMainWindow->createTab(m_pMap->getRoom((int)(event->pos().x() / (ROOM_WIDTH * RES * m_fScale)), (int)(event->pos().y() / (ROOM_HEIGHT * RES * m_fScale))));
        std::cout << (int)(event->pos().x() / (ROOM_WIDTH * RES * m_fScale))  << " : x - y : " << (int)(event->pos().y() / (ROOM_HEIGHT * RES * m_fScale)) << std::endl;
    }
}

Map             *MapDisplay::getMap() const
{
    return (m_pMap);
}
