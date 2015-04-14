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


GameStateProgram::GameStateProgram(GameStateManager* manager)
{
  manager_=manager;
  dragged_=nullptr;
  player_hand_ = CardHandWidget(manager_,
                       WidgetLocation(33.0, 12.0, 40.0, 38.0, 0.0));
  for(int card_count=0; card_count<9; ++card_count) {
    card_[card_count] = CardWidget(manager_,
                        WidgetLocation (6.0, 9.0,
                                        40.0+card_count*4.0 , 42.0, -1.0));
    player_hand_.addChild(&card_[card_count]);
  }
}

GameStateProgram::~GameStateProgram(void)
{
}

void GameStateProgram::Draw(){
  player_hand_.Draw(focus_);
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
  }
}

void GameStateProgram::MouseButtonPressed(int button,
                                          double x_position,
                                          double y_position){
  CardWidget* temp=player_hand_.ExpandCardAtCursor(x_position, y_position);
  if(temp !=nullptr) {
    dragged_ = temp;
    player_hand_.RaiseCard(temp);
    focus_=(Focusable*)temp;
    dragged_->DragStart(x_position, y_position);
  }
}

void GameStateProgram::MouseButtonReleased(int button,
                                           double x_position,
                                           double y_position){
  if(dragged_!=nullptr) {
    dragged_->DragEnd(x_position, y_position);
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