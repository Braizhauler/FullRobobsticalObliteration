/*******************************************************************************
* File: gamestatemanager.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2014 DEC 22
* Version: 0
* Revised: 2014 DEC 24
*
* GameStateManager:
*   A file for keeping track of current state, and redirecting calls to
*   all active game states/logic.
*
* © [2014] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <stack>
#include <vector>
#include <glfw3.h>

#include "gamestate.h"
#include "renderable.h"
//#include "updateable.h"

class GameStateManager {
public:
  //Constructors and Destructor
  GameStateManager(void);
  ~GameStateManager(void);
  //Methods
  GameState Pop();
  GameState Peek();
  void Push(GameState new_state);

  void Render();
  void Update(double elapsed_time_in_ms);
  //Accessors and Mutators
private:
  //Member Variables
  std::stack<GameState> current_state_;
  std::vector<Renderable> active_renderable_;
  //std::vector<Updateable> active_updatable_;
};


#endif //GAME_STATE_MANAGER_H