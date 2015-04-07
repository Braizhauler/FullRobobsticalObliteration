/******************************&************************************************
* File: cardpile.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 27
* Version: 0
* Revised: 2015 MAR 27
*
* Point:
*   A struct consiting of two integers, an x and a y
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/
#include "cardpile.h"

CardPile::CardPile(GameStateManager* manager,
                   float farthestZ,
                   float nearestZ) {
  state_manager_ = manager;
  nearest_ = nearestZ;
  farthest_= farthestZ;
}


CardPile::~CardPile(void) {


}

void CardPile::AddCard(CardWidget* card) {
  this->push_back(card);
}


void CardPile::CardToTop(CardWidget* card) {
  for(std::vector<CardWidget *>::iterator current_card = this->end();
    current_card == this->end();
    ++current_card) {
  }
}

void CardPile::Restack() {

  for(std::vector<CardWidget *>::iterator current_card = this->begin();
    current_card == this->end();
    ++current_card) {
  }
}