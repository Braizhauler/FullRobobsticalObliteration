/******************************&************************************************
* File: rectangleinspace.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 FEB 12
* Version: 0
* Revised: 2015 MAR 12
*
* RectangleInSpace:
*   An interface for a rectangle on a plane
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef RECTANGLE_IN_SPACE_H
#define RECTANGLE_IN_SPACE_H

#include "rectangleonplane.h"

class RectangleInSpace:public virtual RectangleOnPlane {
public:
  virtual ~RectangleInSpace(void) {};
  virtual const double depth() const=0;
  virtual void setDepth(double)=0;
};

#endif //RECTANGLE_H