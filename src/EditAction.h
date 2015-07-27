#pragma once

#include <QObject>
#include <QPair>
#include <QPointF>

class EditAction : public QObject
{
  Q_OBJECT

public:
  enum class SelectionType
  {
    Line,
    Rect,
    Point
  };

  EditAction(int tileWidth, int tileHeight, QObject* parent = nullptr);

  virtual QPair<QPointF, QPointF> getSelection(const QPointF& start,
                                               const QPointF& end) = 0;
  virtual SelectionType getSelectionType() const = 0;

  QPointF quantizePoint(const QPointF& pt, bool center = false);

private:
  int mTileWidth;
  int mTileHeight;
};
