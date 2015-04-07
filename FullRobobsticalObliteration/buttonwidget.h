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

  void Draw(void) const;
  void Draw(const bool has_focus) const;
  
  const bool containPoint(const Point point) const;
  const bool containPoint(const double x, const double y) const;

  void MoveTo(const Point point);

  //Methods
  FrameWidget* parent() const;
  void setParent(FrameWidget*);

  //returns true if argument is a child of this
  const bool isChild(Widget* widget);
  //returns a widget in position child_number
  Widget* child(int child_number);
  //returns the list of widget pointers that are children of this
  std::list<Widget*> children();

  //informs the child to clear their parent,
  //then clears the child from our record
  void clearChild(int); 
  void clearChild(Widget*); 

  // informs all children to to clear their parent,
  //    then clears the all children from the our record
  void clearChildren(); 

  //calls the child's decontructor then removes it from our children record
  void deleteChild(int);

  //calls each childs' decontructor then removes them from our children record
  void deleteChildren(); 

  //adds the passed widget to our children record
  void addChild(Widget*);

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
  std::list<Widget*> child_list_;
  double top_;
  double left_;
  double right_;
  double bottom_;
  double depth_;

  bool is_pressed_;

  float button_color_[3]; //0 red; 1 green; 2 blue;
  float button_shadow_[3]; //0 red; 1 green; 2 blue;
  float pressed_color_[3]; //0 red; 1 green; 2 blue;
  float pressed_shadow_[3]; //0 red; 1 green; 2 blue;
};


#endif //BUTTON_WIDGET_H