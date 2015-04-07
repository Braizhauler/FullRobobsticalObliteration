/*******************************************************************************
* File: gamestatemanager.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 12
* Version: 0
* Revised: 2015 MAR 12
*
* GameStateProgram:
*   A GameState in which the user recieves a hand of cards, can view the
*   GameBoard, moves their cards into their register, and lock their register. 
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/
#ifndef GAME_STATE_PROGRAM_H_
#define GAME_STATE_PROGRAM_H_

#include "gamestate.h"
#include "cardwidget.h"

class GameStateProgram : public GameState
{
public:
  //Constructors, and Destructor
  GameStateProgram(GameStateManager* manager);
  ~GameStateProgram(void);  
  //Methods

  //causes the GameState to draw all widgets
  void Draw() const;
  //returns true if nothing is no other states are to be drawn under this state.
  bool Opaque() const;

  //Loads the GameState onto the GameStateManager stack in active mode
  void Load();
   
  //Called when GameState when another GameState is preparing
  //to load over this State
  void Cover();

  //Called when GameState when another GameState is preparing
  //becomming the topmost active game state
  void Uncover();

  //Called when the Gamestate is unloaded from the GameStateManager
  void Unload();

  //Mouse Input
  void CursorMove(bool left_mouse_button_down,
                  double x_position,
                  double y_position);
  void MouseButtonPressed(int button,
                          double x_position,
                          double y_position);
  void MouseButtonReleased(int button,
                           double x_position,
                           double y_position);
  void MouseButtonClicked(int button,
                           double x_position,
                           double y_position);
private:
  CardWidget card_;
  GameStateManager* manager_;
};

#endif//GAME_STATE_PROGRAM_H_