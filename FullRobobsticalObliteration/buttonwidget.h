/*******************************************************************************
* File: buttonwidget.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 FEB 17
* Version: 0
* Revised: 2015 MAR 27
*
* Button_Widget:
*   A gui widget which has a responds to mouse clicks
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef BUTTON_WIDGET_H
#define BUTTON_WIDGET_H

#include <list>

#include "gamestatemanager.h"
#include "widget.h"
#include "framewidget.h"
#include "widgetlocation.h"
#include "focusable.h"



class ButtonWidget: public Widget, public Focusable
{
public:
  //Constructors, and Destructor
  ButtonWidget(GameStateManager* manager = nullptr);
  ButtonWidget(GameStateManager* manager, const WidgetLocation location);
  ~ButtonWidget(void);

  void Draw();
  void Draw(const bool has_focus);
  
  const bool ContainPoint(const Point point) const;
  const bool ContainPoint(const double x, const double y) const;

  void MoveTo(const Point point);
  void MoveTo(const double x, const double y);

  void SizeTo(const Widget* model);
  void SizeTo(const double width, const double height);

  //Methods
  FrameWidget* parent() const;
  void setParent(FrameWidget*);

  //Accessors and Mutators
  const bool pressed() const;
  void setPressed(bool);

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

  const float* color();
  void setColor(const float red, const float green, const float blue);
private:
  //Member Variables
  GameStateManager* game_state_manager_;
  FrameWidget* parent_;

  WidgetLocation current_location_;

  bool is_pressed_;

  float button_color_[3]; //0 red; 1 green; 2 blue;
  float button_shadow_[3]; //0 red; 1 green; 2 blue;
  float pressed_color_[3]; //0 red; 1 green; 2 blue;
  float pressed_shadow_[3]; //0 red; 1 green; 2 blue;
};


#endif //BUTTON_WIDGET_H