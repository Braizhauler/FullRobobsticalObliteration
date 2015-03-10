/*******************************************************************************
* File: buttonwidget.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 05
* Version: 0
* Revised: 2015 MAR 05
*
* ButtonWidget:
*   A gui widget which has a responds to mouse clicks
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "buttonwidget.h"

ButtonWidget::ButtonWidget(GameStateManager* manager) {
    game_state_manager_ = manager;
}


ButtonWidget::~ButtonWidget(void) {
}


void ButtonWidget::Draw(void) {
  glColor3f(color_[0],color_[1],color_[2]);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3d(top_,left_,depth_);
    glVertex3d(top_,right_,depth_);
    glVertex3d(bottom_,right_,depth_);
    glVertex3d(bottom_,left_,depth_);
  glEnd();
}


Widget* ButtonWidget::parent() {
  return parent_;
}

void ButtonWidget::setParent(Widget* new_parent) {
  parent_->clearChild(this);
  parent_ = new_parent;
}

//returns true if supplied widget * is a child of this.
bool ButtonWidget::isChild(Widget* widget)  {
  for(std::list<Widget*>::iterator child_iterator = child_list_.begin();
      child_iterator != child_list_.end(); ++child_iterator)
    if (widget == *child_iterator)
      return true;
  return false;
}

Widget* ButtonWidget::child(int child_number) {
  std::list<Widget*>::iterator child_iterator = child_list_.begin();
  for(int counter = 0; counter < child_number; ++counter)
    ++child_iterator;
  return *child_iterator;
}

std::list<Widget*> ButtonWidget::children() {
  return child_list_;
}

//informs the child to clear their parent,
//then clears the child from our record
void ButtonWidget::clearChild(int) {
}

void ButtonWidget::clearChild(Widget*) {
}

// informs all children to to clear their parent,
//    then clears the all children from the our record
void ButtonWidget::clearChildren() {
} 

//calls the child's decontructor then removes it from our children record
void ButtonWidget::deleteChild(int) {
}

//calls each childs' decontructor then removes them from our children record
void ButtonWidget::deleteChildren() {
}

//adds the passed widget to our children record
void ButtonWidget::addChild(Widget*) {
}

double ButtonWidget::width() {
  return (right_ - left_);
}

void ButtonWidget::setWidth(double width) {
  right_ = left_+width;
}

double ButtonWidget::height() {
  return (bottom_ - top_);
}

void ButtonWidget::setHeight(double height) {
  bottom_ = (top_ + height);
}

  
double ButtonWidget::left() {
  return left_;
}

void ButtonWidget::setLeft(double left) {
  left_ = left;
}
 
double ButtonWidget::right() {
  return right_;
}

void ButtonWidget::setRight(double right) {
  left_ += right - right_;
  right_ = right;
}
 
double ButtonWidget::top() {
  return top_;
}

void ButtonWidget::setTop(double top) {
  top_ = top;
}
  
double ButtonWidget::bottom() {
  return bottom_;
}

void ButtonWidget::setBottom(double bottom) {
  top_ += bottom - bottom_;
  bottom_ = bottom;
}

double ButtonWidget::depth() {
  return depth_;
}

void ButtonWidget::setDepth(double depth) {
  depth_ = depth;
}