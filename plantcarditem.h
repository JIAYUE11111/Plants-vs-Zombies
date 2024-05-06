#ifndef PLANTCARDITEM_H
#define PLANTCARDITEM_H

#include <QtWidgets>
#include "mouseeventspixmapitem.h"

class Plant;

class TooltipItem: public QGraphicsRectItem
{
public:
    TooltipItem(const QString &text);
    void setText(const QString &text);
private:
    QGraphicsTextItem *tooltipText;
};

class PlantCardItem: public MouseEventsPixmapItem
{
    Q_OBJECT

public:
    PlantCardItem(const Plant *plant, bool smaller = false);
    void setChecked(bool newchecked);
    bool isChecked() const;

    void setPercent(double value);
    void updatePixmap();
private:
    bool checked;
    double percent;
    int lowestHeight, highestHeight;
    QGraphicsPixmapItem *overlayImage;
    QPixmap checkedImage, uncheckedImage;
};


#endif // PLANTCARDITEM_H
