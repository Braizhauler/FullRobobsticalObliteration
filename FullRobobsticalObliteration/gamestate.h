/*******************************************************************************
* File: gamestate.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 JAN 22
* Version: 0
* Revised: 2015 JAN 24
*
* GameState:
*   An interface for a game states to be used by GameStateManager.
*   Specifies Input hooks and draw, and functions for initialization,
*   and clean up as the game switches states
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "renderable.h"

struct GLFWwindow;
class GameStateManager;

class GameState: public Renderable {
public:
  //Constructors, and Destructor
  virtual ~GameState(void) {}
  //Methods

  //returns true if nothing is no other states are to be drawn under this state.
  virtual bool Opaque() const = 0;

  //Loads the GameState onto the GameStateManager stack in active mode
  virtual void Load() = 0;
   
  //Called when GameState when another GameState is preparing
  //to load over this State
  virtual void Cover() = 0;

  //Called when GameState when another GameState is preparing
  //becomming the topmost active game state
  virtual void Uncover() = 0;

  //Called when the Gamestate is unloaded from the GameStateManager
  virtual void Unload() = 0;

  //Mouse Input
  virtual void CursorMove(bool left_mouse_button_down,
                          double x_position,
                          double y_position) = 0;
  virtual void MouseButtonPressed(int button,
                                  double x_position,
                                  double y_position) = 0;
  virtual void MouseButtonReleased(int button,
                                   double x_position,
                                   double y_position) = 0;
  virtual void MouseButtonClicked(int button,
                                  double x_position,
                                  double y_position) = 0;
  //Key Actions
  virtual void Select_Next() = 0;
  virtual void Select_Prev() = 0;
  virtual void Hotkey(const int) = 0;
  virtual void Activate_Selection() = 0;

  //Accessors and Mutators
private:
};


#endif //GAME_STATE_H

/*
  //Constructors, and Destructor
  //Methods


  //causes the GameState to draw all widgets
  void Draw();
  //returns true if nothing is no other states are to be drawn under this state.
  bool Opaque();

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
                           
*/