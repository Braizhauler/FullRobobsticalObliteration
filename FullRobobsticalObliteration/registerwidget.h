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

#ifndef REGISTER_WIDGET_H
#define REGISTER_WIDGET_H

#include "widget.h"
#include "framewidget.h"
#include "cardwidget.h"

class RegisterWidget: public Widget {
public:
  RegisterWidget(void);
  RegisterWidget(GameStateManager* manager,WidgetLocation location);
  ~RegisterWidget(void);

  const bool PointInSlot(const double x, const double y) const;

  void SetCard(CardWidget*);
  CardWidget* Card() const;
  bool IsClear() const;

  //returns true if:
  //x is between left and right
  //y is between top and bottom
  const bool ContainPoint(const double x, const double y) const;
  const bool ContainPoint(const Point) const;

  void MoveTo(const Point);
  void MoveTo(const double x, const double y);

  void SizeTo(const Widget *);
  void SizeTo(const double width, const double height);
  
  FrameWidget* parent() const;
  void setParent(FrameWidget*);

  void Draw();

  double width() const;
  double height() const;
  void setWidth(double);
  void setHeight(double);

  double left() const;
  double right() const;
  double top() const;
  double bottom() const;
  
  void setLeft(double);
  void setRight(double);
  void setTop(double);
  void setBottom(double);

  double depth() const;
  void setDepth(double);
private:
  void CenterSlot();

  WidgetLocation current_location_;
  WidgetLocation card_slot_location_;
  CardWidget* programmed_card_;
  GameStateManager* game_state_manager_;
  FrameWidget* parent_;
};

#endif//REGISTER_WIDGET_H