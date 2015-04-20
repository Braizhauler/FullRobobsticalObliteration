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
  seeded_ = false;
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
  //LoadTestBoard();
  RandomizeBoard();
}


GameBoardController::~GameBoardController(void) {
}

void GameBoardController::LoadTestBoard(void) {
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

void GameBoardController::RandomizeBoard(void) {
  ClearInteriorWalls();
  RecursiveDivision(0,width_,height_,0,true);
}
void GameBoardController::RecursiveDivision(const int north_edge,
                       const int east_edge,
                       const int south_edge,
                       const int west_edge,
                       const bool vertical) { 
  if(vertical) {
    int x=RandomInt(west_edge+1,east_edge);
    for(int y=north_edge;y<south_edge;++y)
      *(GetTile(x,y)->wall_west)=WALL_STANDARD;
    int y=RandomInt(north_edge,south_edge);
    *(GetTile(x,y)->wall_west)=WALL_NONE;
    y=RandomInt(north_edge,south_edge);
    *(GetTile(x,y)->wall_west)=WALL_NONE;
    if(south_edge-north_edge>3) {
      RecursiveDivision(north_edge,x,south_edge,west_edge,false);
      RecursiveDivision(north_edge,east_edge,south_edge,x,false);
    } else {
      if(x-west_edge>2)
        RecursiveDivision(north_edge,x,south_edge,west_edge,true);
      if(east_edge-x>2)
        RecursiveDivision(north_edge,east_edge,south_edge,x,true);
    }
  } else {
    int y=RandomInt(north_edge+1,south_edge);
    for(int x=west_edge;x<east_edge;++x)
      *(GetTile(x,y)->wall_north)=WALL_STANDARD;
    int x=RandomInt(west_edge,east_edge);
    *(GetTile(x,y)->wall_north)=WALL_NONE;
    x=RandomInt(west_edge,east_edge);
    *(GetTile(x,y)->wall_north)=WALL_NONE;
    if(east_edge-west_edge>3) {
      RecursiveDivision(north_edge,east_edge,y,west_edge,true);
      RecursiveDivision(y,east_edge,south_edge,west_edge,true);
    } else {
      if(y-north_edge>2)
        RecursiveDivision(north_edge,east_edge,y,west_edge,false);
      if(south_edge-y>2)
        RecursiveDivision(y,east_edge,south_edge,west_edge,false);
    }
  }
}
//generates a random integer from min to max-1
int GameBoardController::RandomInt(int min, int max) {
  if(!seeded_) {
    srand(time(NULL));
    seeded_=true;
  }
  if (max>min)
    return ((rand() % (max-min)) + min);
  return min;
}
void GameBoardController::ClearInteriorWalls() {
  for(int y=1;y<height_;++y)
    for(int x=1;x<width_;++x) {
        *(GetTile(x,y)->wall_west)=WALL_NONE;
        *(GetTile(x,y)->wall_north)=WALL_NONE;
    }
  for(int x=0;x<width_;++x) {
    *(GetTile(x,0)->wall_north)=WALL_STANDARD;
    *(GetTile(x,height_-1)->wall_south)=WALL_STANDARD;
  }
  for(int y=0;y<height_;++y) {
    *(GetTile(0,y)->wall_west)=WALL_STANDARD;
    *(GetTile(width_-1,y)->wall_east)=WALL_STANDARD;
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