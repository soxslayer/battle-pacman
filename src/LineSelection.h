#pragma once

#include "Selection.h"

class LineSelection : public Selection
{
public:
  LineSelection(bool axisAligned = false, QObject* parent = nullptr);

  virtual void setEnd(const QPointF& pt);

  virtual void draw(QPainter& painter) const;

private:
  bool mAxisAligned;
};
