/*******************************************************************************
* File: gameboardcontroller.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 APR 22
* Version: 0
* Revised: 2015 APR 24
*
* RobotSprite:
*   An entity for rendering a robot
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef ROBOT_WIDGET_H_
#define ROBOT_WIDGET_H_

#include <math.h>

#include "gamestatemanager.h"
#include "gameboardwidget.h"
#include "robotcontroller.h"

namespace Robot {

enum RELATIVE_POSITION_8_WAY {
  INVALID,
  FAR,
  FAR_RIGHT,
  RIGHT,
  NEAR_RIGHT,
  NEAR,
  NEAR_LEFT,
  LEFT,
  FAR_LEFT
};
}


class RobotSprite{
public:
  RobotSprite(GameStateManager* manager=nullptr,const int robot=0);
  ~RobotSprite(void);
  
  void SetSpritePrefix(const int robot_number);

  void Draw(double angle);

private:
  void SetPrefix(const int robot_number);
  Robot::CARDINAL_DIRECTION SetPrefix();
  Robot::RELATIVE_POSITION_8_WAY OriginPosition() const;

  GameStateManager*manager_;

  RobotController board_position_;
  Point target_location_;
  double distance_traveled_;
  
  std::string sprite_prefix_;
  int animation_frame_;

  SpriteAtlas*atlas_;

  static const double ANIMATION_SPEED;
};


#endif//ROBOT_WIDGET_H_
