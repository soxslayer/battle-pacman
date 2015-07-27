#pragma once

#include <list>
#include <vector>

#include "Maze.h"

class MazeBuilder
{
public:
  MazeBuilder();
  ~MazeBuilder();

  Maze& getMaze() { return mMaze; }

  void undoAction();
  void redoAction();

private:
  Maze mMaze;

  static std::vector<std::vector<Maze::Tile>> sDefaultMaze;
};
