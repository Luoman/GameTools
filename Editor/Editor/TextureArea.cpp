#include "ImageManager.h"
#include "TextureArea.h"


#include <iostream>

TextureArea::TextureArea(QWidget *parent, Ui::MainWindow *mainWindow) :
    QLabel(parent), m_pMainWindow(mainWindow), m_iScale(1.5)
{
    m_pBegin = QPoint(0, 0);
    m_pEnd = QPoint(1, 1);
    setGeometry(0, 0, 192, ((((RES * m_iScale) * m_iScale) * ImageManager::getSingleton()->getImages().size()) / MAX_COLUMN) + (RES * m_iScale));
    setMouseTracking(false);
}

void TextureArea::mouseMoveEvent(QMouseEvent *event)
{
    m_pEndPos.setY((event->pos().y()) / (RES * m_iScale));
    m_pEndPos.setX((event->pos().x()) / (RES * m_iScale));
    getBeginEndPoints();
    update();
}

void TextureArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_pEndPos.setX((event->pos().x()) / (RES * m_iScale));
        m_pEndPos.setY((event->pos().y()) / (RES * m_iScale));
        getBeginEndPoints();
        update();
    }
}

void TextureArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_pFirstPos.setX((event->pos().x()) / (RES * m_iScale));
        m_pFirstPos.setY((event->pos().y()) / (RES * m_iScale));
    }
}

void TextureArea::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPen pen(QColor(0, 0, 0), 2);
    int xPos, yPos = -1;
    t_Image *img;

    p.setPen(pen);
    for (xPos = 0; xPos < ImageManager::getSingleton()->getImages().size(); xPos++)
    {
        if (xPos % MAX_COLUMN == 0)
            yPos++;
        img = ImageManager::getSingleton()->getImageFromID(xPos);
        p.drawPixmap(QRect((xPos % MAX_COLUMN) * (RES * m_iScale), yPos * (RES * m_iScale), (RES * m_iScale), (RES * m_iScale)), img->m_iImage);
    }
    p.drawRect(m_pBegin.x() * (RES * m_iScale), m_pBegin.y() * (RES * m_iScale), m_pEnd.x() * (RES * m_iScale), m_pEnd.y() * (RES * m_iScale));
}

void TextureArea::getBeginEndPoints()
{
    if (m_pFirstPos.x() <= m_pEndPos.x())
    {
        m_pBegin.setX(m_pFirstPos.x());
        if (m_pFirstPos.x() == m_pEndPos.x())
            m_pEnd.setX(1);
        else
            m_pEnd.setX(m_pEndPos.x() - m_pFirstPos.x() + 1);
    }
    else
    {
        m_pBegin.setX(m_pEndPos.x());
        m_pEnd.setX(m_pFirstPos.x() - m_pEndPos.x() + 1);
    }
    if (m_pFirstPos.y() <= m_pEndPos.y())
    {
        m_pBegin.setY(m_pFirstPos.y());
        if (m_pFirstPos.y() == m_pEndPos.y())
            m_pEnd.setY(1);
        else
            m_pEnd.setY(m_pEndPos.y() - m_pFirstPos.y() + 1);
    }
    else
    {
        m_pBegin.setY(m_pEndPos.y());
        m_pEnd.setY(m_pFirstPos.y() - m_pEndPos.y() + 1);
    }
}

const QPoint &TextureArea::getBegin() const
{
    return (m_pBegin);
}

const QPoint &TextureArea::getEnd() const
{
    return (m_pEnd);
}
