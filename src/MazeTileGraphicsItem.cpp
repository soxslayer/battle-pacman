#include <QPainter>

#include "MazeTileGraphicsItem.h"

MazeTileGraphicsItem::MazeTileGraphicsItem(const QPixmap& spriteSheet,
                                           const QRectF& tileInfo,
                                           QGraphicsItem* parent)
  : QGraphicsPixmapItem(parent)
{
  QPixmap sprite(tileInfo.width(), tileInfo.height());
  QPainter painter(&sprite);

  painter.drawPixmap(QRect(0, 0, tileInfo.width(), tileInfo.height()), spriteSheet, tileInfo);

  setPixmap(sprite);
  setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
}
