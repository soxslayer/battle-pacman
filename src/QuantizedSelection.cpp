#include <cmath>

#include "QuantizedSelection.h"

QuantizedSelection::QuantizedSelection(Selection& wrapped,
                                       const QRectF& quantization,
                                       QObject* parent)
  : Selection(parent), mWrapped(wrapped), mQuantization(quantization)
{
  mWrapped.setParent(this);
}

void QuantizedSelection::setBegin(const QPointF& pt)
{
  mWrapped.setBegin(quantizePoint(pt));
}

void QuantizedSelection::setEnd(const QPointF& pt)
{
  mWrapped.setEnd(quantizePoint(pt));
}

void QuantizedSelection::draw(QPainter& painter) const
{
  mWrapped.draw(painter);
}

QPointF QuantizedSelection::quantizePoint(const QPointF& pt)
{
  return QPointF(floor(pt.x() / mQuantization.width()) * mQuantization.width()
                 + mQuantization.x(),
                 floor(pt.y() / mQuantization.height()) * mQuantization.height()
                 + mQuantization.y());
}
