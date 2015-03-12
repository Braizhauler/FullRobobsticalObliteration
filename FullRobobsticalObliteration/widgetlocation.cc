#include "widgetlocation.h"

WidgetLocation::WidgetLocation(void) {
  left_  = 0.0;
  right_ = 0.0;
  top_   = 0.0;
  bottom_= 0.0;
  depth_ = 0.0;
}

WidgetLocation::WidgetLocation(double width, double height) {
  left_  = 0.0;
  right_ = width;
  top_   = 0.0;
  bottom_= height;
  depth_ = 0.0;
}

WidgetLocation::WidgetLocation(double width,
                               double height,
                               double left,
                               double top) {
  left_  = left;
  right_ = left + width;
  top_   = top;
  bottom_= top + height;
  depth_ = 0.0;
}

WidgetLocation::WidgetLocation(double width,
                               double height,
                               double left,
                               double top,
                               double depth) {
  left_  = left;
  right_ = left + width;
  top_   = top;
  bottom_= top + height;
  depth_ = depth;
}

WidgetLocation::~WidgetLocation(void) {
}

double WidgetLocation::width() {
  return right_-left_;
}
void WidgetLocation::setWidth(double new_width) {
  right_ = left_ + new_width;
}
 
double WidgetLocation::left() {
  return left_;
}
void WidgetLocation::setLeft(double new_left) {
  right_ += new_left - left_;
  left_ = new_left;
}
  
double WidgetLocation::right() {
  return right_;
}
void WidgetLocation::setRight(double new_right) {
  left_ += new_right - right_;
  right_ = new_right;
}

double WidgetLocation::height() {
  return bottom_ - top_;
}
void WidgetLocation::setHeight(double new_height) {
  bottom_ = top_ + new_height;
}

double WidgetLocation::top() {
  return top_;
}
void WidgetLocation::setTop(double new_top) {
  bottom_ += new_top - top_;
  top_ = new_top;
}

double WidgetLocation::bottom() {
  return bottom_;
}
void WidgetLocation::setBottom(double new_bottom) {
  top_ += new_bottom - bottom_;
  bottom_ = new_bottom;
}
  
double WidgetLocation::depth(){
  return depth_;
}
void WidgetLocation::setDepth(double new_depth){
  depth_ = new_depth;
}