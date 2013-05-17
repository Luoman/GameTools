#include        "RoomDisplay.h"
#include        "TextureArea.h"
#include        "Convert.hh"
#include        "ImageManager.h"

#include        <iostream>
#include        <QScrollBar>
#include        <string>

RoomDisplay::RoomDisplay(QWidget *parent, Ui::MainWindow *ui, MainWindow *mw) :
    QLabel(parent), m_pUi(ui), m_pMainWindow(mw)
{
    m_pCurrentBoxPos = QPoint(0, 0);
}

void        RoomDisplay::mouseMoveEvent(QMouseEvent *event)
{
    QPoint  mouseSensitivity(m_pMouseCoord.x() - event->globalX(), m_pMouseCoord.y() - event->globalY()), prevPos((event->pos().x()) / (RES * m_fScale), (event->pos().y()) / (RES * m_fScale));
    bool b_update = false;

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
        if (m_pSquarePos.x() >= m_iMapX)
            m_pSquarePos.setX(m_iMapX - 1);
        if (m_pSquarePos.y() >= m_iMapY)
            m_pSquarePos.setY(m_iMapY - 1);
        if (m_pUi->tabEdit->currentIndex() == 0 && m_bLeftButton == true)
        {
            std::cout << "ICI" << std::endl;
            updateImage((event->pos().x()) / (RES * m_fScale), (event->pos().y()) / (RES * m_fScale));
            m_pMainWindow->m_bSave = false;
        }
        b_update = true;
    }
    m_pMouseCoord.setX(event->globalX());
    m_pMouseCoord.setY(event->globalY());
    if (b_update == true)
        update();
}

void        RoomDisplay::mouseReleaseEvent(QMouseEvent *ev)
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

void        RoomDisplay::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        m_bRightButton = true;
        setCursor(Qt::ClosedHandCursor);
    }
    if (event->button() == Qt::LeftButton)
    {
        if (m_pUi->tabEdit->currentIndex() == 0)
        {
            std::cout << "ICI" << std::endl;
            m_pMainWindow->m_bSave = false;
            updateImage((event->pos().x()) / (RES * m_fScale), (event->pos().y()) / (RES * m_fScale));
            update();
        }
        else if (m_pUi->tabEdit->currentIndex() == 1)
        {
            m_pCurrentBoxPos = QPoint(event->pos().x() / (RES * m_fScale), event->pos().y() / (RES * m_fScale));
            std::cout << m_pCurrentBoxPos.x() << " : x - y : " << m_pCurrentBoxPos.y() << std::endl;
            m_pUi->currentPos->setText(QString(std::string("Current pos (" + intToString(m_pCurrentBoxPos.x())+ "," + intToString(m_pCurrentBoxPos.y()) + ")").c_str()));
            update();
            m_pMainWindow->displayInfosBox();
        }
        m_bLeftButton = true;
    }
}

void        RoomDisplay::wheelEvent(QWheelEvent *event)
{
    if(event->orientation() == Qt::Vertical && m_bCtrlPress == true)
    {
        m_fScale += (float)(event->delta()) / 240;
        std::cout << m_fScale << std::endl;
        if (m_fScale <= 0.5)
            m_fScale = 0.5;
        else if (m_fScale >= 5)
            m_fScale = 5;
        setGeometry(0, 0, ROOM_WIDTH * (RES * m_fScale), ROOM_HEIGHT * (RES * m_fScale));
        update();
    }
}

void        RoomDisplay::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Control)
        m_bCtrlPress = true;
    if (ev->key() == Qt::Key_I)
    {
        m_bIPress = !m_bIPress;
        update();
    }
    if (ev->key() == Qt::Key_Return)
        m_pMainWindow->apply();
}

void        RoomDisplay::keyReleaseEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Control)
        m_bCtrlPress = false;
}

