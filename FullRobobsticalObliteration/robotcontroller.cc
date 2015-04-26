#include "robotcontroller.h"


RobotController::RobotController(int robot_number,
                                 GameBoardController* board,
                                 Point location,
                                 Robot::CARDINAL_DIRECTION direction) {
  robot_number_ = robot_number;
  board_ = board;
  board_coordiante_location_ = location;
  facing_ = direction;
}


RobotController::~RobotController(void)
{
}


void RobotController::PreformAction(Robot::ACTION) {
}