/*******************************************************************************
* File: registerwidget.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 APR 13
* Version: 0
* Revised: 2015 APR 13
*
* RegisterWidget:
*   A gui widget which can contain a card
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "registerwidget.h"

RegisterWidget::RegisterWidget(void) { 
  current_location_=WidgetLocation(8.0,12.0,0.0,0.0,0.0);
  card_slot_location_=WidgetLocation(6.0,9.0,1.0,2.0,0.0);
  manager_ = nullptr;
  programmed_card_=nullptr;
  parent_ = nullptr;
  atlas_ = nullptr;
}
RegisterWidget::RegisterWidget(GameStateManager*manager,WidgetLocation location) {
  current_location_=location;
  card_slot_location_=WidgetLocation(7.2, 10.8);
  CenterSlot();
  manager_ = manager;
  atlas_ = manager_->TextureAtlas();
  programmed_card_=nullptr;
  parent_ = nullptr;
}
RegisterWidget::~RegisterWidget(void) {
}

const bool RegisterWidget::PointInSlot(const double x, const double y) const {
  if(card_slot_location_.left()<=x&&x<=card_slot_location_.right())
    if(card_slot_location_.top()<=y&&y<=card_slot_location_.bottom())
      return true;
  return false;
}


bool RegisterWidget::IsClear() const {
  return (programmed_card_==nullptr);
}

CardWidget* RegisterWidget::Card() const{
  return programmed_card_;
}

void RegisterWidget::SetCard(CardWidget* card) {
  programmed_card_= card;
  if(card!=nullptr)
    card->MoveTo(card_slot_location_.left(),card_slot_location_.top());
}
//returns true if:
//x is between left and right
//y is between top and bottom
const bool RegisterWidget::ContainPoint(const double x, const double y) const {
  if(current_location_.left()<=x&&x<=current_location_.right())
    if(current_location_.top()<=y&&y<=current_location_.bottom())
      return true;
  return false;
}

const bool RegisterWidget::ContainPoint(const Point point_in_question) const {
  return ContainPoint(point_in_question.x, point_in_question.y);
}

void RegisterWidget::MoveTo(const Point upper_left) {
  current_location_.MoveTo(upper_left);
}
void RegisterWidget::MoveTo(const double x, const double y) {
  current_location_.setLeft(x);
  current_location_.setTop(y);
}

void RegisterWidget::SizeTo(const Widget * model) {
  current_location_.setWidth(model->width());
  current_location_.setHeight(model->height());
}
void RegisterWidget::SizeTo(const double width, const double height) {
  current_location_.setWidth(width);
  current_location_.setHeight(height);
}
  
FrameWidget* RegisterWidget::parent() const {
  return nullptr;
}
void RegisterWidget::setParent(FrameWidget*) {
}

void RegisterWidget::Draw() {
  glColor3f(0.4f,0.6f,0.4f);
  glEnable(GL_TEXTURE_2D);
  atlas_->ActivateTexture("registry_background");
  glBegin(GL_TRIANGLE_FAN);
    atlas_->LoadCoordinates(Texture::UPPER_LEFT);
    glVertex3d(current_location_.left(),
               current_location_.top(),
               current_location_.depth());
    
    atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
    glVertex3d(current_location_.right(),
               current_location_.top(),
               current_location_.depth());
    
    atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
    glVertex3d(current_location_.right(),
               current_location_.bottom(),
               current_location_.depth());
    
    atlas_->LoadCoordinates(Texture::LOWER_LEFT);
    glVertex3d(current_location_.left(),
               current_location_.bottom(),
               current_location_.depth());
  glEnd();
  glColor3f(1.0f,1.0f,1.0f);
  if(programmed_card_==nullptr)
    atlas_->ActivateTexture("red_on");
  else if(programmed_card_->dragging())
    atlas_->ActivateTexture("yellow_on");
  else
    atlas_->ActivateTexture("green_on");
  glBegin(GL_TRIANGLE_FAN);
    atlas_->LoadCoordinates(Texture::UPPER_LEFT);
    glVertex3d(card_slot_location_.left(),
               card_slot_location_.top()-2.0,
               current_location_.depth());
    atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
    glVertex3d(card_slot_location_.left()+1.5,
               card_slot_location_.top()-2.0,
               current_location_.depth());
    atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
    glVertex3d(card_slot_location_.left()+1.5,
               card_slot_location_.top()-0.5,
               current_location_.depth());
    atlas_->LoadCoordinates(Texture::LOWER_LEFT);
    glVertex3d(card_slot_location_.left(),
               card_slot_location_.top()-0.5,
               current_location_.depth());
  glEnd();

  glColor3f(1.0f,1.0f,1.0f);
  glBegin(GL_TRIANGLE_FAN);
  atlas_->ActivateTexture("card_slot");
  atlas_->LoadCoordinates(Texture::UPPER_LEFT);
  glVertex3d(card_slot_location_.left(),
              card_slot_location_.top(),
              card_slot_location_.depth());
  atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
  glVertex3d(card_slot_location_.right(),
              card_slot_location_.top(),
              card_slot_location_.depth());
  atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
  glVertex3d(card_slot_location_.right(),
              card_slot_location_.bottom(),
              card_slot_location_.depth());
  atlas_->LoadCoordinates(Texture::LOWER_LEFT);
  glVertex3d(card_slot_location_.left(),
              card_slot_location_.bottom(),
              card_slot_location_.depth());
  glEnd();
  glDisable(GL_TEXTURE_2D);

  if(programmed_card_!=nullptr)
    programmed_card_->Draw();
}

double RegisterWidget::width() const {
  return current_location_.width();
}
void RegisterWidget::setWidth(double new_width) {
  current_location_.setWidth(new_width);
}

double RegisterWidget::height() const {
  return current_location_.height();
}
void RegisterWidget::setHeight(double new_height) {
  current_location_.setHeight(new_height);
}
  
double RegisterWidget::left() const{
  return current_location_.left();
}
void RegisterWidget::setLeft(double new_left) {
  current_location_.setLeft(new_left);
}
 
double RegisterWidget::right() const{
  return current_location_.right();
}
void RegisterWidget::setRight(double new_right) {
  current_location_.setRight(new_right);
}
 
double RegisterWidget::top() const {
  return current_location_.top();
}
void RegisterWidget::setTop(double new_top) {
  current_location_.setTop(new_top);
}
  
double RegisterWidget::bottom() const {
  return current_location_.bottom();
}
void RegisterWidget::setBottom(double new_bottom) {
  current_location_.setBottom(new_bottom);
}

double RegisterWidget::depth() const {
  return current_location_.depth();
}
void RegisterWidget::setDepth(double new_depth) {
 current_location_.setDepth(new_depth);
}

void RegisterWidget::CenterSlot() {
  card_slot_location_.setLeft((current_location_.left()+
                              current_location_.right()-
                              card_slot_location_.width())/2.0);
  card_slot_location_.setTop((current_location_.top()+
                             current_location_.bottom()-
                             card_slot_location_.height())/2.0+1.0);
}
