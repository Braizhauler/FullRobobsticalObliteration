/*******************************************************************************
* File: cardhandwidget.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 30
* Version: 0
* Revised: 2015 APR 09
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
#include "framewidget.h"
#include "cardwidget.h"

class CardHandWidget: public FrameWidget{
public:
  CardHandWidget(GameStateManager* manager=nullptr);
  CardHandWidget(GameStateManager* manager,WidgetLocation location);
  ~CardHandWidget(void);

  /*******************
  * From Renderable */
  void Draw();

  void Nuetral();
  
  //Takes cursor coodinates
  //Returns an int for the card number the cursor is over.
  int CusorOverCard(const double x, const double y);
  void ExpandCard(int card_number);
  void RaiseCard(int card_number);
private:
};
#endif//CARD_HAND_WIDGET_H