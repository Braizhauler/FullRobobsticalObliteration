#include "carddeck.h"


CardDeck::CardDeck(void) {
  InitializeDeck();
}


CardDeck::~CardDeck(void) {
}

void CardDeck::InitializeDeck() {
  int count=0;
  while(count<6) { //6 U-Turn
    count++;
    card_list_.push_back(Card::RallyCard(Card::SUIT_U_TURN,count));
  }
  while(count<42) { //18 Right //18 Left
    count++;
    card_list_.push_back(Card::RallyCard(Card::SUIT_ROT_LEFT,count));
    card_list_.push_back(Card::RallyCard(Card::SUIT_ROT_RIGHT,++count));
  }
  while(count<48) { //6 Back up
    count++;
    card_list_.push_back(Card::RallyCard(Card::SUIT_BACK_UP,count));
  }
  while(count<66) { //18 Forward 1
    count++;
    card_list_.push_back(Card::RallyCard(Card::SUIT_FORWARD_1,count));
  }
  count=0;
  while(count<66) {
    card_shuffle_.push_back(&card_list_[count]);
    count++;
  }

}

void CardDeck::Shuffle() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(card_shuffle_.begin(),
          card_shuffle_.end(),
          std::default_random_engine(seed));
  top_card_ = card_shuffle_.begin();
}

Card::RallyCard* CardDeck::DealACard() {
	++top_card_;
	return *(top_card_);
}