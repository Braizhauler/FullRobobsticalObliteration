/*******************************************************************************
* File: gametime.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2014 FEB 12
* Version: 0
* Revised: 2014 FEB 12
*
* GameTime:
*   A struct for defining a game time
*
* © [2014] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef GAME_TIME_H
#define GAME_TIME_H

struct GameTime {
public:
  //Constructors and Destructor
  GameTime (void);
  ~GameTime (void);
  int turn;
  int phase;
  int action;
  int frame;
};


#endif //GAME_TIME_H