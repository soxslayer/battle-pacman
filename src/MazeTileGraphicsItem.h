#pragma once

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QRectF>

class MazeTileGraphicsItem : public QGraphicsPixmapItem
{
public:
  MazeTileGraphicsItem(const QPixmap& spriteSheet, const QRectF& tileInfo,
                       QGraphicsItem* parent = nullptr);
};
