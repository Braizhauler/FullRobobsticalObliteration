/*******************************************************************************
* File: widgetlocation.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 FEB 12
* Version: 0
* Revised: 2015 FEB 12
*
* WidgetLocation:
*   An implementation of RectangleInSpace primarily to use to initialize Widgets
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef WIDGET_LOCATION_H
#define WIDGET_LOCATION_H

#include "rectangleinspace.h"

class WidgetLocation : public RectangleInSpace
{
public:
  WidgetLocation(void);
  WidgetLocation(double width, double height);
  WidgetLocation(double width, double height, double left, double top);
  WidgetLocation(double width,
                 double height,
                 double left,
                 double top,
                 double depth);

  ~WidgetLocation(void);
  
  //preserves left
  double width();
  void setWidth(double);
  
  //perserves width
  double left();
  void setLeft(double);
  
  //perserves width
  double right();
  void setRight(double);

  double height();
  void setHeight(double);

  double top();
  void setTop(double);

  double bottom();
  void setBottom(double);

  
  double depth();
  void setDepth(double);
private:
  double left_;
  double right_;
  double top_;
  double bottom_;
  double depth_;
};

#endif//WIDGET_LOCATION_H