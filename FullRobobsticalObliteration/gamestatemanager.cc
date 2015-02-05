/*******************************************************************************
* File: gamestatemanager.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 JAN 22
* Version: 0
* Revised: 2015 JAN 23
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "gamestatemanager.h"

/*******************************
* Constructors and Destructor */

GameStateManager::GameStateManager(void) {
}
GameStateManager::~GameStateManager(void) {
}

/*******************************
* Methods                    */
//Pop returns the top state of the state stack, and removes it from the stack
GameState GameStateManager::Pop() {
  GameState temp = current_state_.top();
  temp.Unload();
  current_state_.pop();
  current_state_.top().Uncover();
  return temp;
}

//Peek returns the top state of the state stack, and leaves it on the stack
GameState GameStateManager::Peek() {
  return current_state_.top();
}

void GameStateManager::Push(GameState new_state) {
  current_state_.top().Cover();
  new_state.Load();
  current_state_.push(new_state);
}

//Calls the render of all active renderables, from the bottom up
void GameStateManager::Render() {
  for (int i=0; active_renderables_.size(); ++i) { //we draw from the bottom up
    active_renderables_.at(i).Render();
  }
}

//Calls the update of all active renderables, from the top down
void GameStateManager::Update(double elapsed_time_in_ms) {
  for(int i = active_updatable_.size() - 1; i >= 0; --i) {
    active_updatable_.at(i).Update(elapsed_time_in_ms);
  }
}

