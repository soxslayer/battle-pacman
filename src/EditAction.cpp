#include "EditAction.h"


EditAction::EditAction(int tileWidth, int tileHeight, QObject* parent)
  : QObject(parent),
    mTileWidth(tileWidth), mTileHeight(tileHeight)
{
}

QPointF EditAction::quantizePoint(const QPointF& pt, bool center)
{
  int xOffset = center ? mTileWidth / 2 : 0;
  int yOffset = center ? mTileHeight / 2 : 0;

  return QPointF(((int)pt.x() / mTileWidth) * mTileWidth + xOffset,
                 ((int)pt.y() / mTileHeight) * mTileHeight + yOffset);
}
