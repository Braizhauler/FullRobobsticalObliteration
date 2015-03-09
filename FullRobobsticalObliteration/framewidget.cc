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
}


FrameWidget::~FrameWidget(void) {
}

Widget* FrameWidget::parent() {
  return parent_;
}

void FrameWidget::setParent(Widget* new_parent) {
  parent_->clearChild(this);
  parent_ = new_parent;
}

//returns true if supplied widget * is a child of this.
bool FrameWidget::isChild(Widget* widget)  {
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

int FrameWidget::width() {
  return (right_ - left_);
}

void FrameWidget::setWidth(int width) {
  right_ = left_+width;
}

int FrameWidget::height() {
  return (bottom_ - top_);
}

void FrameWidget::setHeight(int height) {
  bottom_ = (top_ + height);
}

  
int FrameWidget::left() {
  return left_;
}

void FrameWidget::setLeft(int left) {
  left_ = left;
}
 
int FrameWidget::right() {
  return right_;
}

void FrameWidget::setRight(int right) {
  left_ += right - right_;
  right_ = right;
}
 
int FrameWidget::top() {
  return top_;
}

void FrameWidget::setTop(int top) {
  top_ = top;
}
  
int FrameWidget::bottom() {
  return bottom_;
}

void FrameWidget::setBottom(int bottom) {
  top_ += bottom - bottom_;
  bottom_ = bottom;
}

float FrameWidget::depth() {
  return depth_;
}

void FrameWidget::setDepth(float depth) {
  depth_ = depth;
}

void FrameWidget::Draw() {
  
}