#pragma once

#include <QObject>
#include <QPointF>

class QPainter;

class Selection : public QObject
{
  Q_OBJECT

public:
  Selection(QObject* parent = nullptr);

  virtual void setBegin(const QPointF& pt) { mBegin = pt; }
  virtual void setEnd(const QPointF& pt) { mEnd = pt; }

  const QPointF& getBegin() const { return mBegin; }
  const QPointF& getEnd() const { return mEnd; }

  virtual void draw(QPainter& painter) const;

private:
  QPointF mBegin;
  QPointF mEnd;
};