void        RoomDisplay::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPen pen(QColor(0, 0, 0, 128), 2);
    int posX, posY = 0;
    QFont font = p.font();
    std::map<int, std::map<int, MapBox> > &boxes = m_pRoom->getBoxes();

    font.setPointSize ( 10 );

    p.setPen(pen);
    for (posX = (m_pArea->horizontalScrollBar()->value() / (RES * m_fScale)); posX < (m_pArea->horizontalScrollBar()->value() / (RES * m_fScale)) + (m_pArea->width() / (RES * m_fScale)) + 2 && posX < m_iMapX; ++posX)
        for (posY = (m_pArea->verticalScrollBar()->value() / (RES * m_fScale)); posY < (m_pArea->verticalScrollBar()->value() / (RES * m_fScale)) + (m_pArea->height() / (RES * m_fScale)) + 2 && posY < m_iMapY; ++posY)
        {
            //pen.setWidth(4);
            p.drawPixmap(QRect(posX * (RES * m_fScale), posY * (RES * m_fScale), (RES * m_fScale), (RES * m_fScale)), boxes[posX][posY].getFirstImage()->m_iImage);
            if (m_pRoom->getState(posX, posY) == "monster")
                p.drawPixmap(QRect(posX * (RES * m_fScale), posY * (RES * m_fScale), (RES * m_fScale), (RES * m_fScale)), ImageManager::getSingleton()->getMonsterImage(m_pRoom->getMonster(posX, posY).getName()));
            if (m_pUi->tabEdit->currentIndex() == 1)
            {
                if (m_pRoom->getState(posX, posY) == "object")
                    pen.setColor(QColor(0, 0, 255, 255));
                else if (m_pRoom->getState(posX, posY) == "monster")
                    pen.setColor(QColor(0, 255, 0, 255));
                else if (m_pRoom->getState(posX, posY) == "event")
                    pen.setColor(QColor(255, 0, 0, 255));
                else if (m_pRoom->getState(posX, posY) == "door")
                    pen.setColor(QColor(255, 0, 255, 255));
                p.setPen(pen);
                if (m_pRoom->getState(posX, posY) != "none")
                    p.drawRect(QRect(posX * (RES * m_fScale), posY * (RES * m_fScale), ((RES * m_fScale) - 1), ((RES * m_fScale)) - 1));
            }
        }
 //   pen.setWidth(2);
    pen.setColor(QColor(0, 0, 0, 128));
    p.setPen(pen);
    overview(p);
    p.setFont(font);
    if (m_bIPress == true)
    {
        p.fillRect(QRect(m_pArea->horizontalScrollBar()->value(), m_pArea->verticalScrollBar()->value(), 100, 40), QBrush(QColor(128, 128, 255, 200)));
        p.drawText(QPoint(m_pArea->horizontalScrollBar()->value() + 10, m_pArea->verticalScrollBar()->value() + 15), std::string("x : " + intToString(m_pSquarePos.x()) + " y : " + intToString(m_pSquarePos.y())).c_str());
        p.drawText(QPoint(m_pArea->horizontalScrollBar()->value() + 10, m_pArea->verticalScrollBar()->value() + 35), std::string("res : " + intToString(m_fScale * RES) + " x " + intToString(m_fScale * RES)).c_str());
    }
}

