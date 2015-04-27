#include "robotcontroller.h"


RobotController::RobotController(int robot_number,
                                 GameBoardController* board,
                                 Point location,
                                 Robot::CARDINAL_DIRECTION direction) {
  robot_number_ = robot_number;
  board_ = board;
  current_location_ = location;
  actions_in_queue_=0;
  ClearActionQueue();
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

Point RobotController::GetNextLocation() const {
  if(action_queue_[0]==Robot::ACTION_MOVE_FORWARD) {
    Point next_location=current_location_;
    switch(facing_) {
    case Robot::NORTH:
      if(board_->GetWall(current_location_,GameBoard::NORTH)
                 !=GameBoard::WALL_STANDARD)
        next_location.y-=1;
      break;
    case Robot::EAST:
      if(board_->GetWall(current_location_,GameBoard::EAST)
                 !=GameBoard::WALL_STANDARD)
        next_location.x+=1;
      break;
    case Robot::SOUTH:
      if(board_->GetWall(current_location_,GameBoard::SOUTH)
                 !=GameBoard::WALL_STANDARD)
        next_location.y+=1;
      break;
    case Robot::WEST:
      if(board_->GetWall(current_location_,GameBoard::WEST)
                 !=GameBoard::WALL_STANDARD)
        next_location.x-=1;
      break;
    default:
      ;
    }
    return next_location;
  }
  if(action_queue_[0]==Robot::ACTION_MOVE_BACKWARD) {
    Point next_location=current_location_;
    switch(facing_) {
    case Robot::NORTH:
      if(board_->GetWall(current_location_,GameBoard::SOUTH)
                 !=GameBoard::WALL_STANDARD)
        next_location.y+=1;
      break;
    case Robot::EAST:
      if(board_->GetWall(current_location_,GameBoard::WEST)
                 !=GameBoard::WALL_STANDARD)
        next_location.x-=1;
      break;
    case Robot::SOUTH:
      if(board_->GetWall(current_location_,GameBoard::NORTH)
                 !=GameBoard::WALL_STANDARD)
        next_location.y-=1;
      break;
    case Robot::WEST:
      if(board_->GetWall(current_location_,GameBoard::EAST)
                 !=GameBoard::WALL_STANDARD)
        next_location.x+=1;
      break;
    default:
      ;
    }
    return next_location;
  }
  return current_location_;
}

Robot::CARDINAL_DIRECTION RobotController::GetFacing(void) const {
  return facing_;
}
Robot::CARDINAL_DIRECTION RobotController::GetNextFacing() const {
  if(action_queue_[0]==Robot::ACTION_TURN_LEFT) {
    Robot::CARDINAL_DIRECTION next_facing=facing_;
    switch(facing_) {
    case Robot::NORTH:
      next_facing=Robot::WEST;
      break;
    case Robot::EAST:
      next_facing=Robot::NORTH;
      break;
    case Robot::SOUTH:
      next_facing=Robot::EAST;
      break;
    case Robot::WEST:
      next_facing=Robot::SOUTH;
      break;
    default:
      ;
    }
    return next_facing;
  }
  if(action_queue_[0]==Robot::ACTION_TURN_RIGHT) {
    Robot::CARDINAL_DIRECTION next_facing=facing_;
    switch(facing_) {
    case Robot::NORTH:
      next_facing=Robot::EAST;
      break;
    case Robot::EAST:
      next_facing=Robot::SOUTH;
      break;
    case Robot::SOUTH:
      next_facing=Robot::WEST;
      break;
    case Robot::WEST:
      next_facing=Robot::NORTH;
      break;
    default:
      ;
    }
    return next_facing;
  }
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

bool RobotController::QueueComplete() {
  return(actions_in_queue_==0);
}

Robot::ACTION RobotController::PeekQueue() {
   return action_queue_[0];
}

Robot::ACTION RobotController::PopQueue() {
  Robot::ACTION temp=action_queue_[0];
  facing_=GetNextFacing();
  current_location_=GetNextLocation();
  int index=0;
  do {
    action_queue_[index]=action_queue_[index+1];
  } while (++index<4);
  action_queue_[4]=Robot::ACTION_INVALID;
  if(--actions_in_queue_<0)actions_in_queue_=0;
  return temp;
}