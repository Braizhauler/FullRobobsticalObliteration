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
  card_ = CardWidget(manager_,
                     WidgetLocation (8.0, 12.0, 10.0, 10.0, 1.0));
}

GameStateProgram::~GameStateProgram(void)
{
}

void GameStateProgram::Draw() const{
  card_.Draw();
}

//returns true if nothing is no other states are to be drawn under this state.
bool GameStateProgram::Opaque() const {
  return true;
}

//Loads the GameState onto the GameStateManager stack in active mode
void GameStateProgram::Load() {
  card_.MoveTo(10.0, 10.0); 
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
}

void GameStateProgram::MouseButtonPressed(int button,
                                          double x_position,
                                          double y_position){
}

void GameStateProgram::MouseButtonReleased(int button,
                                           double x_position,
                                           double y_position){
}

void GameStateProgram::MouseButtonClicked(int button,
                                          double x_position,
                                          double y_position){
}

//Key Actions
void GameStateProgram::Select_Next() {
}
void GameStateProgram::Select_Prev() {
}
void GameStateProgram::Hotkey(const int) {
}
void GameStateProgram::Activate_Selection() {
}