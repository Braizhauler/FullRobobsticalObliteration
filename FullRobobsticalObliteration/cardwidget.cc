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
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "cardwidget.h"

const double CardWidget::FLIP_SPEED=0.1;

CardWidget::CardWidget(GameStateManager* manager) {
  game_state_manager_ = manager;
  atlas_ = manager->TextureAtlas();
  card_ = nullptr;
  face_up_= true;
  flipping_up_ = true;
  flip_width_=1.0;
  setColor(0.8f,0.8f,0.8f);
  dragging_ = false;

  current_location_ = WidgetLocation(8.0, 12.0, 0.0, 0.0, 0.0);
}

CardWidget::CardWidget(GameStateManager* manager, WidgetLocation location) {
  game_state_manager_ = manager;
  atlas_ = manager->TextureAtlas();
  card_ = nullptr;
  face_up_ = true;
  flip_width_=1.0;
  setColor(1.0f,1.0f,1.0f);
  dragging_ = false;
  current_location_ = location;
}

CardWidget::~CardWidget(void) {
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

card::Card* CardWidget::GetCard(){
	return card_;
}

void CardWidget::SetCard(card::Card*new_card){
  bool face_up_=true;
	card_ = new_card;
}

std::string CardWidget::GetTextureName(void) {
  if (card_==nullptr) return "";
  return std::to_string(10*card_->priority);
}


const bool CardWidget::dragging() const {
  return dragging_;
}

void CardWidget::DragStart(double x, double y) {
  dragging_=true;
  drag_location_=current_location_;
  drag_point_.x=x-current_location_.left();
  drag_point_.y=y-current_location_.top();
}
void CardWidget::DragTo(double x, double y) {
  drag_location_.setLeft(x-drag_point_.x);
  drag_location_.setTop(y-drag_point_.y);
}
Point CardWidget::DragEnd(double x, double y) {
  dragging_=false;
  drag_point_.x=drag_location_.left();
  drag_point_.y=drag_location_.top();
  return drag_point_;
}

void CardWidget::FlipStart() {
  flipping_up_ = !flipping_up_;
  flip_width_=0.9*flip_width_;
}

void CardWidget::Draw() {
  if(flip_width_<1.0) {
    if ((face_up_&&flipping_up_)||(!(face_up_||flipping_up_))) {
      flip_width_+=FLIP_SPEED;
      if(flip_width_>1.0){
        flip_width_=1.0;
      }
    } else {
      flip_width_-=FLIP_SPEED;
      if(flip_width_<0.0){
        face_up_=!face_up_;
        flip_width_=0.0;
      }
    }
  } else {
    flip_width_=1.0;
  }
  if (face_up_) 
    atlas_->ActivateTexture(GetTextureName());
  else
    atlas_->ActivateTexture("card_back");
  double card_skew=(1.0-flip_width_)*current_location_.width()/2.0;
  glEnable(GL_TEXTURE_2D);
  glColor3f(color_[0],color_[1],color_[2]);
  glBegin(GL_TRIANGLE_FAN);
    atlas_->LoadCoordinates(Texture::UPPER_LEFT);
    glVertex3d(current_location_.left()+card_skew,
               current_location_.top(),
               current_location_.depth());
    
    atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
    glVertex3d(current_location_.right()-card_skew,
               current_location_.top(),
               current_location_.depth());

    atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
    glVertex3d(current_location_.right()-card_skew,
               current_location_.bottom(),
               current_location_.depth());

    atlas_->LoadCoordinates(Texture::LOWER_LEFT);
    glVertex3d(current_location_.left()+card_skew,
               current_location_.bottom(),
               current_location_.depth());
  glEnd();
  glDisable(GL_TEXTURE_2D);
  if(dragging_) {
    glColor3f(0.8f, 0.4f, 0.4f);
    glLineWidth(3);
      glBegin(GL_LINE_LOOP);
      glVertex3d(drag_location_.left(),
                 drag_location_.top(),
                 drag_location_.depth());
      glVertex3d(drag_location_.right(),
                 drag_location_.top(),
                 drag_location_.depth());
      glVertex3d(drag_location_.right(),
                 drag_location_.bottom(),
                 drag_location_.depth());
      glVertex3d(drag_location_.left(),
                 drag_location_.bottom(),
                 drag_location_.depth());
    glEnd();
    glLineWidth(1);
  };
}

//TODO, Move focus from widget to interface Focusable and game states
void CardWidget::Draw(bool has_focus) {
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
const bool CardWidget::ContainPoint(const Point point) const{
  return ContainPoint(point.x, point.y);
}

  
const bool CardWidget::ContainPoint(const double x, const double y) const{
  if( (current_location_.left() <= x) && (x <= current_location_.right()) ) {
    if( (current_location_.top()<= y) && (y <= current_location_.bottom()) ) {
      return true;
    }
  }
  return false;
}

void CardWidget::MoveTo(const double x, const double y) {
  Point point;
  point.x = x;
  point.y = y;
  current_location_.MoveTo(point);
}

void CardWidget::MoveTo(const Point point) {
  current_location_.MoveTo(point);
}

void CardWidget::SizeTo(const double x, const double y) {
  Point point;
  point.x = x;
  point.y = y;
  current_location_.MoveTo(point);
}

void CardWidget::SizeTo(const Widget* model) {
  current_location_.setWidth(model->width());
  current_location_.setHeight(model->height());
}

FrameWidget* CardWidget::parent() const {
  return parent_;
}

void CardWidget::setParent(FrameWidget* new_parent) {
  new_parent->clearChild(this);
  parent_ = new_parent;
}

double CardWidget::width() const {
  return current_location_.width();
}
void CardWidget::setWidth(double new_width) {
  current_location_.setWidth(new_width);
}

double CardWidget::height() const {
  return current_location_.height();
}
void CardWidget::setHeight(double new_height) {
  current_location_.setHeight(new_height);
}
  
double CardWidget::left() const{
  return current_location_.left();
}
void CardWidget::setLeft(double new_left) {
  current_location_.setLeft(new_left);
}
 
double CardWidget::right() const{
  return current_location_.right();
}
void CardWidget::setRight(double new_right) {
  current_location_.setRight(new_right);
}
 
double CardWidget::top() const {
  return current_location_.top();
}
void CardWidget::setTop(double new_top) {
  current_location_.setTop(new_top);
}
  
double CardWidget::bottom() const {
  return current_location_.bottom();
}
void CardWidget::setBottom(double new_bottom) {
  current_location_.setBottom(new_bottom);
}

double CardWidget::depth() const {
  return current_location_.depth();
}
void CardWidget::setDepth(double new_depth) {
 current_location_.setDepth(new_depth);
}
