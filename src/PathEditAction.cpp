#include <cmath>

#include "PathEditAction.h"

PathEditAction::PathEditAction(int tileWidth, int tileHeight, QObject* parent)
  : EditAction(tileWidth, tileHeight, parent)
{
}

QPair<QPointF, QPointF> PathEditAction::getSelection(const QPointF& start,
                                                     const QPointF& end)
{
  QPointF delta = end - start;
  QPair<QPointF, QPointF> ret;

  ret.first = quantizePoint(start, true);
  ret.second = end;

  if (fabs(delta.x()) < fabs(delta.y()))
    ret.second.setX(ret.first.x());
  else
    ret.second.setY(ret.first.y());

  ret.second = quantizePoint(ret.second, true);

  return ret;
}

EditAction::SelectionType PathEditAction::getSelectionType() const
{
  return EditAction::SelectionType::Line;
}
