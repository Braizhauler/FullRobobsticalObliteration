/*******************************************************************************
* File: buttonwidget.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 FEB 17
* Version: 0
* Revised: 2015 MAR 10
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

class ButtonWidget: public Widget {
public:
  //Constructors, and Destructor
  ButtonWidget(GameStateManager* manager = nullptr);
  ~ButtonWidget(void);

  void Draw(void);
  
  bool containPoint(Point point);
  bool containPoint(double x, double y);

  //Methods
  Widget* parent();
  void setParent(Widget*);

  //returns true if argument is a child of this
  bool isChild(Widget* widget);
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

  double width();
  //maintains left
  void setWidth(double);

  double height();
  //maintains top
  void setHeight(double);
  
  double left();
  //maintains width
  void setLeft(double);
  
  double right();
  //maintains width
  void setRight(double);
  
  double top();
  //maintains height
  void setTop(double);
  
  double bottom();
  //maintains height
  void setBottom(double);
  
  double depth();
  void setDepth(double);

  const float* color();
  void setColor(const float red, const float green, const float blue);
private:
  //Member Variables
  GameStateManager* game_state_manager_;
  Widget* parent_;
  std::list<Widget*> child_list_;
  double top_;
  double left_;
  double right_;
  double bottom_;
  double depth_;
  float color_[3]; //0 red; 1 green; 2 blue;
};


#endif //BUTTON_WIDGET_H