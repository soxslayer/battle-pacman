#include <QPainter>

#include "Selection.h"

Selection::Selection(QObject* parent)
  : QObject(parent)
{
}

void Selection::draw(QPainter& painter) const
{
  painter.drawEllipse(getBegin(), 2, 2);
  painter.drawEllipse(getEnd(), 2, 2);
}
