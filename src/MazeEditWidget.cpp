#include <QColor>
#include <QMouseEvent>
#include <QPaintEngine>
#include <QPen>
#include <QRectF>

#include "MazeEditWidget.h"

#include "Maze.h"
#include "MazeTileGraphicsItem.h"

MazeEditWidget::MazeEditWidget(QWidget* parent)
  : QGraphicsView(parent),
    mSpriteSheet(SpriteSheet::loadYaml("original_spritesheet.yaml"))
{
  mScene = new QGraphicsScene(this);

  setScene(mScene);

  mScene->setBackgroundBrush(Qt::black);

  renderMaze();
}

void MazeEditWidget::setEnableGrid(bool grid)
{
  mGrid = grid;
  viewport()->update();
}

void MazeEditWidget::setSelection(Selection* selection)
{
  if (mSelection)
    mSelection->deleteLater();

  mSelection = selection;
  mSelection->setParent(this);
}

void MazeEditWidget::drawForeground(QPainter* painter, const QRectF& rect)
{
  if (mGrid) {
    QPen pen(Qt::DotLine);
    pen.setColor(QColor(255, 255, 255, 64));

    painter->setPen(pen);

    int tileWidth = mSpriteSheet.tileInfo().width();
    int tileHeight = mSpriteSheet.tileInfo().height();

    for (int x = (int)(rect.left() / tileWidth) * tileWidth; x < rect.right();
         x += tileWidth) {
      painter->drawLine(x, rect.top(), x, rect.bottom());
      painter->drawLine(x + tileWidth - 1, rect.top(),
                        x + tileWidth - 1, rect.bottom());
    }

    for (int y = (int)(rect.top() / tileHeight) * tileHeight; y < rect.bottom();
         y += tileHeight) {
      painter->drawLine(rect.left(), y, rect.right(), y);
      painter->drawLine(rect.left(), y + tileHeight - 1,
                        rect.right(), y + tileHeight - 1);
    }
  }

  if (mSelectActive && mSelection) {
    painter->setPen(Qt::blue);
    painter->setBrush(Qt::blue);

    mSelection->draw(*painter);
  }
}

void MazeEditWidget::renderMaze()
{
  Maze& maze = mMazeBuilder.getMaze();
  int mazeWidth = maze.width();
  int mazeHeight = maze.height();
  const QRectF& tileInfo = mSpriteSheet.tileInfo();
  int tileWidth = tileInfo.width();
  int tileHeight = tileInfo.height();

  for (int y = 0; y < mazeHeight; ++y) {
    for (int x = 0; x < mazeWidth; ++x) {
      SpriteSheet::MazeSprite sprite = maze.getWallSprite(x, y);

      if (sprite != SpriteSheet::MazeSprite::None) {
        QGraphicsItem* item = new MazeTileGraphicsItem(mSpriteSheet.sheetImage(),
                                                 mSpriteSheet.getSpriteInfo(sprite));
        item->setPos(x * tileWidth, y * tileHeight);
        mScene->addItem(item);
      }
    }
  }
}

void MazeEditWidget::mousePressEvent(QMouseEvent* event)
{
  if (!mSelection)
    return;

  mSelectActive = true;
  mSelection->setBegin(mapToScene(event->pos()));
}

void MazeEditWidget::mouseMoveEvent(QMouseEvent* event)
{
  if (!mSelection)
    return;

  mSelection->setEnd(mapToScene(event->pos()));
  viewport()->update();
}

void MazeEditWidget::mouseReleaseEvent(QMouseEvent* event)
{
  if (mSelectActive && mSelection) {
    mSelection->setEnd(mapToScene(event->pos()));

    mSelectActive = false;
    viewport()->update();
  }
}
