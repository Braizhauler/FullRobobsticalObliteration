/*******************************************************************************
* File: gamestatemainmenu.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 01
* Version: 0
* Revised: 2015 APR 09
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
  focus_ = nullptr;
  button_1_ = ButtonWidget(game_state_manager_,
                           WidgetLocation (20.0, 6.0, 32.0, 32.0, -1.0));
  button_1_.setColor(0.8f, 0.8f, 0.8f);

  button_2_ = ButtonWidget(game_state_manager_,
                           WidgetLocation (20.0, 6.0, 32.0, 42.0, -1.0));
  button_2_.setColor(0.8f, 0.8f, 0.8f);

  card_1_ = CardWidget(game_state_manager_,
                       WidgetLocation (8.0, 12.0, 10.0, 10.0, 1.0));
}

GameStateMainMenu::~GameStateMainMenu(void) {
}

//Loads the GameStateMainMenu onto the GameStateManager stack in active mode
void GameStateMainMenu::Load() {
  button_1_.MoveTo(32.0, 32.0);
  button_2_.MoveTo(32.0, 42.0);
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

  if(!left_mouse_button_down) {
    if(button_1_.pressed())
      button_1_.setPressed(false);
    if(button_2_.pressed())
      button_2_.setPressed(false);
  }
  if(card_1_.dragging()) {
    card_1_.DragTo(x_position, y_position);
  }
}
void GameStateMainMenu::MouseButtonPressed(int button,
                                           double x_position,
                                           double y_position) {
  if(button_1_.ContainPoint(x_position,y_position) ) {
    button_1_.setPressed(true);
    Focus(&button_1_);
  } else if(button_2_.ContainPoint(x_position,y_position) ) {
    button_2_.setPressed(true);
    Focus(&button_2_);
  } else if(card_1_.ContainPoint(x_position,y_position) ) {
    card_1_.DragStart(x_position,y_position);
    Focus(&card_1_);
  }
}
void GameStateMainMenu::MouseButtonReleased(int button,
                                            double x_position,
                                            double y_position) {
  if(button_1_.pressed())
    button_1_.setPressed(false);
  else if(button_2_.pressed())
    button_2_.setPressed(false);
  else if(card_1_.dragging())
    card_1_.MoveTo(card_1_.DragEnd(x_position,y_position));
}

void GameStateMainMenu::MouseButtonClicked(int button,
                                           double x_position,
                                           double y_position) {
  if(button_1_.ContainPoint(x_position,y_position) ) {
    Activate_Button_Widget(1);
  }
  if(button_2_.ContainPoint(x_position,y_position) ) {
    Activate_Button_Widget(2);
  }
}

void GameStateMainMenu::Activate_Button_Widget(int button_number) {
  const float * button_color;
  switch(button_number) {
    
  case 1:
    button_color = button_1_.color();
    if(button_color[0] == 0.6f)
      button_1_.setColor(0.8f,0.8f,0.8f);
    else
      button_1_.setColor(0.6f,0.7f,0.9f);
    break;
  case 2:
    game_state_manager_->Push(game_state_program_);
    break;
  }
}
//Key Actions
void GameStateMainMenu::Select_Next() {
  if(focus_ == &button_1_) {
    Focus(&button_2_);
  } else if(focus_ == &button_2_) {
    Focus(&card_1_);
  } else if(focus_ == &card_1_) {
    Focus(&button_1_);
  } else {
    Focus(&button_1_);
  }
}
void GameStateMainMenu::Select_Prev() {
}
void GameStateMainMenu::Hotkey(const int position) {
}
void GameStateMainMenu::Activate_Selection() {
  if(focus_!=nullptr) {
    if(focus_==&button_1_)
      Activate_Button_Widget(1);
    if(focus_==&button_2_)
      Activate_Button_Widget(2);
  }
}


bool GameStateMainMenu::Opaque(void) const{
  return false;
}

void GameStateMainMenu::Focus(Focusable* new_focus) {
  focus_ = new_focus;
}

void GameStateMainMenu::Draw() {
  game_state_manager_->TextureAtlas()->getCoordinates("10");
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.00f, 0.05f, 0.05f);
    glTexCoord2d( 0.0,  0.0);
    glVertex3f( 0.0f,  0.0f, 0.0f);
    glTexCoord2d( 1.0,  0.0);
    glVertex3f(84.0f,  0.0f, 0.0f);
    glTexCoord2d( 1.0,  1.0);
    glVertex3f(84.0f, 54.0f, 0.0f);
    glTexCoord2d( 0.0,  1.0);
    glVertex3f( 0.0f, 54.0f, 0.0f);
  glEnd();
  
  glDisable(GL_TEXTURE_2D);

  button_1_.Draw();
  button_2_.Draw();
  card_1_.Draw();
  if(focus_ != nullptr)
    focus_->Draw(true);
}

void GameStateMainMenu::LinkProgramState(GameState* state) {
  game_state_program_ = state;
}