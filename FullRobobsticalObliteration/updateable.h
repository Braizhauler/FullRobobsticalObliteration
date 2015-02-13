/*******************************************************************************
* File: updateable.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 FEB 12
* Version: 0
* Revised: 2015 FEB 12
*
* Renderable:
*   Virtual class for game states that require a update as the game's time or
*   animation frame number changes.
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef UPDATEABLE_H
#define UPDATEABLE_H

#include "gametime.h"

class Updateable {
public:
  //Constructors and Destructor
  virtual ~Updateable(void);

  virtual void Update(GameTime) = 0;
};

#endif //UPDATEABLE_H