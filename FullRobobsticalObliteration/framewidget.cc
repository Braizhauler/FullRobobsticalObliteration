/*******************************************************************************
* File: framewidget.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 06
* Version: 0
* Revised: 2015 APR 07
*
* FrameWidget:
*   A basic gui widget primarily ment for use as a widget container
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "framewidget.h"

FrameWidget::FrameWidget(GameStateManager* manager) {
    game_state_manager_ = manager;
    parent_ = nullptr;
}


FrameWidget::~FrameWidget(void) {
}

const bool FrameWidget::containPoint(const double x, const double y) const {
  if( (current_location_.left() <= x) && (x <= current_location_.right()) ) {
    if( (current_location_.top()<= y) && (y <= current_location_.bottom()) ) {
      return true;
    }
  }
  return false;
}

const bool FrameWidget::containPoint(const Point point) const {
  return containPoint(point.x, point.y);
}

void FrameWidget::MoveTo(const double x, const double y) {
  Point upper_left;
  upper_left.x = x;
  upper_left.y = y;
  current_location_.MoveTo(upper_left);
}

void FrameWidget::MoveTo(const Point upper_left) {
  current_location_.MoveTo(upper_left);
}



FrameWidget* FrameWidget::parent() const{
  return parent_;
}

void FrameWidget::setParent(FrameWidget* new_parent) {
  parent_->clearChild(this);
  parent_ = new_parent;
}

void FrameWidget::Draw() {
    for(std::list<Widget*>::iterator child_iterator = child_list_.begin();
      child_iterator != child_list_.end(); ++child_iterator)
      (*child_iterator)->Draw();
}

//returns true if supplied widget * is a child of this.
const bool FrameWidget::isChild(Widget* widget)  {
  for(std::list<Widget*>::iterator child_iterator = child_list_.begin();
      child_iterator != child_list_.end(); ++child_iterator)
    if (widget == *child_iterator)
      return true;
  return false;
}

Widget* FrameWidget::child(int child_number) {
  std::list<Widget*>::iterator child_iterator = child_list_.begin();
  for(int counter = 0; counter < child_number; ++counter)
    ++child_iterator;
  return *child_iterator;
}

std::list<Widget*> FrameWidget::children() {
  return child_list_;
}

//informs the child to clear their parent,
//then clears the child from our record
void FrameWidget::clearChild(Widget* child_to_remove) {
  child_to_remove->setParent(nullptr);
  child_list_.remove(child_to_remove);
}

// informs all children to to clear their parent,
//    then clears the all children from the our record
void FrameWidget::clearChildren() {
  for(std::list<Widget*>::iterator current = child_list_.begin(),
      end = child_list_.end();
      current != end;
      ++current)
    (*current)->setParent(nullptr);
  child_list_.clear();
} 

//adds the passed widget to our children record
void FrameWidget::addChild(Widget* new_child) {
  child_list_.push_back(new_child);
}

double FrameWidget::width() const {
  return current_location_.width();
}
void FrameWidget::setWidth(double new_width) {
  current_location_.setWidth(new_width);
}

double FrameWidget::height() const {
  return current_location_.height();
}
void FrameWidget::setHeight(double new_height) {
  current_location_.setHeight(new_height);
}
  
double FrameWidget::left() const{
  return current_location_.left();
}
void FrameWidget::setLeft(double new_left) {
  current_location_.setLeft(new_left);
}
 
double FrameWidget::right() const{
  return current_location_.right();
}
void FrameWidget::setRight(double new_right) {
  current_location_.setRight(new_right);
}
 
double FrameWidget::top() const {
  return current_location_.top();
}
void FrameWidget::setTop(double new_top) {
  current_location_.setTop(new_top);
}
  
double FrameWidget::bottom() const {
  return current_location_.bottom();
}
void FrameWidget::setBottom(double new_bottom) {
  current_location_.setBottom(new_bottom);
}

double FrameWidget::depth() const {
  return current_location_.depth();
}
void FrameWidget::setDepth(double new_depth) {
 current_location_.setDepth(new_depth);
}
