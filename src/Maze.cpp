#include <cstring>
#include <stdexcept>

#include <QtGlobal>
#include <QDebug>

#include "Maze.h"

Maze::Tile::Tile()
  : mAttrs(0)
{
  setAttribute(Tile::Walkway);
}

Maze::Tile::Tile(const Attribute& attr)
  : mAttrs(0)
{
  setAttribute(attr);
}

Maze::Tile::Tile(const std::vector<Attribute>& attrs)
  : mAttrs(0)
{
  for (const auto& attr : attrs)
    setAttribute(attr);
}

bool Maze::Tile::hasAttribute(const Attribute& attr) const
{
  return mAttrs & (1 << static_cast<int>(attr));
}

bool Maze::Tile::hasAttributes(const std::vector<Attribute>& attrs) const
{
  for (const auto& attr : attrs) {
    if (!hasAttribute(attr))
      return false;
  }

  return true;
}

void Maze::Tile::setAttribute(const Attribute& attr)
{
  mAttrs |= (1 << static_cast<int>(attr));
}

void Maze::Tile::setAttributes(const std::vector<Attribute>& attrs)
{
  for (const auto& attr : attrs)
    setAttribute(attr);
}

void Maze::Tile::unsetAttribute(const Attribute& attr)
{
  mAttrs &= ~(1 << static_cast<int>(attr));
}

void Maze::Tile::unsetAttributes(const std::vector<Attribute>& attrs)
{
  for (const auto& attr : attrs)
    unsetAttribute(attr);
}



#define WALL_MASK(t) (1ul << ((t) * 5))
#define GHOUSE_MASK(t) (2ul << ((t) * 5))
#define GDOOR_MASK(t) (4ul << ((t) * 5))
#define EXTERNAL_MASK(t) (8ul << ((t) * 5))
#define WALKWAY_MASK(t) (16ul << ((t) * 5))

QVector<QPair<uint64_t, SpriteSheet::MazeSprite>> Maze::sSpriteLUT = {
  {
    EXTERNAL_MASK(0) | EXTERNAL_MASK(1) | EXTERNAL_MASK(2)
    | EXTERNAL_MASK(3) | WALL_MASK(4) | WALL_MASK(5)
    | EXTERNAL_MASK(6) | WALL_MASK(7),
    SpriteSheet::MazeSprite::OutsideTLCorner
  },
  {
    EXTERNAL_MASK(0) | EXTERNAL_MASK(1) | EXTERNAL_MASK(2)
    | WALL_MASK(3) | WALL_MASK(4) | EXTERNAL_MASK(5)
    | WALL_MASK(7) | EXTERNAL_MASK(8),
    SpriteSheet::MazeSprite::OutsideTRCorner
  },
  {
    EXTERNAL_MASK(0) | WALL_MASK(1) | EXTERNAL_MASK(3)
    | WALL_MASK(4) | WALL_MASK(5) | EXTERNAL_MASK(6)
    | EXTERNAL_MASK(7) | EXTERNAL_MASK(8),
    SpriteSheet::MazeSprite::OutsideBLCorner
  },
  {
    WALL_MASK(1) | EXTERNAL_MASK(2) | WALL_MASK(3)
    | WALL_MASK(4) | EXTERNAL_MASK(5) | EXTERNAL_MASK(6)
    | EXTERNAL_MASK(7) | EXTERNAL_MASK(8),
    SpriteSheet::MazeSprite::OutsideBRCorner
  },
  {
    WALKWAY_MASK(0) | WALKWAY_MASK(1) | WALKWAY_MASK(2)
    | WALKWAY_MASK(3) | GHOUSE_MASK(4) | GHOUSE_MASK(5),
    SpriteSheet::MazeSprite::GhostHouseTLCorner
  },
  {
    WALKWAY_MASK(0) | WALKWAY_MASK(1) | WALKWAY_MASK(2)
    | GHOUSE_MASK(3) | GHOUSE_MASK(4) | WALKWAY_MASK(5),
    SpriteSheet::MazeSprite::GhostHouseTRCorner
  },
  {
    WALKWAY_MASK(3) | GHOUSE_MASK(4) | GHOUSE_MASK(5)
    | WALKWAY_MASK(6) | WALKWAY_MASK(7) | WALKWAY_MASK(8),
    SpriteSheet::MazeSprite::GhostHouseBLCorner
  },
  {
    GHOUSE_MASK(3) | GHOUSE_MASK(4) | WALKWAY_MASK(5)
    | WALKWAY_MASK(6) | WALKWAY_MASK(7) | WALKWAY_MASK(8),
    SpriteSheet::MazeSprite::GhostHouseBRCorner
  },
  {
    WALKWAY_MASK(1) | GHOUSE_MASK(4)
    | GDOOR_MASK(5) | GHOUSE_MASK(7),
    SpriteSheet::MazeSprite::GhostHouseLWallEnd
  },
  {
    WALKWAY_MASK(0) | GDOOR_MASK(3)
    | GHOUSE_MASK(4) | GHOUSE_MASK(7),
    SpriteSheet::MazeSprite::GhostHouseRWallEnd
  },
  {
    WALKWAY_MASK(1) | GHOUSE_MASK(4) | GHOUSE_MASK(7),
    SpriteSheet::MazeSprite::OutsideBWall
  },
  {
    GHOUSE_MASK(1) | GHOUSE_MASK(4) | WALKWAY_MASK(7),
    SpriteSheet::MazeSprite::OutsideTWall
  },
  {
    WALKWAY_MASK(3) | GHOUSE_MASK(4) | GHOUSE_MASK(5),
    SpriteSheet::MazeSprite::OutsideRWall
  },
  {
    GHOUSE_MASK(3) | GHOUSE_MASK(4) | WALKWAY_MASK(5),
    SpriteSheet::MazeSprite::OutsideLWall
  },
  {
    EXTERNAL_MASK(1) | WALL_MASK(4),
    SpriteSheet::MazeSprite::OutsideTWall
  },
  {
    WALL_MASK(4) | EXTERNAL_MASK(7),
    SpriteSheet::MazeSprite::OutsideBWall
  },
  {
    EXTERNAL_MASK(3) | WALL_MASK(4),
    SpriteSheet::MazeSprite::OutsideLWall
  },
  {
    WALL_MASK(4) | EXTERNAL_MASK(5),
    SpriteSheet::MazeSprite::OutsideRWall
  },
  {
    GDOOR_MASK(4),
    SpriteSheet::MazeSprite::GhostHouseDoor
  }
};



