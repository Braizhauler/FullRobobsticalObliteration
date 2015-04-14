/*******************************************************************************
* File: cardhandwidget.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 30
* Version: 0
* Revised: 2015 APR 13
*
* CardHandWidget:
*   A basic gui widget primarily ment for use as a widget container
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "cardhandwidget.h"


const double CardHandWidget::CARD_EXPOSE_RATE = 0.2;

CardHandWidget::CardHandWidget(GameStateManager* manager) {
  current_location_=WidgetLocation(8.0,8.0,0.0,0.0,0.0);
  game_state_manager_ = manager;
  parent_ = nullptr;
}

CardHandWidget::CardHandWidget(GameStateManager* manager,
                               WidgetLocation location) {
  child_list_.clear();
  game_state_manager_ = manager;
  current_location_ = location;
}

CardHandWidget::~CardHandWidget(void) {
}

FrameWidget* CardHandWidget::parent() const{
  return parent_;
}

void CardHandWidget::setParent(FrameWidget* new_parent) {
  parent_->clearChild(this);
  parent_ = new_parent;
}

void CardHandWidget::Draw(Focusable* focus) {
    glColor3f(0.5f,0.0f,0.1f);
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
  
  for(std::list<CardWidget*>::iterator child_iterator=child_list_.begin(),
      end_child_list=child_list_.end();
      child_iterator!=end_child_list;
      ) {
    if((*child_iterator)==card_raised_) {
      if(card_raised_->top()>current_location_.top())
        card_raised_->setTop(card_raised_->top() - CARD_EXPOSE_RATE);
      if(card_raised_->top()<current_location_.top())
        card_raised_->setTop(current_location_.top());
    } else {
      if((*child_iterator)->bottom()<current_location_.bottom())
        (*child_iterator)->setBottom((*child_iterator)->bottom() + CARD_EXPOSE_RATE);
      if((*child_iterator)->bottom()>current_location_.bottom())
        (*child_iterator)->setBottom(current_location_.bottom());
    }
    if(focus!=(Focusable*)(*child_iterator))
      (*child_iterator)->Draw();
    else
      (*child_iterator)->Draw(true);
        if((*child_iterator)==card_expanded_) {
      double last_card_left_edge=(*child_iterator)->left();
      ++child_iterator;
      if(child_iterator!=end_child_list) {
        if((*child_iterator)->left()<last_card_left_edge+card_width_)
          (*child_iterator)->setLeft((*child_iterator)->left()+CARD_EXPOSE_RATE);
        if((*child_iterator)->left()>last_card_left_edge+card_width_)
          (*child_iterator)->setLeft(last_card_left_edge+card_width_);
      }
    } else {
      double last_card_left_edge=(*child_iterator)->left();
      ++child_iterator;
      if(child_iterator!=end_child_list) {
        if((*child_iterator)->left()>last_card_left_edge+card_spacing_)
          (*child_iterator)->setLeft((*child_iterator)->left()-1.5*CARD_EXPOSE_RATE);
        if((*child_iterator)->left()<last_card_left_edge+card_spacing_)
          (*child_iterator)->setLeft(last_card_left_edge+card_spacing_);
      }
    }
  }
}

void CardHandWidget::Draw() {
  Draw(nullptr);
}

void CardHandWidget::addChild(CardWidget* new_child) {
  if(child_list_.empty()) {
    card_width_=new_child->width();
    card_height_=new_child->height();
  } else {
    new_child->SizeTo(card_width_,card_height_);
  }
  child_list_.push_back(new_child);
  cards_total_ = child_list_.size();
  if(cards_total_> 0) {
    if(card_width_*cards_total_<= current_location_.width()) {
      card_spacing_ = card_width_;
    } else {
      card_spacing_ = (current_location_.width()-(2*card_width_))
                      /(cards_total_-2);
    }
  }
  std::list<CardWidget*>::iterator child_iter = child_list_.begin();
  std::list<CardWidget*>::iterator end_child_list = child_list_.end();
  int count=0;
  while(child_iter!=end_child_list) {
    (*child_iter)->setLeft(current_location_.left()+(count*card_spacing_));
    (*child_iter)->setBottom(current_location_.bottom());
    ++count;
    ++child_iter;
  }
}

const bool CardHandWidget::ContainPoint(const Point point) const {
  return ContainPoint(point.x, point.y);
}

  
const bool CardHandWidget::ContainPoint(const double x, const double y) const {
  if( (current_location_.left() <= x) && (x <= current_location_.right()) ) {
    if( (current_location_.top() <= y) && (y <= current_location_.bottom()) ) {
      return true;
    }
  }
  return false;
}

void CardHandWidget::MoveTo(const double x, const double y) {
  current_location_.setLeft(x);
  current_location_.setTop(y);
}

void CardHandWidget::MoveTo(const Point point) {
  current_location_.MoveTo(point);
}

void CardHandWidget::SizeTo(const double x, const double y) {
  setWidth(x);
  setHeight(y);
}

void CardHandWidget::SizeTo(const Widget * model) {
  SizeTo(model->width(),model->height());
}


CardWidget* CardHandWidget::NextCard(Widget* current_card) {
  std::list<CardWidget*>::iterator child_iterator=child_list_.begin(),
                                end = child_list_.end();
  while(child_iterator != end) {
    if (current_card==(*child_iterator)) {
      ++child_iterator;
      if(child_iterator != end)
        return (*child_iterator);
      else
        return (nullptr);
    } else {
      ++child_iterator;
    }
  }
  return (*child_list_.begin());
}

CardWidget* CardHandWidget::CardAtCursor(const double x, const double y) {
  if(!ContainPoint(x,y))
    return nullptr;
  else {
    std::list<CardWidget*>::reverse_iterator child_iterator=child_list_.rbegin();
    std::list<CardWidget*>::reverse_iterator end = child_list_.rend();
    while(child_iterator != end &&
          !(*child_iterator)->ContainPoint(x,y)) {
      ++child_iterator;
    }
    if(child_iterator==end)
      return nullptr;
    return (*child_iterator);
  }
}

CardWidget* CardHandWidget::ExpandCardAtCursor(const double x, const double y) {
  if(!ContainPoint(x,y))
    return nullptr;
  else {
    std::list<CardWidget*>::reverse_iterator child_iterator=child_list_.rbegin();
    std::list<CardWidget*>::reverse_iterator end = child_list_.rend();
    while(child_iterator != end &&
          !(*child_iterator)->ContainPoint(x,y)) {
      ++child_iterator;
    }
    if(child_iterator==end)
      return nullptr;
    card_expanded_=(*child_iterator);
    return (*child_iterator);
  }
}


void CardHandWidget::ExpandCard(CardWidget* card_to_expand)  {
  for(std::list<CardWidget*>::iterator child_iter = child_list_.begin(),
      end_child_list = child_list_.end();
      child_iter!=end_child_list;
      child_iter++)
    if((*child_iter)==card_to_expand)
      card_expanded_=card_to_expand;
}

void CardHandWidget::RaiseCard(CardWidget* card_to_raise) {
  for(std::list<CardWidget*>::iterator child_iter = child_list_.begin(),
      end_child_list = child_list_.end();
      child_iter!=end_child_list;
      ++child_iter)
    if((*child_iter)==card_to_raise)
      card_raised_=card_to_raise;
}

void CardHandWidget::LowerAllCards() {
  card_raised_=nullptr;
}

void CardHandWidget::CollapseAllCards() {
}

double CardHandWidget::width() const {
  return current_location_.width();
}
void CardHandWidget::setWidth(double new_width) {
  current_location_.setWidth(new_width);
}

double CardHandWidget::height() const {
  return current_location_.height();
}
void CardHandWidget::setHeight(double new_height) {
  current_location_.setHeight(new_height);
}
  
double CardHandWidget::left() const{
  return current_location_.left();
}
void CardHandWidget::setLeft(double new_left) {
  current_location_.setLeft(new_left);
}
 
double CardHandWidget::right() const{
  return current_location_.right();
}
void CardHandWidget::setRight(double new_right) {
  current_location_.setRight(new_right);
}
 
double CardHandWidget::top() const {
  return current_location_.top();
}
void CardHandWidget::setTop(double new_top) {
  current_location_.setTop(new_top);
}
  
double CardHandWidget::bottom() const {
  return current_location_.bottom();
}
void CardHandWidget::setBottom(double new_bottom) {
  current_location_.setBottom(new_bottom);
}

double CardHandWidget::depth() const {
  return current_location_.depth();
}
void CardHandWidget::setDepth(double new_depth) {
 current_location_.setDepth(new_depth);
}
