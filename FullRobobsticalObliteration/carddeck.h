/*******************************************************************************
* File: carddeck.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 APR 18
* Version: 0
* Revised: 2015 APR 18 
*
* CardDeck:
*   A logical construct for holding deck of cards and dealing them out randomly
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef CARD_DECK_H_
#define CARD_DECK_H_

#include <vector>       // std::vector
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

namespace Card {
enum CARD_SUIT {
  SUIT_U_TURN,
  SUIT_ROT_LEFT,
  SUIT_ROT_RIGHT,
  SUIT_BACK_UP,
  SUIT_FORWARD_1
};
struct Rally_Card {  
  Rally_Card(void) {suit=SUIT_FORWARD_1; priority=10;}
  Rally_Card(CARD_SUIT card_suit,int card_priority) {
    suit=card_suit; priority=card_priority;}
  CARD_SUIT suit;
  int priority;
};
}//namepace card
using namespace Card;
using std::vector;
class CardDeck
{
public:
  CardDeck(void);
  ~CardDeck(void);
  void Shuffle();
  void Deal();
  Rally_Card* DealACard();
private:
  void InitializeDeck();
  vector<Rally_Card*>::iterator top_card_;
  vector<Rally_Card> card_list_;
  vector<Rally_Card*> card_shuffle_;
};

#endif//CARD_DECK_H_