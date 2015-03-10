/******************************&************************************************
* File: widget.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 FEB 12
* Version: 0
* Revised: 2015 FEB 12
*
* Widget:
*   An interface for all user interface elements
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef WIDGET_H
#define WIDGET_H


#include <list>

#include "rectangleinspace.h"

class Widget: public RectangleInSpace, public Renderable {
public:
  //inform children and parent when you are deconstructed
  virtual ~Widget(void) {}

  virtual Widget* parent()=0;
  virtual void setParent(Widget*)=0;

  
  virtual bool isChild(Widget*)=0;
  virtual Widget* child(int)=0;
  virtual std::list<Widget*> children()=0;

  //informs the child to clear their parent,
  //then clears the child from our record
  virtual void clearChild(Widget*)=0; 

  // informs all children to to clear their parent,
  //    then clears the all children from the our record
  virtual void clearChildren()=0;
  

  //calls the child's decontructor then removes it from our children record
  virtual void deleteChild(int)=0;

  //calls each childs' decontructor then removes them from our children record
  virtual void deleteChildren()=0; 

  //adds the passed widget to our children record
  virtual void addChild(Widget*)=0;


};

#endif //WIDGET_H