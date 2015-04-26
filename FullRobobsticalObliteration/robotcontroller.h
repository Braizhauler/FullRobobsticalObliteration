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
#include "carddeck.h"
#include "gameboardcontroller.h"
namespace Robot {
enum CARDINAL_DIRECTION {
  INVALID = -1,
  NORTH,
  SOUTH,
  EAST,
  WEST
};

enum ACTION {
  ACTION_INVALID = -1,
  ACTION_TURN_LEFT,
  ACTION_TURN_RIGHT,
  ACTION_MOVE_FORWARD,
  ACTION_MOVE_BACKWARD
};
}

class RobotController{
public:
  RobotController(int robot_number = 1,
                  GameBoardController* board = nullptr,
                  Point location = Point(0.0,0.0),
                  Robot::CARDINAL_DIRECTION direction=Robot::NORTH
                  );
  ~RobotController(void);

  Robot::ACTION*ParceCard(Card::Rally_Card); 
  void PreformAction(Robot::ACTION);
private:
  GameBoardController*board_;
  Robot::CARDINAL_DIRECTION facing_;
  int robot_number_;
  Point board_coordiante_location_;
};