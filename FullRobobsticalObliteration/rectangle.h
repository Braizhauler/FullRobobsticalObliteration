/******************************&************************************************
* File: rectangle.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 FEB 12
* Version: 0
* Revised: 2015 FEB 12
*
* Rectangle:
*   An interface for an object that has a width and a height
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
public:
  virtual ~Rectangle(void) {};
  virtual int width()=0;
  virtual int height()=0;
  virtual void setWidth(int)=0;
  virtual void setHeight(int)=0;
};

#endif //RECTANGLE_H