#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>

#include "MazeBuilder.h"

#include "Selection.h"
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

  void setEnableGrid(bool grid);
  void setSelection(Selection* selection);
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
  bool mSelectActive = false;
  Selection* mSelection = nullptr;

  void renderMaze();
};
