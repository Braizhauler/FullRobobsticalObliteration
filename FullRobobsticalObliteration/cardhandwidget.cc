/*******************************************************************************
* File: cardhandwidget.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 30
* Version: 0
* Revised: 2015 APR 09
*
* CardHandWidget:
*   A basic gui widget primarily ment for use as a widget container
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "cardhandwidget.h"

const double CARD_EXPOSE_RATE = 0.1;

CardHandWidget::CardHandWidget(GameStateManager* manager):FrameWidget(manager) {
  current_location_=WidgetLocation(8.0,8.0,0.0,0.0,0.0);
}

CardHandWidget::CardHandWidget(GameStateManager* manager,
                               WidgetLocation location):
                               FrameWidget(manager, location) {
  child_list_.clear();
}


CardHandWidget::~CardHandWidget(void) {
}

void CardHandWidget::Draw() {
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
  for(std::list<Widget*>::iterator child_iterator=child_list_.begin();
      child_iterator != child_list_.end(); ++child_iterator)
    (*child_iterator)->Draw();
}

void CardHandWidget::Nuetral() {
}

int CardHandWidget::CusorOverCard(const double x, const double y) {
  if(!containPoint(x,y))
    return -2;
  else {
    int card_number=child_list_.size()-1;
    std::list<Widget*>::reverse_iterator child_iterator=child_list_.rbegin();
    std::list<Widget*>::reverse_iterator end = child_list_.rend();
    while(child_iterator != end &&
          !(*child_iterator)->containPoint(x,y)) {
      ++child_iterator;
      --card_number;
    }
    return card_number;
  }

}
void ExpandCard(int card_number);
void RaiseCard(int card_number);