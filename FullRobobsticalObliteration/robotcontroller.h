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
#ifndef ROBOT_CONTROLER_H_
#define ROBOT_CONTROLER_H_

#include "point.h"
#include "carddeck.h"
#include "gameboardcontroller.h"
namespace Robot {
enum CARDINAL_DIRECTION {
  INVALID_CARDINAL_DIRECTION = -1,
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

  

  
  Robot::ACTION PeekQueue();
  Robot::ACTION PopQueue();
  Robot::ACTION*QueueCard(Card::RallyCard);
  int GetRobotNumber(void) const;

  Point GetLocation() const;
  Point GetNextLocation() const;
  Robot::CARDINAL_DIRECTION GetFacing() const;
  Robot::CARDINAL_DIRECTION GetNextFacing() const;

  bool QueueComplete();
private:
  void ClearActionQueue();
  void QueueAction(Robot::ACTION action=Robot::ACTION_INVALID);

  GameBoardController*board_;
  Robot::CARDINAL_DIRECTION facing_;

  int robot_number_;

  Point current_location_;
  int actions_in_queue_;

  static const int ACTION_QUEUE_SIZE=5;
  Robot::ACTION action_queue_[ACTION_QUEUE_SIZE];
};
#endif//ROBOT_CONTROLER_H_