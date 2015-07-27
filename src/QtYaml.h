#pragma once

#include <QMap>
#include <QRectF>
#include <QString>
#include <QVector2D>

namespace YAML
{

template<>
struct convert<QString>
{
  static bool decode(const Node& node, QString& rhs)
  {
    rhs = QString::fromStdString(node.as<std::string>());

    return true;
  }
};

template<>
struct convert<QVector2D>
{
  static bool decode(const Node& node, QVector2D& rhs)
  {
    if (node.IsSequence()) {
      if (node.size() != 2)
        return false;

      rhs.setX(node[0].as<float>());
      rhs.setY(node[1].as<float>());

      return true;
    }
    else if (node.IsMap()) {
      if (!node["x"] || ! node["y"])
        return false;

      rhs.setX(node["x"].as<float>());
      rhs.setY(node["y"].as<float>());

      return true;
    }

    return false;
  }
};

template<>
struct convert<QRectF>
{
  static bool decode(const Node& node, QRectF& rhs)
  {
    if (node.IsSequence()) {
      if (node.size() != 4)
        return false;

      rhs.setX(node[0].as<float>());
      rhs.setY(node[1].as<float>());
      rhs.setWidth(node[2].as<float>());
      rhs.setHeight(node[3].as<float>());

      return true;
    }
    else if (node.IsMap()) {
      if (!node["x"] || !node["y"] || !node["width"] || !node["height"])
        return false;

      rhs.setX(node["x"].as<float>());
      rhs.setY(node["y"].as<float>());
      rhs.setWidth(node["width"].as<float>());
      rhs.setHeight(node["height"].as<float>());

      return true;
    }

    return false;
  }
};

template<typename K, typename V>
struct convert<QMap<K, V>>
{
  static bool decode(const Node& node, QMap<K, V>& rhs)
  {
    if (!node.IsMap())
      return false;

    rhs = QMap<K, V>(node.as<std::map<K, V>>());

    return true;
  }
};

} /* namespace YAML */