void            RoomDisplay::overview(QPainter &p)
{
    if (m_pUi->tabEdit->currentIndex() == 0)
    {
        TextureArea *tex = reinterpret_cast<TextureArea*>(m_pUi->textureArea_bis->widget());
        QPoint begin = tex->getBegin(), end = tex->getEnd();
        int tmpX = m_pReelPos.x(), tmpY = m_pReelPos.y(), tmpBX = begin.x(), tmpBY = begin.y();
        t_Image *img;

        if (m_pReelPos.x() >= 0 && m_pReelPos.x() >= 0)
            for (; tmpX < m_pReelPos.x() + end.x(); ++tmpX, ++tmpBX)
                for (tmpY =  m_pReelPos.y(), tmpBY = begin.y(); tmpY < m_pReelPos.y() + end.y(); ++tmpY, ++tmpBY)
                {
                    if (((MAX_COLUMN * tmpBY) + tmpBX) < (int)ImageManager::getSingleton()->getImages().size())
                        img = ImageManager::getSingleton()->getImageFromID((MAX_COLUMN * tmpBY) + tmpBX);
                    else
                        img = ImageManager::getSingleton()->getDefaultImage();
                    p.drawPixmap(QRect(tmpX * (RES * m_fScale), tmpY * (RES * m_fScale), (RES * m_fScale), (RES * m_fScale)), img->m_iImage);
                }
        p.drawRect(m_pReelPos.x() * (RES * m_fScale), m_pReelPos.y() * (RES * m_fScale), end.x() * (RES * m_fScale), end.y() * (RES * m_fScale));
    }
    else
    {
        QPen        pen(QColor(255, 255, 255, 255), 4);

        p.drawRect(m_pReelPos.x() * (RES * m_fScale), m_pReelPos.y() * (RES * m_fScale), ((RES * m_fScale) - 1), ((RES * m_fScale) - 1));
        p.setPen(pen);
        p.drawRect(m_pCurrentBoxPos.x() * (RES * m_fScale), m_pCurrentBoxPos.y() * (RES * m_fScale), ((RES * m_fScale) - 1), ((RES * m_fScale) - 1));
    }
}

void            RoomDisplay::updateImage(int posX, int posY)
{
    TextureArea *tex = reinterpret_cast<TextureArea*>(m_pUi->textureArea_bis->widget());
    QPoint begin = tex->getBegin(), end = tex->getEnd();
    int tmpX = posX, tmpY = posY, tmpBX = begin.x(), tmpBY = begin.y();
    t_Image *img;
    std::map<int, std::map<int, MapBox> > &boxes = m_pRoom->getBoxes();

    if (posX >= 0 && posY >= 0)
        for (; tmpX < posX + end.x(); ++tmpX, ++tmpBX)
            for (tmpY = posY, tmpBY = begin.y(); tmpY < posY + end.y(); ++tmpY, ++tmpBY)
            {
                if (((MAX_COLUMN * tmpBY) + tmpBX) < (int)ImageManager::getSingleton()->getImages().size())
                    img = ImageManager::getSingleton()->getImageFromID((MAX_COLUMN * tmpBY) + tmpBX);
                else
                    img = ImageManager::getSingleton()->getDefaultImage();
                if (tmpX < m_iMapX && tmpY < m_iMapY)
                        boxes[tmpX][tmpY].setFirstImage(img);
            }
}

void            RoomDisplay::initialize(QScrollArea *area, Room *room)
{
    m_pMouseCoord = QPoint(0, 0);
    m_pSquarePos = QPoint(0, 0);
    m_iMapX = ROOM_WIDTH;
    m_iMapY = ROOM_HEIGHT;
    m_pRoom = room;
    m_pArea = area;
    m_fScale = 0.5;
    m_bLeftButton = false;
    m_bRightButton = false;
    m_bCtrlPress = false;
    m_bIPress = true;
    setGeometry(0, 0, ROOM_WIDTH * (RES * m_fScale), ROOM_HEIGHT * (RES * m_fScale));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

void            RoomDisplay::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if (m_pUi->tabEdit->currentIndex() == 1 && ev->button() == Qt::LeftButton)
    {
        m_pCurrentBoxPos = QPoint(ev->pos().x() / (RES * m_fScale), ev->pos().y() / (RES * m_fScale));
        m_pUi->currentPos->setText(QString(std::string("Current pos (" + intToString(m_pCurrentBoxPos.x())+ "," + intToString(m_pCurrentBoxPos.y()) + ")").c_str()));
        update();
        m_pMainWindow->displayInfosBox();
    }
}

QPoint          &RoomDisplay::getCurrentBoxPos()
{
    return (m_pCurrentBoxPos);
}

Room            *RoomDisplay::getRoom() const
{
    return (m_pRoom);
}

