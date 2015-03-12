/*******************************************************************************
* File: renderable.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 12
* Version: 0
* Revised: 2015 MAR 12
*
* Focusable:
*   Virtual class for objects that can gain "focus" for purpose of keyboard
*     input, solely adds an alternate draw function when class is focused.
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef FOCUSABLE_H
#define FOCUSABLE_H

class Focusable {
public:
  //Constructors and Destructor
  virtual ~Focusable(void) {};

  virtual void Draw(const bool focused) = 0;
};

#endif //FOCUSABLE_H