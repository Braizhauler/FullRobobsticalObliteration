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
  deck_ = game_state_manager_->GetCardDeck();
  deck_->Shuffle();

  focus_ = nullptr;
  button_1_ = ButtonWidget(game_state_manager_,
                           WidgetLocation (20.0, 6.0, 32.0, 41.0, -1.0));
  button_1_.setColor(0.8f, 0.8f, 0.8f);
  button_1_.SetTexture("play_button");
  button_2_ = ButtonWidget(game_state_manager_,
                           WidgetLocation (20.0, 6.0, 32.0, 48.0, -1.0));
  button_2_.setColor(0.8f, 0.8f, 0.8f);

  stage_=0;
  wait_=0;
  step_=0;
  robot_=0;
  sprite_atlas_ = game_state_manager_->TextureAtlas();
}

GameStateMainMenu::~GameStateMainMenu(void) {
}

//Loads the GameStateMainMenu onto the GameStateManager stack in active mode
void GameStateMainMenu::Load() {
  button_1_.MoveTo(32.0, 41.0);
  button_2_.MoveTo(32.0, 48.0);
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
  } 
}
void GameStateMainMenu::MouseButtonReleased(int button,
                                            double x_position,
                                            double y_position) {
  if(button_1_.pressed())
    button_1_.setPressed(false);
  else if(button_2_.pressed())
    button_2_.setPressed(false);
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
    game_state_manager_->Push(game_state_program_);
    break;
  case 2:
    button_color = button_1_.color();
    game_state_manager_->Exit();
    break;
  }
}
//Key Actions
void GameStateMainMenu::Select_Next() {
  if(focus_ == &button_1_) {
    Focus(&button_2_);
  } else if(focus_ == &button_2_) {
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
  //game_state_manager_->TextureAtlas()->getCoordinates("10");
  
  if(++wait_>7) {
    wait_=0;
    if(++step_>3) {
      step_=0;
      if(++stage_>7) {
        stage_=0;
        if(++robot_>7) robot_=0;
      }
    }
  }
  if(focus_ != nullptr)
    focus_->Draw(true);
  sprite_atlas_->ActivateTexture("card_back");
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_QUADS);
    glColor3f(1.00f, 1.00f, 1.00f);
    sprite_atlas_->LoadCoordinates(Texture::UPPER_LEFT);
    glVertex3f(28.0f, 0.0f, 0.0f);
    sprite_atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
    glVertex3f(56.0f, 0.0f, 0.0f);
    sprite_atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
    glVertex3f(56.0f, 40.0f, 0.0f);
    sprite_atlas_->LoadCoordinates(Texture::LOWER_LEFT);
    glVertex3f(28.0f, 40.0f, 0.0f);

    sprite_atlas_->LoadCoordinates(Texture::LOWER_LEFT);
    glVertex3f( 0.0f, 50.0f, 0.0f);
    sprite_atlas_->LoadCoordinates(Texture::UPPER_LEFT);
    glVertex3f( 0.0f,  0.0f, 0.0f);
    sprite_atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
    glVertex3f(28.0f,  0.0f, 0.0f);
    sprite_atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
    glVertex3f(28.0f, 40.0f, 0.0f);

    sprite_atlas_->LoadCoordinates(Texture::LOWER_LEFT);
    glVertex3f(56.0f, 40.0f, 0.0f);
    sprite_atlas_->LoadCoordinates(Texture::UPPER_LEFT);
    glVertex3f(56.0f, 0.0f, 0.0f);
    sprite_atlas_->LoadCoordinates(Texture::UPPER_RIGHT);
    glVertex3f(84.0f, 0.0f, 0.0f);
    sprite_atlas_->LoadCoordinates(Texture::LOWER_RIGHT);
    glVertex3f(84.0f, 50.0f, 0.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  button_1_.Draw();
  button_2_.Draw();
}

void GameStateMainMenu::LinkProgramState(GameState* state) {
  game_state_program_ = state;
}