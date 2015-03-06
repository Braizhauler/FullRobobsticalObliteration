/*******************************************************************************
* File: button.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 FEB 17
* Version: 0
* Revised: 2015 FEB 17
*
* Button:
*   An interface for a game states to be used by GameStateManager.
*   Specifies Input hooks and draw, and functions for initialization,
*   and clean up as the game switches states
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef BUTTON_H
#define BUTTON_H

#include <list>

#include "gamestatemanager.h"
#include "widget.h"

class Button: public Widget {
public:
  //Constructors, and Destructor
  Button(GameStateManager* manager);
  ~Button(void);
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


#endif //GAME_STATE_H