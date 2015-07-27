#include "MazeBuilder.h"
#include "Maze.h"

/* maze with just a ghost house in the center */
std::vector<std::vector<Maze::Tile>> MazeBuilder::sDefaultMaze = {
  {
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall)
  },
  {
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(Maze::Tile::Wall)
  },
  {
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile({ Maze::Tile::GhostDoor, Maze::Tile::Wall }),
    Maze::Tile({ Maze::Tile::GhostDoor, Maze::Tile::Wall }),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile(),
    Maze::Tile(Maze::Tile::Wall)
  },
  {
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile(),
    Maze::Tile(Maze::Tile::Wall)
  },
  {
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile(),
    Maze::Tile(Maze::Tile::Wall)
  },
  {
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile(Maze::Tile::GhostHouse),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile(),
    Maze::Tile(Maze::Tile::Wall)
  },
  {
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile({ Maze::Tile::GhostHouse, Maze::Tile::Wall }),
    Maze::Tile(),
    Maze::Tile(Maze::Tile::Wall)
  },
  {
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(),
    Maze::Tile(Maze::Tile::Wall)
  },
  {
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall),
    Maze::Tile(Maze::Tile::Wall)
  }
};

MazeBuilder::MazeBuilder()
  : mMaze(sDefaultMaze)
{
}

MazeBuilder::~MazeBuilder()
{
}

void MazeBuilder::undoAction()
{
}

void MazeBuilder::redoAction()
{
}
