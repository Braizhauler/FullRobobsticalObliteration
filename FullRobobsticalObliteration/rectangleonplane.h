/******************************&************************************************
* File: rectangleonplane.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 FEB 12
* Version: 0
* Revised: 2015 FEB 12
*
* RectangleOnPlane:
*   An interface for a rectangle on a plane
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef RECTANGLE_ON_PLANE_H
#define RECTANGLE_ON_PLANE_H

#include "rectangle.h"
#include "point.h"

class RectangleOnPlane: public Rectangle {
public:
  virtual ~RectangleOnPlane(void) {};
  //returns true if:
  //x is between left and right
  //y is between top and bottom
  virtual bool containPoint(int x, int y)=0;
  virtual bool containPoint(Point)=0;

  virtual int left()=0;
  virtual int right()=0;
  virtual int top()=0;
  virtual int bottom()=0;
  
  virtual void setLeft(int)=0;
  virtual void setRight(int)=0;
  virtual void setTop(int)=0;
  virtual void setBottom(int)=0;
};

#endif //RECTANGLE_ON_PLANE_H