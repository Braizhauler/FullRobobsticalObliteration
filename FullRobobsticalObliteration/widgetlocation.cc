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

const double WidgetLocation::width() const {
  return right_-left_;
}
void WidgetLocation::setWidth(double new_width) {
  right_ = left_ + new_width;
}
 
const double WidgetLocation::left() const {
  return left_;
}
void WidgetLocation::setLeft(double new_left) {
  right_ += new_left - left_;
  left_ = new_left;
}
  
const double WidgetLocation::right() const {
  return right_;
}
void WidgetLocation::setRight(double new_right) {
  left_ += new_right - right_;
  right_ = new_right;
}

const double WidgetLocation::height() const {
  return bottom_ - top_;
}
void WidgetLocation::setHeight(double new_height) {
  bottom_ = top_ + new_height;
}

const double WidgetLocation::top() const {
  return top_;
}
void WidgetLocation::setTop(double new_top) {
  bottom_ += new_top - top_;
  top_ = new_top;
}

const double WidgetLocation::bottom() const {
  return bottom_;
}
void WidgetLocation::setBottom(double new_bottom) {
  top_ += new_bottom - bottom_;
  bottom_ = new_bottom;
}
  
const double WidgetLocation::depth() const {
  return depth_;
}
void WidgetLocation::setDepth(double new_depth){
  depth_ = new_depth;
}