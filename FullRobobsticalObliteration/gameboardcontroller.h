/*******************************************************************************
* File: gameboardcontroller.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 APR 17
* Version: 0
* Revised: 2015 APR 17
*
* GameBoardController:
*   An logical contruct for holding the play space in memory, and functions of
*   convinence, like loading maps from files etc.
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/
#ifndef GAME_BOARD_CONTROLER_H_
#define GAME_BOARD_CONTROLER_H_

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time *///To initialize srand 
#include <vector>
#include "point.h"
namespace GameBoard {

enum FLOOR_MATERIAL {
  FLOOR_EMPTY,
  FLOOR_TRACK,
  FLOOR_TRACK_RIGHT,
  FLOOR_TRACK_LEFT
};

enum DIRECTION {
  DIRECTION_NULL=-1,
  NORTH,
  EAST,
  SOUTH,
  WEST
};
enum WALL {
  WALL_NONE,
  WALL_STANDARD
};

struct Tile {
  Tile(FLOOR_MATERIAL floor,DIRECTION dir,
       WALL*north,WALL*east,WALL*south,WALL*west){
    floor_type=floor;
    floor_texture_direction=dir;
    wall_north=north;
    wall_east=east;
    wall_south=south;
    wall_west=west;
  };
  const WALL getWallMaterial(const DIRECTION dir) const {
    if(dir==NORTH) return*wall_north;
    if(dir==EAST) return*wall_east;
    if(dir==SOUTH) return*wall_south;
    if(dir==WEST) return*wall_west;
    return WALL_NONE;
  }
  FLOOR_MATERIAL  floor_type;
  DIRECTION  floor_texture_direction;
  WALL * wall_north;
  WALL * wall_east;
  WALL * wall_south;
  WALL * wall_west;
};

}
class GameBoardController {
public:
  GameBoardController(int board_size = 8);
  ~GameBoardController(void);

  void LoadTestBoard(void);

  void RandomizeBoard(void);

  GameBoard::Tile*GetTile(int x, int y);
  GameBoard::Tile*GetTile(Point location);
  GameBoard::Tile*GetTile(double x, double y);
  
  GameBoard::WALL GetWall(int x, int y,GameBoard::DIRECTION wall_direction) const;
  GameBoard::WALL GetWall(double x, double y,GameBoard::DIRECTION wall_direction) const;
  GameBoard::WALL GetWall(Point location,GameBoard::DIRECTION wall_direction) const;

private:
  void ClearInteriorWalls();
  void RecursiveDivision(const int wall_north,
                         const int wall_east,
                         const int wall_south,
                         const int wall_west,
                         const bool vertical);
  int RandomInt(int min, int max);

  int width_;
  int height_;
  int seeded_;
  std::vector<GameBoard::WALL> north_south_walls_;
  std::vector<GameBoard::WALL> east_west_walls_;
  std::vector<GameBoard::Tile> board_;
};

#endif//GAME_BOARD_CONTROLER_H_