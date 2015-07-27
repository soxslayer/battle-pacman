#pragma once

#include <memory>
#include <vector>

#include <QVector>

#include "SpriteSheet.h"

class Maze
{
public:
  class Tile
  {
  public:
    typedef enum
    {
      External,
      Wall,
      GhostHouse,
      GhostDoor,
      Pellet,
      PowerPellet,
      Walkway
    } Attribute;

    Tile();
    Tile(const Attribute& attr);
    Tile(const std::vector<Attribute>& attrs);

    bool hasAttribute(const Attribute& attr) const;
    bool hasAttributes(const std::vector<Attribute>& attrs) const;
    void setAttribute(const Attribute& attr);
    void setAttributes(const std::vector<Attribute>& attrs);
    void unsetAttribute(const Attribute& attr);
    void unsetAttributes(const std::vector<Attribute>& attrs);

  private:
    int mAttrs;
  };

  Maze(unsigned width, unsigned height);
  Maze(const std::vector<std::vector<Tile>>& tiles);

  int width() const { return mWidth; }
  int height() const { return mHeight; }

  Tile getTile(int x, int y) const;
  void setTile(int x, int y, const Tile& tile);
  SpriteSheet::MazeSprite getWallSprite(int x, int y);

private:
  typedef std::vector<std::vector<Tile>> TileBuffer;

  unsigned mWidth = 0;
  unsigned mHeight = 0;
  TileBuffer mMaze;

  static QVector<QPair<uint64_t, SpriteSheet::MazeSprite>> sSpriteLUT;
};
