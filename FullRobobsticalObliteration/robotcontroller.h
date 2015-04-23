/*******************************************************************************
* File: robot.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 JAN 19
* Version: 0
* Revised: 2015 FEB 02
*
*
* Robot:
*  A logical robot; 
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "point.h"
#include "gameboardcontroller.h"
namespace Robot {
enum CARDNIAL_DIRECTION {
  INVALID,
  NORTH,
  SOUTH,
  EAST,
  WEST
};

enum ACTION {
  ACTION_INVALID,
  ACTION_TURN_LEFT,
  ACTION_TURN_RIGHT,
  ACTION_MOVE_FORWARD,
  ACTION_MOVE_BACKWARD
 
};
}

class RobotController{
public:
  RobotController(void);
  ~RobotController(void);
private:
  DIRECTION facing_;
  int robot_number;
  Point board_coordiante_location_;
};

