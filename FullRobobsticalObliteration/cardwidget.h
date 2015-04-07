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
* � [2015] Dwarfholm.com
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

class CardWidget: public Widget, public Focusable
{
public:
  //Constructors, and Destructor
  CardWidget(GameStateManager* manager = nullptr);
  CardWidget(GameStateManager* manager, const WidgetLocation location);
  ~CardWidget(void);

  void Draw(void) const;
  void Draw(const bool has_focus) const;
  
  const bool containPoint(Point point);
  const bool containPoint(double x, double y);

  //Methods
  const FrameWidget* parent() const;
  void setParent(FrameWidget*);

  const double width() const;
  //maintains left
  void setWidth(double);

  const double height() const;
  //maintains top
  void setHeight(double);
  
  const double left() const;
  //maintains width
  void setLeft(double);
  
  const double right() const;
  //maintains width
  void setRight(double);
  
  const double top() const;
  //maintains height
  void setTop(double);
  
  const double bottom() const;
  //maintains height
  void setBottom(double);
  
  const double depth() const;
  void setDepth(double);

  const float* color();
  void setColor(const float red, const float green, const float blue);
private:
  //Member Variables
  GameStateManager* game_state_manager_;
  FrameWidget* parent_;
  bool dragging;
  WidgetLocation current_location_;
  WidgetLocation former_location_;
  float color_[3];
};


#endif //CARD_WIDGET_H