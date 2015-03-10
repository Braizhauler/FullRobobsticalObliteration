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
  GameState* temp = active_state_.back();
  temp->Unload();
  active_state_.pop_back();
  if(active_state_.size() > 0)
    active_state_.back()->Uncover();
  RestackRenderables();
  return temp;
}

//Peek returns a pointer to top state of the state stack, and leaving it on the
//stack
GameState* GameStateManager::Peek() {
  return active_state_.back();
}

void GameStateManager::Push(GameState* new_state) {
  if (active_state_.size() > 0)
    active_state_.back()->Cover();
  new_state->Load();
  active_state_.push_back(new_state);
  RestackRenderables();
}

/*******************************
* Mouse Input                 */
void GameStateManager::CursorMove(bool left_mouse_button_down,
                                  double x_position,
                                  double y_position) {
  active_state_.back()->CursorMove(left_mouse_button_down,
                                   x_position,
                                   y_position);
}
void GameStateManager::MouseButtonPressed(int button,
                                          double x_position,
                                          double y_position) {
  active_state_.back()->MouseButtonPressed(button,
                                           x_position,
                                           y_position);
}
void GameStateManager::MouseButtonReleased(int button,
                                           double x_position,
                                           double y_position) {
  active_state_.back()->MouseButtonReleased(button,
                                            x_position,
                                            y_position);
}
void GameStateManager::MouseButtonClicked(int button,
                                          double  x_position,
                                          double  y_position) {
  active_state_.back()->MouseButtonClicked(button,
                                           x_position,
                                           y_position);
}



//Calls the render of all active renderables, from the bottom up
void GameStateManager::Draw() {
  
  // Set the background to the clear color
  glClear(GL_COLOR_BUFFER_BIT);
  for (int i=0; i < active_renderable_.size(); ++i) { //we draw from the bottom up
    active_renderable_[i]->Draw();
  }
}

//Calls the update of all active renderables, from the top down
void GameStateManager::Update(GameTime currentTime) {
  for(int i = (int)active_updatable_.size() - 1; i >= 0; --i) {
    active_updatable_.at(i)->Update(currentTime);
  }
}

//Exit
void GameStateManager::Exit() {
  window_->Exit();
}


void GameStateManager::RestackRenderables() {
  active_renderable_.clear();
  std::vector<GameState*>::reverse_iterator renderable_inspector;
  std::vector<GameState*>::reverse_iterator b = active_state_.rbegin();
  std::vector<GameState*>::reverse_iterator e = active_state_.rend();
  for(renderable_inspector = active_state_.rbegin();
      renderable_inspector != active_state_.rend() &&
      !( (*renderable_inspector)->Opaque() );
      ++renderable_inspector)
    {}
      
  while (renderable_inspector != active_state_.rbegin()) {
    --renderable_inspector;
    active_renderable_.push_back(*renderable_inspector);
  }
}