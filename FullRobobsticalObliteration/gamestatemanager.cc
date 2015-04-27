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

GameStateManager::GameStateManager(MyWindowWrapper * window):
                                                       game_board_(BOARD_SIZE),
                                   player_robot_(4,&game_board_,
                                                 Point(0.0,0.0),
                                                 Robot::SOUTH){
  window_= window;
  deck_.Shuffle();
}

GameStateManager::~GameStateManager(void) {
}


SpriteAtlas * GameStateManager::TextureAtlas() {
  return &atlas_;
}

CardDeck* GameStateManager::GetCardDeck() {
	return &deck_;
}

RobotController*GameStateManager::GetPlayerRobot() {
  return &player_robot_;
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



void GameStateManager::Select_Next() {
  active_state_.back()->Select_Next();
}
void GameStateManager::Select_Prev() {
  active_state_.back()->Select_Prev();
}
void GameStateManager::Hotkey(const int key_number) {
  active_state_.back()->Hotkey(key_number);
}
void GameStateManager::Activate_Selection() {
  active_state_.back()->Activate_Selection();
}

//Calls the render of all active renderables, from the bottom up
void GameStateManager::Draw() {
  // Set the background to the clear color
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.05f, 0.05f, 0.05f);
    glVertex3f( 0.0f,  0.0f, 0.0f);
    glVertex3f(84.0f,  0.0f, 0.0f);
    glVertex3f(84.0f, 54.0f, 0.0f);
    glVertex3f( 0.0f, 54.0f, 0.0f);
  glEnd();
  for (int i=0; i < active_renderable_.size(); ++i) { //we draw from the bottom up
    active_renderable_[i]->Draw();
  }
}

//Calls the update of all active renderables, from the top down
void GameStateManager::Update() {
  for(int i = (int)active_updatable_.size() - 1; i >= 0; --i) {
    active_updatable_.at(i)->Update();
  }
}

//Exit
void GameStateManager::Exit() {
  window_->Exit();
}


void GameStateManager::RestackRenderables() {
  active_renderable_.clear();
  int number_of_game_states = active_state_.size();
  int game_state_counter;
  for(game_state_counter=number_of_game_states-1;
      game_state_counter>0&&!(active_state_[game_state_counter]->Opaque());
      --game_state_counter);
  while (game_state_counter<number_of_game_states) {
    active_renderable_.push_back(active_state_[game_state_counter]);
    ++game_state_counter;
  }
}