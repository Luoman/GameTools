#ifndef TEXTUREAREA_H
#define TEXTUREAREA_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <vector>

#include "mainwindow.h"
#include "ui_mainwindow.h"

# define    MAX_COLUMN      3

class TextureArea : public QLabel
{
    Q_OBJECT
public:
    explicit TextureArea(QWidget *parent = 0, Ui::MainWindow *mainWndow = NULL);
    
public:
    void                paintEvent(QPaintEvent *);
    void                mouseMoveEvent(QMouseEvent *);
    void                mouseReleaseEvent(QMouseEvent *ev);
    void                mousePressEvent(QMouseEvent *ev);

public:
    void                getBeginEndPoints();

public:
    const QPoint        &getBegin() const;
    const QPoint        &getEnd() const;

signals:
    
public slots:
    
private:
    Ui::MainWindow      *m_pMainWindow;
    bool                m_bLeftButton;
    bool                m_pUpdate;
    float                 m_iScale;
    QPoint              m_pEndPos, m_pFirstPos, m_pBegin, m_pEnd;
};

#endif // TEXTUREAREA_H
