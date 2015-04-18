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

#include <vector>
#include "point.h"
namespace gameboard {

enum FLOOR_MATERIAL {
  FLOOR_EMPTY,
  FLOOR_TRACK,
  FLOOR_TRACK_RIGHT,
  FLOOR_TRACK_LEFT
};

enum DIRECTION {
  DIRECTION_NULL,
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
using std::vector;
using namespace gameboard;
class GameBoardController {
public:
  GameBoardController(int board_size = 8);
  ~GameBoardController(void);

  void loadTestBoard(void);

  Tile*GetTile(int x, int y);
  Tile*GetTile(Point location);
  Tile*GetTile(double x, double y);
  
  WALL GetWall(int x, int y,DIRECTION wall_direction) const;
  WALL GetWall(double x, double y,DIRECTION wall_direction) const;
  WALL GetWall(Point location,DIRECTION wall_direction) const;
private:
  int width_;
  int height_;

  vector<WALL> north_south_walls_;
  vector<WALL> east_west_walls_;
  vector<Tile> board_;
};