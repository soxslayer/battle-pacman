#pragma once

#include <QRectF>

#include "Selection.h"

class QuantizedSelection : public Selection
{
public:
  QuantizedSelection(Selection& wrapped, const QRectF& quantization,
                     QObject* parent = nullptr);

  virtual void setBegin(const QPointF& pt);
  virtual void setEnd(const QPointF& pt);

  virtual void draw(QPainter& painter) const;

private:
  Selection& mWrapped;
  QRectF mQuantization;

  QPointF quantizePoint(const QPointF& pt);
};
