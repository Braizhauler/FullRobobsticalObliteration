/*******************************************************************************
* File: gameboardcontroller.cc
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


#include "gameboardcontroller.h"


GameBoardController::GameBoardController(int board_size) {
  width_ = board_size;
  height_ = board_size;

  for(int count=0,number_ns_walls=(width_+1)*height_;
      count<number_ns_walls;++count)
    north_south_walls_.push_back(WALL_NONE);
  for(int count=0,number_ew_walls=width_*(height_+1);
      count<number_ew_walls;++count)
    east_west_walls_.push_back(WALL_NONE);
  for(int y=0;y<height_;++y)
    for(int x=0;x<width_;++x)
      board_.push_back(Tile(FLOOR_EMPTY,DIRECTION_NULL,
                            &east_west_walls_[x+y*width_],
                            &north_south_walls_[x+1+y*(width_+1)],
                            &east_west_walls_[x+(y+1)*width_],
                            &north_south_walls_[x+y*(width_+1)]));
  loadTestBoard();
}


GameBoardController::~GameBoardController(void) {
}

void GameBoardController::loadTestBoard(void) {
  for(int y=0;y<height_;++y)
    for(int x=0;x<width_;++x) {
      if(x==0)
        *(board_[x+y*width_].wall_west)=WALL_STANDARD;
      if(x==7)
        *(board_[x+y*width_].wall_east)=WALL_STANDARD;
      if(y==0)
        *(board_[x+y*width_].wall_north)=WALL_STANDARD;
      if(y==7)
        *(board_[x+y*width_].wall_south)=WALL_STANDARD;
      if((x+y)%11==0)
        board_[x+y*width_].floor_type=FLOOR_TRACK;
      if((x+y)%3==0)
        *(board_[x+y*width_].wall_north)=WALL_STANDARD;
      if((x-y)%4==0)
        *(board_[x+y*width_].wall_east)=WALL_STANDARD;
    }
}


Tile*GameBoardController::GetTile(int x, int y) {
  return &board_[x+y*width_];
}

Tile*GameBoardController::GetTile(Point location) {
  return GetTile(location.x,location.y);
}

Tile*GameBoardController::GetTile(double x, double y) {
  return GetTile((int)x,(int)y);
} 


WALL GameBoardController::GetWall(int x,int y,DIRECTION wall_direction) const {
  return board_[x+y*width_].getWallMaterial(wall_direction);
}
WALL GameBoardController::GetWall(double x,
                                  double y,
                                  DIRECTION wall_direction) const {
  return GetWall((int)x,(int)y,wall_direction);
}
WALL GameBoardController::GetWall(Point location,DIRECTION wall_direction) const{
  return GetWall(location.x,location.y,wall_direction);
}