#include "robotcontroller.h"


RobotController::RobotController(int robot_number,
                                 GameBoardController* board,
                                 Point location,
                                 Robot::CARDINAL_DIRECTION direction) {
  robot_number_ = robot_number;
  board_ = board;
  current_location_ = location;
  facing_ = direction;
}


RobotController::~RobotController(void)
{
}


Robot::ACTION* RobotController::QueueCard(Card::RallyCard card) {
  switch(card.suit) {
  case Card::SUIT_U_TURN:
    QueueAction(Robot::ACTION_TURN_RIGHT);
    QueueAction(Robot::ACTION_TURN_RIGHT);
    break;
  case Card::SUIT_ROT_LEFT:
    QueueAction(Robot::ACTION_TURN_LEFT);
    break;
  case Card::SUIT_ROT_RIGHT:
    QueueAction(Robot::ACTION_TURN_RIGHT);
    break;
  case Card::SUIT_BACK_UP:
    QueueAction(Robot::ACTION_MOVE_BACKWARD);
    break;
  case Card::SUIT_FORWARD_1:
    QueueAction(Robot::ACTION_MOVE_FORWARD);
    break;
  case Card::SUIT_FORWARD_2:
    QueueAction(Robot::ACTION_MOVE_FORWARD);
    QueueAction(Robot::ACTION_MOVE_FORWARD);
    break;
  case Card::SUIT_FORWARD_3:
    QueueAction(Robot::ACTION_MOVE_FORWARD);
    QueueAction(Robot::ACTION_MOVE_FORWARD);
    QueueAction(Robot::ACTION_MOVE_FORWARD);
  default:
    ;
  }
  return action_queue_;
}

int RobotController::GetRobotNumber(void) const {
  return robot_number_;
}

Point RobotController::GetLocation(void) const {
  return current_location_;
}

Robot::CARDINAL_DIRECTION RobotController::GetFacing(void) const {
  return facing_;
}
void RobotController::ClearActionQueue() {
  actions_in_queue_=0;
  for(int count=0;count<ACTION_QUEUE_SIZE;++count) {
    action_queue_[count]=Robot::ACTION_INVALID;
  }
}

void RobotController::QueueAction(Robot::ACTION action) {
  if(action!=Robot::ACTION_INVALID&&actions_in_queue_<ACTION_QUEUE_SIZE) {
    action_queue_[actions_in_queue_]=action;
    ++actions_in_queue_;
  }
}
