/*******************************************************************************
* File: cardhandwidget.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 30
* Version: 0
* Revised: 2015 MAR 31
*
* CardHandWidget:
*   A basic gui widget primarily ment for use as a widget container
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "cardhandwidget.h"

CardHandWidget::CardHandWidget(GameStateManager* manager) {
    game_state_manager_ = manager;
}


CardHandWidget::~CardHandWidget(void) {
}

const bool CardHandWidget::containPoint(Point point) {
  return containPoint(point.x, point.y);
}

const bool CardHandWidget::containPoint(double x, double y) {
  if( (left_>=x) && (x>=right_) )
    if( (top_>=y) && (y>=bottom_) )
      return true;
  return false;
}


Widget* CardHandWidget::parent() {
  return parent_;
}

void CardHandWidget::setParent(Widget* new_parent) {
  parent_ = new_parent;
}

//returns true if supplied widget * is a child of this.
const bool CardHandWidget::isChild(Widget* widget)  {
  for(std::list<Widget*>::iterator child_iterator = child_list_.begin();
      child_iterator != child_list_.end(); ++child_iterator)
    if (widget == *child_iterator)
      return true;
  return false;
}

Widget* CardHandWidget::child(int child_number) {
  std::list<Widget*>::iterator child_iterator = child_list_.begin();
  for(int counter = 0; counter < child_number; ++counter)
    ++child_iterator;
  return *child_iterator;
}

std::list<Widget*> CardHandWidget::children() {
  return child_list_;
}

//informs the child to clear their parent,
//then clears the child from our record
void CardHandWidget::clearChild(int) {
}

void CardHandWidget::clearChild(Widget*) {
}

// informs all children to to clear their parent,
//    then clears the all children from the our record
void CardHandWidget::clearChildren() {
} 

//calls the child's decontructor then removes it from our children record
void CardHandWidget::deleteChild(int) {
}

//calls each childs' decontructor then removes them from our children record
void CardHandWidget::deleteChildren() {
}

//adds the passed widget to our children record
void CardHandWidget::addChild(Widget*) {
}

double CardHandWidget::width() {
  return (right_ - left_);
}

void CardHandWidget::setWidth(double width) {
  right_ = left_+width;
}

double CardHandWidget::height() {
  return (bottom_ - top_);
}

void CardHandWidget::setHeight(double height) {
  bottom_ = (top_ + height);
}

  
double CardHandWidget::left() {
  return left_;
}

void CardHandWidget::setLeft(double left) {
  left_ = left;
}
 
double CardHandWidget::right() {
  return right_;
}

void CardHandWidget::setRight(double right) {
  left_ += right - right_;
  right_ = right;
}
 
double CardHandWidget::top() {
  return top_;
}

void CardHandWidget::setTop(double top) {
  top_ = top;
}
  
double CardHandWidget::bottom() {
  return bottom_;
}

void CardHandWidget::setBottom(double bottom) {
  top_ += bottom - bottom_;
  bottom_ = bottom;
}

double CardHandWidget::depth() {
  return depth_;
}

void CardHandWidget::setDepth(double depth) {
  depth_ = depth;
}

void CardHandWidget::Draw() {
  glColor3f(0.8f,0.8f,0.5f);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3d(left_,top_,depth_);
    glVertex3d(right_,top_,depth_);
    glVertex3d(right_,bottom_,depth_);
    glVertex3d(left_,bottom_,depth_);
  glEnd();
}