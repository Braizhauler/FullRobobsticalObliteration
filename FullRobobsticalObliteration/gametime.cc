/*******************************************************************************
* File: gametime.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 FEB 12
* Version: 0
* Revised: 2015 FEB 12
*
* GameTime:
*   Data for holding a time within our game.
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/
#include "gametime.h"

GameTime::GameTime() {
  turn = 0;
  phase = 0;
  action = 0;
  frame = 0;
}

GameTime::~GameTime(void) {
}