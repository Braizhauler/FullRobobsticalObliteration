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
* � [2015] Dwarfholm.com
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

  /**********************
  * RectangleInSpace   */
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

  /*******************
  * From Renderable */
  void Draw();
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
};


#endif //FRAME_WIDGET_H