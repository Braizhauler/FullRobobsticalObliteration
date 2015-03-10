/*******************************************************************************
* File: renderable.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 JAN 24
* Version: 0
* Revised: 2015 JAN 24
*
* Renderable:
*   Virtual class for objects that are drawn.
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef RENDERABLE_H
#define RENDERABLE_H

class Renderable {
public:
  //Constructors and Destructor
  virtual ~Renderable(void) {};

  virtual void Draw(void) = 0;
};

#endif //RENDERABLE_H