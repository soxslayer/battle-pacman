#pragma once

#include <QPair>
#include <QPointF>

#include "EditAction.h"

class PathEditAction : public EditAction
{
public:
  PathEditAction(int tileWidth, int tileHeight, QObject* parent = nullptr);

  virtual QPair<QPointF, QPointF> getSelection(const QPointF& start,
                                               const QPointF& end);
  virtual SelectionType getSelectionType() const;
};
