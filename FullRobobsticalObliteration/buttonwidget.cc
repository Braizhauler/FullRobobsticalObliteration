/*******************************************************************************
* File: buttonwidget.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 Feb 20
* Version: 0
* Revised: 2015 MAR 10
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

  has_focus_ = false;
  is_pressed_ = false;

  top_= 0.0;
  bottom_= 5.0;
  left_= 0.0;
  right_= 10.0;
  depth_ = 0.0;
}

ButtonWidget::ButtonWidget(GameStateManager* manager, WidgetLocation location) {
  game_state_manager_ = manager;

  setColor(0.8f,0.8f,0.8f);

  has_focus_ = false;
  is_pressed_ = false;

  top_= location.top();
  bottom_= location.bottom();
  left_= location.left();
  right_= location.right();
  depth_ = location.depth();
}

ButtonWidget::~ButtonWidget(void) {
}

void ButtonWidget::Draw(void) const {
  is_pressed_ ?
    glColor3f(pressed_color_[0],pressed_color_[1],pressed_color_[2]) :
    glColor3f(button_color_[0],button_color_[1],button_color_[2]);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3d(left_,top_,depth_);
    glVertex3d(right_,top_,depth_);
    glVertex3d(right_,bottom_,depth_);
    glVertex3d(left_,bottom_,depth_);
  glEnd();
  if(is_pressed_)
    glColor3f(pressed_shadow_[0], pressed_shadow_[1], pressed_shadow_[2]);
  else
    glColor3f(button_shadow_[0], button_shadow_[1], button_shadow_[2]);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3d(right_, bottom_, depth_);
    glVertex3d(left_, bottom_, depth_);
    glVertex3d(left_+ 0.3,bottom_-0.3, depth_);
    glVertex3d(right_- 0.3,bottom_-0.3, depth_);
    glVertex3d(right_- 0.3,top_ + 0.3, depth_);
    glVertex3d(right_,top_,depth_);
  glEnd();

}

//TODO, Move focus from widget to interface Focusable and game states
void ButtonWidget::Draw(bool has_focus) const {
  Draw();
  if(has_focus) {
    glColor3f(0.8f, 0.8f, 0.0f);
    glBegin(GL_LINE_LOOP);
      glVertex3d(left_,top_,depth_);
      glVertex3d(right_,top_,depth_);
      glVertex3d(right_,bottom_,depth_);
      glVertex3d(left_,bottom_,depth_);
    glEnd();
  }
}
bool ButtonWidget::containPoint(Point point) {
  return containPoint(point.x, point.y);
}

  
bool ButtonWidget::containPoint(double x, double y) {
  if( (left_ <= x) && (x <= right_) ) {
    if( (top_ <= y) && (y <= bottom_) ) {
      return true;
    }
  }
  return false;
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

bool ButtonWidget::pressed() {
  return is_pressed_;
}
void ButtonWidget::setPressed(bool pressed_state) {
  is_pressed_ = pressed_state;
}

bool ButtonWidget::focus() {
  return has_focus_;
}

void ButtonWidget::setFocus() {
  has_focus_ = true;
}

void ButtonWidget::clearFocus() {
  has_focus_ = false;
}

double ButtonWidget::width() {
  return (right_ - left_);
}
void ButtonWidget::setWidth(double width) {
  right_ = (left_ + width);
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
void ButtonWidget::setLeft(double new_left) {
  right_ += new_left - left_;
  left_ = new_left;
}
 
double ButtonWidget::right() {
  return right_;
}
void ButtonWidget::setRight(double new_right) {
  left_ += new_right - right_;
  right_ = new_right;
}
 
double ButtonWidget::top() {
  return top_;
}
void ButtonWidget::setTop(double new_top) {
  bottom_ += new_top - top_;
  top_ = new_top;
}
  
double ButtonWidget::bottom() {
  return bottom_;
}
void ButtonWidget::setBottom(double new_bottom) {
  top_ += new_bottom - bottom_;
  bottom_ = new_bottom;
}

double ButtonWidget::depth() {
  return depth_;
}
void ButtonWidget::setDepth(double depth) {
  depth_ = depth;
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