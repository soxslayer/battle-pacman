#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QPointF>

#include "MazeBuilder.h"

#include "EditAction.h"
#include "SpriteSheet.h"

class QMouseEvent;
class QPainter;
class QWidget;
class QGraphicsScene;

class MazeEditWidget : public QGraphicsView
{
  Q_OBJECT

public:
  MazeEditWidget(QWidget* parent = nullptr);
  ~MazeEditWidget();

  void setEnableGrid(bool grid);
  void setEditAction(EditAction* editAction);
  int tileWidth() const { return mSpriteSheet.tileInfo().width(); }
  int tileHeight() const { return mSpriteSheet.tileInfo().height(); }

protected:
  virtual void drawForeground(QPainter* painter, const QRectF& rect);
  virtual void mousePressEvent(QMouseEvent* event);
  virtual void mouseMoveEvent(QMouseEvent* event);
  virtual void mouseReleaseEvent(QMouseEvent* event);

private:
  QGraphicsScene* mScene;
  MazeBuilder mMazeBuilder;
  SpriteSheet mSpriteSheet;
  bool mGrid = false;
  QPointF mSelectBegin;
  QPointF mSelectEnd;
  bool mSelectActive = false;
  EditAction* mEditAction = nullptr;

  void renderMaze();
};
