/*******************************************************************************
* File: cardpile.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 FEB 17
* Version: 0
* Revised: 2015 MAR 27
*
* Card_Pile:
*   A structure for holding Card_Widgets to keep their z-orders in order
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef CARD_PILE_H
#define CARD_PILE_H

#include <vector>

//#include "gamestate.h"
#include "widget.h"
#include "cardwidget.h"

class GameState;

class CardPile: public std::vector<CardWidget *>
{
public:
  //Constructors, and Destructor
  CardPile(GameStateManager* manager = nullptr,
           float farthestZ = 0.0f,
           float nearestZ  = 1.0f);
  ~CardPile(void);

  void AddCard(CardWidget*);
  
  void CardToTop(CardWidget*);

  void Restack();
private:
  //Member Variables
  GameStateManager* state_manager_;

  float nearest_;
  float farthest_;
};


#endif //CARD_PILE_H