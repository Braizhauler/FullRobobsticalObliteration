/*******************************************************************************
* File: gamestatemainmenu.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 01
* Version: 0
* Revised: 2015 MAR 01
*
* GameStateMainMenu:
*   An implementation of GameState for a game states to be used by
*   GameStateManager.
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/
#include "gamestatemainmenu.h"


GameStateMainMenu::GameStateMainMenu(GameStateManager* manager) {
  game_state_manager_ = manager;
  button_1_ = ButtonWidget(game_state_manager_);
  button_1_.setColor(0.8f, 0.8f, 0.8f);
  button_1_.setTop(3.0);
  button_1_.setLeft(3.0);
  button_1_.setHeight(3.0);
  button_1_.setWidth(6.0);
  button_1_.setDepth(-1.0);

  button_2_ = ButtonWidget(game_state_manager_);
  button_2_.setColor(0.8f, 0.8f, 0.8f);
  button_2_.setTop(3.0);
  button_2_.setLeft(10.0);
  button_2_.setHeight(3.0);
  button_2_.setWidth(6.0);
  button_2_.setDepth(-1.0);
}

GameStateMainMenu::~GameStateMainMenu(void) {
}

//Loads the GameStateMainMenu onto the GameStateManager stack in active mode
void GameStateMainMenu::Load() {
}

//Called when GameState when another GameState is preparing
//to load over this State
void GameStateMainMenu::Cover() {
}

//Called when GameState when another GameState is preparing
//becomming the topmost active game state
void GameStateMainMenu::Uncover() {
}

//Called when the Gamestate is unloaded from the GameStateManager
void GameStateMainMenu::Unload() {
}

void GameStateMainMenu::CursorMove(bool left_mouse_button_down,
                                   double x_position,
                                   double y_position) {
  if(!left_mouse_button_down) {
    if(button_1_.pressed())
      button_1_.setPressed(false);
    if(button_2_.pressed())
      button_2_.setPressed(false);
  }
}
void GameStateMainMenu::MouseButtonPressed(int button,
                                           double x_position,
                                           double y_position) {
  if(button_1_.containPoint(x_position,y_position) ) {
    button_1_.setPressed(true);
    Focus(&button_1_);
  }
  if(button_2_.containPoint(x_position,y_position) ) {
    button_2_.setPressed(true);
    Focus(&button_2_);
  }
}
void GameStateMainMenu::MouseButtonReleased(int button,
                                            double x_position,
                                            double y_position) {
  if(button_1_.pressed())
    button_1_.setPressed(false);
  if(button_2_.pressed())
    button_2_.setPressed(false);
}
void GameStateMainMenu::MouseButtonClicked(int button,
                                           double x_position,
                                           double y_position) {
  if(button_1_.containPoint(x_position,y_position) ) {
    const float * button_1_color( button_1_.color() );
    if(button_1_color[0] == 0.6f)
      button_1_.setColor(0.8f,0.8f,0.8f);
    else
      button_1_.setColor(0.6f,0.7f,0.9f);
  }
  if(button_2_.containPoint(x_position,y_position) ) {
    const float * button_2_color( button_2_.color() );
    if(button_2_color[0] == 0.6f)
      button_2_.setColor(0.8f,0.8f,0.8f);
    else
      button_2_.setColor(0.6f,0.7f,0.9f);
  }
}

bool GameStateMainMenu::Opaque(void) {
  return false;
}

void GameStateMainMenu::Focus(Widget* new_focus) {
  button_1_.clearFocus();
  button_2_.clearFocus();
  new_focus->setFocus();
}

void GameStateMainMenu::Draw(void) {
  button_1_.Draw();
  button_2_.Draw();
}