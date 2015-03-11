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
  button_ = ButtonWidget(game_state_manager_);
  button_.setColor(1.0f, 0.0f, 0.5f);
  button_.setTop(3.0);
  button_.setLeft(3.0);
  button_.setHeight(3.0);
  button_.setWidth(3.0);
  button_.setDepth(-1.0);
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
}
void GameStateMainMenu::MouseButtonPressed(int button,
                                           double x_position,
                                           double y_position) {
}
void GameStateMainMenu::MouseButtonReleased(int button,
                                            double x_position,
                                            double y_position) {
}
void GameStateMainMenu::MouseButtonClicked(int button,
                                           double x_position,
                                           double y_position) {
  if(button_.containPoint(x_position,y_position) )
    button_.setColor(0.0f,1.0f,0.0f);
}


bool GameStateMainMenu::Opaque(void) {
  return false;
}

void GameStateMainMenu::Draw(void) {
  glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f( 0.0f,  0.0f, 0.0f);
    glVertex3f(84.0f,  0.0f, 0.0f);
    glVertex3f(84.0f, 54.0f, 0.0f);
    glVertex3f( 0.0f, 54.0f, 0.0f);
  glEnd();
  button_.Draw();
}