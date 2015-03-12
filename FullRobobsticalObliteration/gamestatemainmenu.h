/*******************************************************************************
* File: gamestatemainmenu.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 01
* Version: 0
* Revised: 2015 MAR 12
*
* GameStateMainMenu:
*   An implementation of GameState for a game states to be used by
*   GameStateManager.
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef GAME_STATE_MAIN_MENU_H
#define GAME_STATE_MAIN_MENU_H

#include <GL/glew.h>
#include <iostream>

#include "gamestate.h"
#include "renderable.h"
#include "focusable.h"
#include "framewidget.h"
#include "buttonwidget.h"

class GameStateMainMenu : public GameState
{
public:
  GameStateMainMenu(GameStateManager* manager);
  ~GameStateMainMenu(void);
  //Methods

  //Loads the GameStateMainMenu onto the GameStateManager stack in active mode
  void Load();
   
  //Called when GameState when another GameState is preparing
  //to load over this State
  void Cover();

  //Called when GameState when another GameState is preparing
  //becomming the topmost active game state
  void Uncover();

  //Called when the Gamestate is unloaded from the GameStateManager
  void Unload();

  void CursorMove(bool left_mouse_button_down,
                  double x_position,
                  double y_position);
  void MouseButtonPressed(int button, double x_position, double y_position);
  void MouseButtonReleased(int button, double x_position, double y_position);
  void MouseButtonClicked(int button, double x_position, double y_position);

  bool Opaque(void) const;

  void Focus(Focusable* new_focus);

  void Draw(void) const;
private:
  //Member Variables
  GameStateManager* game_state_manager_;
  Focusable* focus_;
  ButtonWidget button_1_;
  ButtonWidget button_2_;
};



#endif //GAME_STATE_MAIN_MENU_H