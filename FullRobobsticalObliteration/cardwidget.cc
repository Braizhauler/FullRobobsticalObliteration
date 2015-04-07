/*******************************************************************************
* File: cardwidget.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 27
* Version: 0
* Revised: 2015 MAR 27
*
* CardWidget:
*   A gui widget which has a responds to mouse clicks
*
* � [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "cardwidget.h"

CardWidget::CardWidget(GameStateManager* manager) {
  game_state_manager_ = manager;

  setColor(0.8f,0.8f,0.8f);


  current_location_.setTop(0.0);
  current_location_.setBottom(5.0);
  current_location_.setLeft(0.0);
  current_location_.setRight(10.0);
  current_location_.setDepth(0.0);
}

CardWidget::CardWidget(GameStateManager* manager, WidgetLocation location) {
  game_state_manager_ = manager;

  setColor(0.8f,0.8f,0.8f);

  current_location_ = location;
}

CardWidget::~CardWidget(void) {
}

void CardWidget::Draw(void) const {
  glColor3f(color_[0],color_[1],color_[2]);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3d(current_location_.left(),
               current_location_.top(),
               current_location_.depth());
    glVertex3d(current_location_.right(),
               current_location_.top(),
               current_location_.depth());
    glVertex3d(current_location_.right(),
               current_location_.bottom(),
               current_location_.depth());
    glVertex3d(current_location_.left(),
               current_location_.bottom(),
               current_location_.depth());
  glEnd();
}

//TODO, Move focus from widget to interface Focusable and game states
void CardWidget::Draw(bool has_focus) const {
  Draw();
  if(has_focus) {
    glColor3f(0.8f, 0.8f, 0.0f);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex3d(current_location_.left(),
               current_location_.top(),
               current_location_.depth());
    glVertex3d(current_location_.right(),
               current_location_.top(),
               current_location_.depth());
    glVertex3d(current_location_.right(),
               current_location_.bottom(),
               current_location_.depth());
    glVertex3d(current_location_.left(),
               current_location_.bottom(),
               current_location_.depth());
    glEnd();
    glLineWidth(1);
  }
}
const bool CardWidget::containPoint(Point point) {
  return containPoint(point.x, point.y);
}

  
const bool CardWidget::containPoint(double x, double y) {
  if( (current_location_.left() <= x) && (x <= current_location_.right()) ) {
    if( (current_location_.top()<= y) && (y <= current_location_.bottom()) ) {
      return true;
    }
  }
  return false;
}


const FrameWidget* CardWidget::parent() const {
  return parent_;
}

void CardWidget::setParent(FrameWidget* new_parent) {
  new_parent->clearChild(this);
  parent_ = new_parent;
}

const double CardWidget::width() const {
  return current_location_.width();
}
void CardWidget::setWidth(double new_width) {
  current_location_.setWidth(new_width);
}

const double CardWidget::height() const {
  return current_location_.height();
}
void CardWidget::setHeight(double new_height) {
  current_location_.setHeight(new_height);
}

  
const double CardWidget::left() const{
  return current_location_.left();
}
void CardWidget::setLeft(double new_left) {
  current_location_.setLeft(new_left);
}
 
const double CardWidget::right() const{
  return current_location_.right();
}
void CardWidget::setRight(double new_right) {
  current_location_.setRight(new_right);
}
 
const double CardWidget::top() const {
  return current_location_.top();
}
void CardWidget::setTop(double new_top) {
  current_location_.setTop(new_top);
}
  
const double CardWidget::bottom() const {
  return current_location_.bottom();
}
void CardWidget::setBottom(double new_bottom) {
  current_location_.setBottom(new_bottom);
}

const double CardWidget::depth() const {
  return current_location_.depth();
}
void CardWidget::setDepth(double new_depth) {
 current_location_.setDepth(new_depth);
}

const float* CardWidget::color() {
  return color_;
}

void CardWidget::setColor(const float red,
                          const float green,
                          const float blue) {
  color_[0] = red;
  color_[1] = green;
  color_[2] = blue;
}