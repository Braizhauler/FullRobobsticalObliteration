/*******************************************************************************
* File: gamestatemanager.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 12
* Version: 0
* Revised: 2015 APR 08
*
* GameStateProgram:
*   A GameState in which the user recieves a hand of cards, can view the
*   GameBoard, moves their cards into their register, and lock their register. 
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/
#include "gamestateprogram.h"


GameStateProgram::GameStateProgram(GameStateManager* manager):
                              board_(manager,
                                    WidgetLocation(84.0, 42.0, 0.0, 0.0, 0.0)) {
  manager_=manager;
  dragged_=nullptr;
  register_dragging_from_=-1;
  player_hand_ = CardHandWidget(manager_,
                       WidgetLocation(33.0, 17.0, 51.0, 38.0, 0.0));
  confirm_button_= ButtonWidget(manager_,
                       WidgetLocation(6.0, 4.0, 40.0, 48.0, 0.0));
  for(int register_count=0;register_count<NUMBER_OF_REGISTERS;++register_count){
    register_[register_count]=
                RegisterWidget(manager,
                               WidgetLocation(8.0,14.0,
                                              0.0+register_count*8.0,40.0,
                                              0.0));
  }
  for(int card_count=0; card_count<MAX_NUMBER_OF_CARDS_IN_HAND; ++card_count) {
    card_[card_count] = CardWidget(manager_,
                                   WidgetLocation(7.2, 10.8,
                                                40.0+card_count*4.0,44.0,-1.0));
    card_[card_count].SetCard(manager->GetCardDeck()->DealACard());
    player_hand_.addChild(&card_[card_count]);
  }
  last_mouse_position_ = Point(0.0,0.0);
}

GameStateProgram::~GameStateProgram(void) {
}

void GameStateProgram::Draw(){
  board_.Draw();
  confirm_button_.Draw();
  for(int register_count=0;register_count<NUMBER_OF_REGISTERS;++register_count)
    register_[register_count].Draw();
  player_hand_.Draw(focus_);
  if(dragged_!=nullptr)
    dragged_->Draw();
}

//returns true if nothing is no other states are to be drawn under this state.
bool GameStateProgram::Opaque() const {
  return true;
}

//Loads the GameState onto the GameStateManager stack in active mode
void GameStateProgram::Load() {

}

//Called when GameState when another GameState is preparing
//to load over this State
void GameStateProgram::Cover() {
}

//Called when GameState when another GameState is preparing
//becomming the topmost active game state
void GameStateProgram::Uncover() {
}

//Called when the Gamestate is unloaded from the GameStateManager
void GameStateProgram::Unload() {
}

//Mouse Input
void GameStateProgram::CursorMove(bool left_mouse_button_down,
                                  double x_position,
                                  double y_position){
  if(dragged_!=nullptr)
    dragged_->DragTo(x_position, y_position);
  else {
    CardWidget* card_at_cursor = player_hand_.CardAtCursor(x_position, y_position);
    if(card_at_cursor!=nullptr) {
      player_hand_.ExpandCard(card_at_cursor);
    }
    
    if(left_mouse_button_down) {
      if(board_.ContainPoint(x_position,y_position)) {
          board_.setAngle(board_.angle()
                          +(0.2*(y_position-18.0)* 
                          (last_mouse_position_.x-x_position)));
          board_.setAngle(board_.angle()
                          +(0.2*(y_position-18.0)* 
                          (last_mouse_position_.x-x_position)));
      }
    }
  }
  last_mouse_position_ = Point(x_position,y_position);
}

void GameStateProgram::MouseButtonPressed(int button,
                                          double x_position,
                                          double y_position){
  last_mouse_position_ = Point(x_position,y_position);
  CardWidget* temp=player_hand_.ExpandCardAtCursor(x_position, y_position);
  if(temp !=nullptr) {
    dragged_ = temp;
    player_hand_.RaiseCard(temp);
    focus_=(Focusable*)temp;
    dragged_->DragStart(x_position, y_position);
  } else {
    for(int current_register=0;
        current_register<NUMBER_OF_REGISTERS;
        ++current_register) {
      if(!register_[current_register].IsClear()) {
        if(register_[current_register].PointInSlot(x_position, y_position)) {
          dragged_= register_[current_register].Card();
          dragged_->DragStart(x_position, y_position);
          register_dragging_from_=current_register;
        }
      }
    }
  }
}

void GameStateProgram::MouseButtonReleased(int button,
                                           double x_position,
                                           double y_position){
  if(dragged_!=nullptr) {
    dragged_->DragEnd(x_position, y_position);
    if(register_dragging_from_>=0) {
      register_[register_dragging_from_].SetCard(nullptr);
      register_dragging_from_=-1;
    }
    bool card_added_to_register=false;
    for(int slot=0;slot<NUMBER_OF_REGISTERS;++slot) {
      if(register_[slot].IsClear()&&
         register_[slot].PointInSlot(x_position, y_position)) {
        player_hand_.ClearChild(dragged_);
        register_[slot].SetCard(dragged_);
        card_added_to_register=true;
      }
    }
    if(!card_added_to_register)
      player_hand_.addChild(dragged_);
    dragged_=nullptr;
  }
  player_hand_.CollapseAllCards();
}

void GameStateProgram::MouseButtonClicked(int button,
                                          double x_position,
                                          double y_position){                                         
  CardWidget* temp=player_hand_.ExpandCardAtCursor(x_position, y_position);
  if(temp !=nullptr) {
    focus_=(Focusable*)temp;
  }
}

//Key Actions
void GameStateProgram::Select_Next() {
  focus_=(Focusable*)player_hand_.NextCard((Widget*)focus_);
}
void GameStateProgram::Select_Prev() {
}
void GameStateProgram::Hotkey(const int) {
}
void GameStateProgram::Activate_Selection() {
}