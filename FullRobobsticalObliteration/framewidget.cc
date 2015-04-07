/*******************************************************************************
* File: framewidget.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 06
* Version: 0
* Revised: 2015 MAR 06
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

const FrameWidget* FrameWidget::parent() const{
  return parent_;
}

void FrameWidget::setParent(FrameWidget* new_parent) {
  parent_->clearChild(this);
  parent_ = new_parent;
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
void FrameWidget::clearChild(int) {
}

void FrameWidget::clearChild(Widget*) {
}

// informs all children to to clear their parent,
//    then clears the all children from the our record
void FrameWidget::clearChildren() {
} 

//calls the child's decontructor then removes it from our children record
void FrameWidget::deleteChild(int) {
}

//calls each childs' decontructor then removes them from our children record
void FrameWidget::deleteChildren() {
}

//adds the passed widget to our children record
void FrameWidget::addChild(Widget*) {
}

double FrameWidget::width() {
  return (right_ - left_);
}

void FrameWidget::setWidth(double width) {
  right_ = left_+width;
}

double FrameWidget::height() {
  return (bottom_ - top_);
}

void FrameWidget::setHeight(double height) {
  bottom_ = (top_ + height);
}

  
double FrameWidget::left() {
  return left_;
}

void FrameWidget::setLeft(double left) {
  left_ = left;
}
 
double FrameWidget::right() {
  return right_;
}

void FrameWidget::setRight(double right) {
  left_ += right - right_;
  right_ = right;
}
 
double FrameWidget::top() {
  return top_;
}

void FrameWidget::setTop(double top) {
  top_ = top;
}
  
double FrameWidget::bottom() {
  return bottom_;
}

void FrameWidget::setBottom(double bottom) {
  top_ += bottom - bottom_;
  bottom_ = bottom;
}

double FrameWidget::depth() {
  return depth_;
}

void FrameWidget::setDepth(double depth) {
  depth_ = depth;
}

void FrameWidget::Draw() {
  
}