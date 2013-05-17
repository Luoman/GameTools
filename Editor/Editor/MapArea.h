#ifndef MAPAREA_H
#define MAPAREA_H

#include <QScrollArea>
#include <QWidget>

class MapArea : public QScrollArea
{
public:
    explicit MapArea(QWidget *parent);
};

#endif // MAPAREA_H
