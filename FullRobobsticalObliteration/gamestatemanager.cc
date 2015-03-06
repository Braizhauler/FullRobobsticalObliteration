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

GameStateManager::GameStateManager(MyWindowWrapper * window) {
  window_= window;
}

GameStateManager::~GameStateManager(void) {
}

/*******************************
* Methods                    */
//Pop returns the top state of the state stack, and removes it from the stack
GameState* GameStateManager::Pop() {
  GameState* temp = current_state_.top();
  temp->Unload();
  current_state_.pop();
  current_state_.top()->Uncover();
  return temp;
}

//Peek returns a pointer to top state of the state stack, and leaving it on the
//stack
GameState* GameStateManager::Peek() {
  return current_state_.top();
}

void GameStateManager::Push(GameState* new_state) {
  current_state_.top()->Cover();
  new_state->Load();
  current_state_.push(new_state);
}

//Calls the render of all active renderables, from the bottom up
void GameStateManager::Draw() {
  for (int i=0; active_renderable_.size(); ++i) { //we draw from the bottom up
    active_renderable_.at(i)->Draw();
  }
}

//Calls the update of all active renderables, from the top down
void GameStateManager::Update(GameTime currentTime) {
  for(int i = active_updatable_.size() - 1; i >= 0; --i) {
    active_updatable_.at(i)->Update(currentTime);
  }
}

//Exit
void GameStateManager::Exit() {
  window_->Exit();
}