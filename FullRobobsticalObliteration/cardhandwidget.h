/*******************************************************************************
* File: cardhandwidget.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 30
* Version: 0
* Revised: 2015 MAR 30
*
* Button_Widget:
*   A gui widget which has a responds to mouse clicks
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef CARD_HAND_WIDGET_H
#define CARD_HAND_WIDGET_H

#include "gamestatemanager.h"
#include "widget.h"

class CardHandWidget: public Widget{
public:
  CardHandWidget(GameStateManager* manager);
  ~CardHandWidget(void);

  /********************
  * From Widget      */  
  const bool containPoint(Point point);
  const bool containPoint(double x, double y);

  Widget* parent();
  void setParent(Widget*);
  
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

  /*************************
  * From RectangleInSpace */
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

  /*******************
  * From Renderable */
  void Draw();

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
};
#endif//CARD_HAND_WIDGET_H