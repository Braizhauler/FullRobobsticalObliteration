/*******************************************************************************
* File: framewidget.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 06
* Version: 0
* Revised: 2015 MAR 06
*
* FrameWidget:
*   A basic gui widget primarily ment for use as a widget container
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef FRAME_WIDGET_H
#define FRAME_WIDGET_H

#include <list>

#include "gamestatemanager.h"
#include "widget.h"

class FrameWidget: public Widget {
public:
  //Constructors, and Destructor
  FrameWidget(GameStateManager* manager);
  ~FrameWidget(void);


  /*******************
  * From Widget */
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

  int width();
  //maintains left
  void setWidth(int);

  int height();
  //maintains top
  void setHeight(int);
  
  int left();
  //maintains width
  void setLeft(int);
  
  int right();
  //maintains width
  void setRight(int);
  
  int top();
  //maintains height
  void setTop(int);
  
  int bottom();
  //maintains height
  void setBottom(int);
  
  float depth();
  void setDepth(float);

  /*******************
  * From Renderable */
  void Draw();
private:
  //Member Variables
  GameStateManager* game_state_manager_;
  Widget* parent_;
  std::list<Widget*> child_list_;
  int top_;
  int left_;
  int right_;
  int bottom_;
  float depth_;
};


#endif //FRAME_WIDGET_H