/******************************&************************************************
* File: point.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 04
* Version: 0
* Revised: 2015 MAR 04
*
* Point:
*   A struct consiting of two integers, an x and a y
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/
#ifndef POINT_H
#define POINT_H

struct Point {
public:
  Point() {this->x=0.0;y=0.0;}
  Point(Point * model) {x=model->x;y=model->y;}
  Point(double x_pos,double y_pos) {x=x_pos;y=y_pos;}
  double x;
  double y;
};

#endif //POINT_H