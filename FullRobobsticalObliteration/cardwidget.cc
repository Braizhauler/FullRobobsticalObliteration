/*******************************************************************************
* File: cardwidget.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 Feb 20
* Version: 0
* Revised: 2015 MAR 10
*
* CardWidget:
*   A gui widget which has a responds to mouse clicks
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "cardwidget.h"

CardWidget::CardWidget(GameStateManager* manager) {
  game_state_manager_ = manager;

  setColor(0.8f,0.8f,0.8f);

  top_= 0.0;
  bottom_= 5.0;
  left_= 0.0;
  right_= 10.0;
  depth_ = 0.0;
}

CardWidget::CardWidget(GameStateManager* manager, WidgetLocation location) {
  game_state_manager_ = manager;

  setColor(0.8f,0.8f,0.8f);

  top_= location.top();
  bottom_= location.bottom();
  left_= location.left();
  right_= location.right();
  depth_ = location.depth();
}

CardWidget::~CardWidget(void) {
}

void CardWidget::Draw(void) const {
  glColor3f(color_[0],color_[1],color_[2]);
  glBegin(GL_TRIANGLE_FAN);
    glVertex3d(left_,top_,depth_);
    glVertex3d(right_,top_,depth_);
    glVertex3d(right_,bottom_,depth_);
    glVertex3d(left_,bottom_,depth_);
  glEnd();
}

//TODO, Move focus from widget to interface Focusable and game states
void CardWidget::Draw(bool has_focus) const {
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
bool CardWidget::containPoint(Point point) {
  return containPoint(point.x, point.y);
}

  
bool CardWidget::containPoint(double x, double y) {
  if( (left_ <= x) && (x <= right_) ) {
    if( (top_ <= y) && (y <= bottom_) ) {
      return true;
    }
  }
  return false;
}


Widget* CardWidget::parent() {
  return parent_;
}

void CardWidget::setParent(Widget* new_parent) {
  parent_->clearChild(this);
  parent_ = new_parent;
}

//returns true if supplied widget * is a child of this.
bool CardWidget::isChild(Widget* widget)  {
  for(std::list<Widget*>::iterator child_iterator = child_list_.begin();
      child_iterator != child_list_.end(); ++child_iterator)
    if (widget == *child_iterator)
      return true;
  return false;
}

Widget* CardWidget::child(int child_number) {
  std::list<Widget*>::iterator child_iterator = child_list_.begin();
  for(int counter = 0; counter < child_number; ++counter)
    ++child_iterator;
  return *child_iterator;
}

std::list<Widget*> CardWidget::children() {
  return child_list_;
}

//informs the child to clear their parent,
//then clears the child from our record
void CardWidget::clearChild(int) {
}

void CardWidget::clearChild(Widget*) {
}

// informs all children to to clear their parent,
//    then clears the all children from the our record
void CardWidget::clearChildren() {
} 

//calls the child's decontructor then removes it from our children record
void CardWidget::deleteChild(int) {
}

//calls each childs' decontructor then removes them from our children record
void CardWidget::deleteChildren() {
}

//adds the passed widget to our children record
void CardWidget::addChild(Widget*) {
}

double CardWidget::width() {
  return (right_ - left_);
}
void CardWidget::setWidth(double width) {
  right_ = (left_ + width);
}

double CardWidget::height() {
  return (bottom_ - top_);
}
void CardWidget::setHeight(double height) {
  bottom_ = (top_ + height);
}

  
double CardWidget::left() {
  return left_;
}
void CardWidget::setLeft(double new_left) {
  right_ += new_left - left_;
  left_ = new_left;
}
 
double CardWidget::right() {
  return right_;
}
void CardWidget::setRight(double new_right) {
  left_ += new_right - right_;
  right_ = new_right;
}
 
double CardWidget::top() {
  return top_;
}
void CardWidget::setTop(double new_top) {
  bottom_ += new_top - top_;
  top_ = new_top;
}
  
double CardWidget::bottom() {
  return bottom_;
}
void CardWidget::setBottom(double new_bottom) {
  top_ += new_bottom - bottom_;
  bottom_ = new_bottom;
}

double CardWidget::depth() {
  return depth_;
}
void CardWidget::setDepth(double depth) {
  depth_ = depth;
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