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

struct GLFWwindow;
class GameStateManager;

class GameState {
public:
  //Constructors, and Destructor
  GameState(GameStateManager* manager) {
    game_state_manager_ = manager;
  }
  virtual ~GameState(void) {}
  //Methods

  //Loads the GameState onto the GameStateManager stack in active mode
  virtual void Load() {}
   
  //Called when GameState when another GameState is preparing
  //to load over this State
  virtual void Cover() {}

  //Called when GameState when another GameState is preparing
  //becomming the topmost active game state
  virtual void Uncover() {}

  //Called when the Gamestate is unloaded from the GameStateManager
  virtual void Unload() {}


  //Accessors and Mutators
private:
  //Member Variables
  GameStateManager* game_state_manager_;
};


#endif //GAME_STATE_H