Maze::Maze(unsigned width, unsigned height)
{
  mWidth = width;
  mHeight = height;

  mMaze.resize(mHeight);

  for (auto& col : mMaze)
    col.resize(mWidth);
}

Maze::Maze(const std::vector<std::vector<Tile>>& tiles)
{
  mHeight = tiles.size();
  mWidth = 0;

  for (const auto& row : tiles) {
    if (mWidth == 0)
      mWidth = row.size();
    else if (mWidth != row.size())
      throw std::invalid_argument("non-square maze given");

    mMaze.push_back(row);
  }
}

Maze::Tile Maze::getTile(int x, int y) const
{
  // If out of bounds, return a wall tile
  if (x < 0 || (unsigned)x >= mWidth)
    return Tile(Tile::External);

  if (y < 0 || (unsigned)y >= mHeight)
    return Tile(Tile::External);

  return mMaze[y][x];
}

void Maze::setTile(int x, int y, const Tile& tile)
{
  if (x < 0 || (unsigned)x >= mWidth)
    return;

  if (y < 0 || (unsigned)y >= mHeight)
    return;

  mMaze[y][x] = tile;
}

SpriteSheet::MazeSprite Maze::getWallSprite(int x, int y)
{
  uint64_t lutIndex = 0;

  for (int i = 0; i < 9; ++i) {
    Tile t = getTile(x + (i % 3 - 1), y + (i / 3 - 1));

    if (t.hasAttribute(Tile::Wall))
      lutIndex |= WALL_MASK(i);

    if (t.hasAttribute(Tile::GhostHouse))
      lutIndex |= GHOUSE_MASK(i);

    if (t.hasAttribute(Tile::GhostDoor))
      lutIndex |= GDOOR_MASK(i);

    if (t.hasAttribute(Tile::External))
      lutIndex |= EXTERNAL_MASK(i);

    if (t.hasAttribute(Tile::Walkway))
      lutIndex |= WALKWAY_MASK(i);
  }

  for (const auto& sprite : sSpriteLUT) {
    if ((lutIndex & sprite.first) == sprite.first)
      return static_cast<SpriteSheet::MazeSprite>(sprite.second);
  }

  return SpriteSheet::MazeSprite::None;
}
