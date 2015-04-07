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

class RectangleOnPlane: public virtual Rectangle {
public:
  virtual ~RectangleOnPlane(void) {};

  virtual double left() const=0;
  virtual double right() const=0;
  virtual double top() const=0;
  virtual double bottom() const=0;
  
  virtual void setLeft(double)=0;
  virtual void setRight(double)=0;
  virtual void setTop(double)=0;
  virtual void setBottom(double)=0;
};

#endif //RECTANGLE_ON_PLANE_H