#include "SpriteSheet.h"

QRectF SpriteSheet::getSpriteInfo(MazeSprite sprite)
{
  QRectF ret = mTileInfo;
  const QVector2D& spriteLocation = mSprites[sprite];

  ret.translate(spriteLocation.x() * ret.width(),
                spriteLocation.y() * ret.height());

  return ret;
}

SpriteSheet SpriteSheet::loadYaml(const QString& filename)
{
  YAML::Node config = YAML::LoadFile(filename.toStdString());
  return config.as<SpriteSheet>();
}

bool SpriteSheet::decodeYaml(const YAML::Node& node, SpriteSheet& rhs)
{
  if (!node.IsMap())
    return false;

  // check required fields
  if (!node["filename"] || !node["tileInfo"])
    return false;

  QString sheetFilename = node["filename"].as<QString>();

  rhs.mSheetImage = QPixmap(sheetFilename);
  rhs.mTileInfo = node["tileInfo"].as<QRectF>();
  rhs.mSprites = node["sprites"].as<QMap<MazeSprite, QVector2D>>();

  return true;
}

SpriteSheet::MazeSprite SpriteSheet::stringToMazeWallSprite(
  const QString& s)
{
  MAZE_SPRITE_LIST(MAZE_SPRITE_FROM_STRING_ITEM, s)

  return MazeSprite::Invalid;
}
