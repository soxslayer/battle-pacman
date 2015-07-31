#include <cmath>

#include <QPainter>
#include <QPointF>

#include "LineSelection.h"

LineSelection::LineSelection(bool axisAligned, QObject* parent)
  : Selection(parent), mAxisAligned(axisAligned)
{
}

void LineSelection::setEnd(const QPointF& pt)
{
  QPointF newPt = pt;

  if (mAxisAligned) {
    QPointF delta = newPt - getBegin();

    if (fabs(delta.x()) < fabs(delta.y()))
      newPt.setX(getBegin().x());
    else
      newPt.setY(getBegin().y());
  }

  Selection::setEnd(newPt);
}

void LineSelection::draw(QPainter& painter) const
{
  painter.drawLine(getBegin(), getEnd());

  Selection::draw(painter);
}
