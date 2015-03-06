/*******************************************************************************
* File: button.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 05
* Version: 0
* Revised: 2015 MAR 05
*
* Button:
*   An interface for a game states to be used by GameStateManager.
*   Specifies Input hooks and draw, and functions for initialization,
*   and clean up as the game switches states
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "button.h"

Button::Button(GameStateManager* manager) {
    game_state_manager_ = manager;
}


Button::~Button(void) {
}

Widget* Button::parent() {
  return parent_;
}

void Button::setParent(Widget* new_parent) {
  parent_->clearChild(this);
  parent_ = new_parent;
}

//returns true if supplied widget * is a child of this.
bool Button::isChild(Widget* widget)  {
  for(std::list<Widget*>::iterator child_iterator = child_list_.begin();
      child_iterator != child_list_.end(); ++child_iterator)
    if (widget == *child_iterator)
      return true;
  return false;
}

Widget* Button::child(int child_number) {
  std::list<Widget*>::iterator child_iterator = child_list_.begin();
  for(int counter = 0; counter < child_number; ++counter)
    ++child_iterator;
  return *child_iterator;
}

std::list<Widget*> Button::children() {
  return child_list_;
}

//informs the child to clear their parent,
//then clears the child from our record
void Button::clearChild(int) {
}

void Button::clearChild(Widget*) {
}

// informs all children to to clear their parent,
//    then clears the all children from the our record
void Button::clearChildren() {
} 

//calls the child's decontructor then removes it from our children record
void Button::deleteChild(int) {
}

//calls each childs' decontructor then removes them from our children record
void Button::deleteChildren() {
}

//adds the passed widget to our children record
void Button::addChild(Widget*) {
}

int Button::width() {
  return (right_ - left_);
}

void Button::setWidth(int width) {
  right_ = left_+width;
}

int Button::height() {
  return (bottom_ - top_);
}

void Button::setHeight(int height) {
  bottom_ = (top_ + height);
}

  
int Button::left() {
  return left_;
}

void Button::setLeft(int left) {
  left_ = left;
}
 
int Button::right() {
  return right_;
}

void Button::setRight(int right) {
  left_ += right - right_;
  right_ = right;
}
 
int Button::top() {
  return top_;
}

void Button::setTop(int top) {
  top_ = top;
}
  
int Button::bottom() {
  return bottom_;
}

void Button::setBottom(int bottom) {
  top_ += bottom - bottom_;
  bottom_ = bottom;
}

float Button::depth() {
  return depth_;
}

void Button::setDepth(float depth) {
  depth_ = depth;
}