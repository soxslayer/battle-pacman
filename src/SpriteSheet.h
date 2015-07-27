#pragma once

#include <yaml-cpp/yaml.h>

#include <QMap>
#include <QPixmap>
#include <QRectF>
#include <QVector2D>

#include "QtYaml.h"

#define MAZE_SPRITE_LIST(item, ...) \
  item(GhostHouseTLCorner, ##__VA_ARGS__) \
  item(GhostHouseTRCorner, ##__VA_ARGS__) \
  item(GhostHouseBLCorner, ##__VA_ARGS__) \
  item(GhostHouseBRCorner, ##__VA_ARGS__) \
  item(GhostHouseLWallEnd, ##__VA_ARGS__) \
  item(GhostHouseRWallEnd, ##__VA_ARGS__) \
  item(GhostHouseDoor, ##__VA_ARGS__) \
  item(OutsideTLCorner, ##__VA_ARGS__) \
  item(OutsideTRCorner, ##__VA_ARGS__) \
  item(OutsideBLCorner, ##__VA_ARGS__) \
  item(OutsideBRCorner, ##__VA_ARGS__) \
  item(OutsideTWall, ##__VA_ARGS__) \
  item(OutsideBWall, ##__VA_ARGS__) \
  item(OutsideRWall, ##__VA_ARGS__) \
  item(OutsideLWall, ##__VA_ARGS__) \
  item(OutsideEnd, ##__VA_ARGS__) \
  item(OutsideUConnector1, ##__VA_ARGS__) \
  item(OutsideUConnector2, ##__VA_ARGS__) \
  item(OutsideDConnector1, ##__VA_ARGS__) \
  item(OutsideDConnector2, ##__VA_ARGS__) \
  item(OutsideRConnector1, ##__VA_ARGS__) \
  item(OutsideRConnector2, ##__VA_ARGS__) \
  item(OutsideLConnector1, ##__VA_ARGS__) \
  item(OutsideLConnector2, ##__VA_ARGS__) \
  item(None, ##__VA_ARGS__) \
  item(Invalid, ##__VA_ARGS__)

#define MAZE_SPRITE_ENUM_ITEM(ms) ms,
#define MAZE_SPRITE_FROM_STRING_ITEM(ms, var) \
  if (var == #ms) \
    return MazeSprite::ms;

class SpriteSheet
{
public:
  enum class MazeSprite
  {
    MAZE_SPRITE_LIST(MAZE_SPRITE_ENUM_ITEM)
  };

  const QPixmap& sheetImage() const { return mSheetImage; }
  const QRectF& tileInfo() const { return mTileInfo; }
  QRectF getSpriteInfo(MazeSprite sprite);

  static SpriteSheet loadYaml(const QString& filename);
  static bool decodeYaml(const YAML::Node& node, SpriteSheet& rhs);
  static MazeSprite stringToMazeWallSprite(const QString& s);

private:
  QPixmap mSheetImage;
  QRectF mTileInfo;
  QMap<MazeSprite, QVector2D> mSprites;
};

namespace YAML
{

template<>
struct convert<SpriteSheet>
{
  static bool decode(const Node& node, SpriteSheet& rhs)
  {
    return SpriteSheet::decodeYaml(node, rhs);
  }
};

template<>
struct convert<SpriteSheet::MazeSprite>
{
  static bool decode(const Node& node, SpriteSheet::MazeSprite& rhs)
  {
    rhs = SpriteSheet::stringToMazeWallSprite(node.as<QString>());
    return true;
  }
};

} /* namespace YAML */
