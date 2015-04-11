/*******************************************************************************
* File: buttonwidget.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 Feb 20
* Version: 0
* Revised: 2015 MAR 27
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

  setColor(0.8f,0.8f,0.8f);

  is_pressed_ = false;
  current_location_ = WidgetLocation(2.0,5.0,0.0,0.0,0.0);

}

ButtonWidget::ButtonWidget(GameStateManager* manager, WidgetLocation location) {
  game_state_manager_ = manager;

  setColor(0.8f,0.8f,0.8f);

  is_pressed_ = false;

  current_location_ = location;
}

ButtonWidget::~ButtonWidget(void) {
}

void ButtonWidget::Draw() {
  is_pressed_ ?
    glColor3f(pressed_color_[0],pressed_color_[1],pressed_color_[2]) :
    glColor3f(button_color_[0],button_color_[1],button_color_[2]);
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
  if(is_pressed_)
    glColor3f(pressed_shadow_[0], pressed_shadow_[1], pressed_shadow_[2]);
  else
    glColor3f(button_shadow_[0], button_shadow_[1], button_shadow_[2]);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3d(current_location_.right(),
               current_location_.bottom(),
               current_location_.depth());
    glVertex3d(current_location_.left(),
               current_location_.bottom(),
               current_location_.depth());
    glVertex3d(current_location_.left()+0.3,
               current_location_.bottom()-0.3,
               current_location_.depth());
    glVertex3d(current_location_.right()-0.3,
               current_location_.bottom()-0.3,
               current_location_.depth());
    glVertex3d(current_location_.right()-0.3,
               current_location_.top()+0.3,
               current_location_.depth());
    glVertex3d(current_location_.right(),
               current_location_.top(),
               current_location_.depth());
  glEnd();

}

//TODO, Move focus from widget to interface Focusable and game states
void ButtonWidget::Draw(bool has_focus) {
  Draw();
  if(has_focus) {
    glColor3f(0.8f, 0.8f, 0.0f);
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
  }
}
const bool ButtonWidget::ContainPoint(const Point point) const {
  return ContainPoint(point.x, point.y);
}

  
const bool ButtonWidget::ContainPoint(const double x, const double y) const {
  if( (current_location_.left() <= x) && (x <= current_location_.right()) ) {
    if( (current_location_.top() <= y) && (y <= current_location_.bottom()) ) {
      return true;
    }
  }
  return false;
}

void ButtonWidget::MoveTo(const double x, const double y) {
  current_location_.setLeft(x);
  current_location_.setTop(y);
}

void ButtonWidget::MoveTo(const Point point) {
  current_location_.MoveTo(point);
}

void ButtonWidget::SizeTo(const double x, const double y) {
  setWidth(x);
  setHeight(y);
}

void ButtonWidget::SizeTo(const Widget * model) {
  SizeTo(model->width(),model->height());
}

FrameWidget* ButtonWidget::parent() const {
  return parent_;
}

void ButtonWidget::setParent(FrameWidget* new_parent) {
  parent_->clearChild(this);
  parent_ = new_parent;
}

const bool ButtonWidget::pressed() const{
  return is_pressed_;
}
void ButtonWidget::setPressed(bool pressed_state) {
  is_pressed_ = pressed_state;
}


double ButtonWidget::width() const {
  return current_location_.width();
}
void ButtonWidget::setWidth(double new_width) {
  current_location_.setWidth(new_width);
}

double ButtonWidget::height() const {
  return current_location_.height();
}
void ButtonWidget::setHeight(double new_height) {
  current_location_.setHeight(new_height);
}
  
double ButtonWidget::left() const{
  return current_location_.left();
}
void ButtonWidget::setLeft(double new_left) {
  current_location_.setLeft(new_left);
}
 
double ButtonWidget::right() const{
  return current_location_.right();
}
void ButtonWidget::setRight(double new_right) {
  current_location_.setRight(new_right);
}
 
double ButtonWidget::top() const {
  return current_location_.top();
}
void ButtonWidget::setTop(double new_top) {
  current_location_.setTop(new_top);
}
  
double ButtonWidget::bottom() const {
  return current_location_.bottom();
}
void ButtonWidget::setBottom(double new_bottom) {
  current_location_.setBottom(new_bottom);
}

double ButtonWidget::depth() const {
  return current_location_.depth();
}
void ButtonWidget::setDepth(double new_depth) {
 current_location_.setDepth(new_depth);
}



const float* ButtonWidget::color() {
  return button_color_;
}

void ButtonWidget::setColor(const float red,
                            const float green,
                            const float blue) {
  button_color_[0] = red;
  button_color_[1] = green;
  button_color_[2] = blue;
  button_shadow_[0] = red / 2;
  button_shadow_[1] = green / 2;
  button_shadow_[2] = blue / 2;
  pressed_color_[0] = red / 2;
  pressed_color_[1] = green / 2;
  pressed_color_[2] = blue / 2;
  pressed_shadow_[0] = red / 4;
  pressed_shadow_[1] = green / 4;
  pressed_shadow_[2] = blue / 4;
}