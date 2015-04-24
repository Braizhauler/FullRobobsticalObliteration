/*******************************************************************************
* File: cardwidget.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 27
* Version: 0
* Revised: 2015 MAR 27
*
* Card_Widget:
*   A gui widget which is draggable and stackable
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef CARD_WIDGET_H
#define CARD_WIDGET_H

#include <list>

#include "gamestatemanager.h"
#include "widget.h"
#include "framewidget.h"
#include "widgetlocation.h"
#include "focusable.h"
#include "carddeck.h"

class CardWidget: public Widget, public Focusable
{
public:
  //Constructors, and Destructor
  CardWidget(GameStateManager* manager = nullptr);
  CardWidget(GameStateManager* manager, const WidgetLocation location);
  ~CardWidget(void);

  const float* color();
  void setColor(const float red, const float green, const float blue);

  const bool dragging() const;

  void DragStart(double x, double y);
  void DragTo(double x, double y);
  Point DragEnd(double x, double y);

  void FlipStart(void);
  bool Flipping(void);

  /*******************
  * From Renderable */
  void Draw();
  void Draw(const bool has_focus);
  

  /*******************
  * From Widget */
  const bool ContainPoint(const Point point) const;
  const bool ContainPoint(const double x, const double y) const;

  void MoveTo(const Point point);
  void MoveTo(const double x, const double y);
  
  void SizeTo(const Widget* model);
  void SizeTo(const double width, const double height);

  card::Card* GetCard(void);
  void SetCard(card::Card* );
  std::string GetTextureName(void);

  FrameWidget* parent() const;
  void setParent(FrameWidget*);

  double width() const;
  //maintains left
  void setWidth(double);

  double height() const;
  //maintains top
  void setHeight(double);
  
  double left() const;
  //maintains width
  void setLeft(double);
  
  double right() const;
  //maintains width
  void setRight(double);
  
  double top() const;
  //maintains height
  void setTop(double);
  
  double bottom() const;
  //maintains height
  void setBottom(double);
  
  double depth() const;
  void setDepth(double);
private:
  //Member Variables
  GameStateManager* game_state_manager_;
  FrameWidget* parent_;
  double flip_width_;
  bool face_up_;
  bool flipping_up_;
  bool dragging_;
  Point drag_point_;
  WidgetLocation current_location_;
  WidgetLocation drag_location_;
  float color_[3];
  SpriteAtlas* atlas_;
  Card* card_;

  static const double FLIP_SPEED;
};

#endif //CARD_WIDGET_H