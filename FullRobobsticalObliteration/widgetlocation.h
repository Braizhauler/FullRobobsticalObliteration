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
  const double width() const;
  void setWidth(double);
  
  //perserves width
  const double left() const;
  void setLeft(double);
  
  //perserves width
  const double right() const;
  void setRight(double);

  const double height() const;
  void setHeight(double);

  const double top() const;
  void setTop(double);

  const double bottom() const;
  void setBottom(double);

  
  const double depth() const;
  void setDepth(double);
private:
  double left_;
  double right_;
  double top_;
  double bottom_;
  double depth_;
};

#endif//WIDGET_LOCATION_H