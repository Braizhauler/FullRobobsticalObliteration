/*******************************************************************************
* File: cardhandwidget.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 30
* Version: 0
* Revised: 2015 APR 13
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
#include "cardwidget.h"


class CardHandWidget: public Widget{
public:
  CardHandWidget(GameStateManager* manager=nullptr);
  CardHandWidget(GameStateManager* manager,WidgetLocation location);
  ~CardHandWidget(void);

  void addChild(CardWidget* new_child);

  //returns true if argument is a child of this
  const bool isChild(CardWidget* widget);

  //returns the list of widget pointers that are children of this
  std::list<CardWidget*> children();

  //informs the child to clear their parent,
  //then clears the child from our record
  void ClearChild(CardWidget*); 

  // informs all children to to clear their parent,
  //    then clears the all children from the our record
  void ClearChildren(); 

  //adds the passed widget to our children record
  void addChild(Widget*);
  /*******************
  * From Widget */
  virtual FrameWidget* parent() const;
  virtual void setParent(FrameWidget*);

  const bool ContainPoint(const Point point) const;
  const bool ContainPoint(const double x, const double y) const;

  void MoveTo(const Point point);
  void MoveTo(const double x, const double y);

  void SizeTo(const Widget* model);
  void SizeTo(const double width, const double height);

  void Draw(Focusable*);
  /*******************
  * From Renderable */
  void Draw();
  
  //Accepts a widget
  //if it is a child of the CardHandWidget
  //returns the next child in the list
  //return nullptr if it is the last child in the list
  //returns the first widget if the widget is not a child of CardHandWidget
  CardWidget* NextCard(Widget*);
  //Takes cursor coodinates
  //Returns an int for the card number the cursor is over.
  //Returns nullptr if mouse over not over a card in cardhandwidget.
  CardWidget* CardAtCursor(const double x, const double y);
  //Takes cursor coodinates
  //Expands that card
  //Returns an int for the card number the cursor is over.
  //Returns nullptr if mouse over not over a card in cardhandwidget.
  CardWidget* ExpandCardAtCursor(const double x, const double y);
  void ExpandCard(CardWidget* card_number);
  void RaiseCard(CardWidget* card_number);
  void LowerAllCards();
  void CollapseAllCards();

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
private:
  static const double CARD_EXPOSE_RATE;

  GameStateManager* game_state_manager_;
  FrameWidget* parent_;
  std::list<CardWidget*> child_list_;
  WidgetLocation current_location_;

  int cards_total_;
  double card_width_;
  double card_height_;
  double card_spacing_;
  CardWidget* card_expanded_;
  CardWidget* card_raised_;
};


#endif//CARD_HAND_WIDGET_H