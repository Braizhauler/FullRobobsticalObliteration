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
class Robot
{
public:
  Robot(void);
  ~Robot(void);

private:
  DIRECTION facing_;
  int robot_number;
  Point board_coordiante_location_;
};

