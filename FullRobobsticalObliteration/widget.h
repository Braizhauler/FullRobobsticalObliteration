/******************************&************************************************
* File: widget.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 FEB 12
* Version: 0
* Revised: 2015 FEB 12
*
* Widget:
*   An interface for all user interface elements
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef WIDGET_H
#define WIDGET_H


#include <list>

#include "renderable.h"
#include "rectangleinspace.h"

class FrameWidget;

class Widget: public virtual RectangleInSpace, public virtual Renderable {
public:
  //inform children and parent when you are deconstructed
  virtual ~Widget(void) {}


  //returns true if:
  //x is between left and right
  //y is between top and bottom
  virtual const bool containPoint(double x, double y)=0;
  virtual const bool containPoint(Point)=0;

  virtual const FrameWidget* parent() const=0;
  virtual void setParent(FrameWidget*)=0;
};

#endif //WIDGET_H