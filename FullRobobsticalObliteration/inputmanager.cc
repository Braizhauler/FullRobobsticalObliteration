/*******************************************************************************
* File: inputmanager.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 05
* Version: 0
* Revised: 2015 MAR 05
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "inputmanager.h"

const int KEYBIND_EXIT = GLFW_KEY_ESCAPE;

/*******************************
* Constructors                */
InputManager::InputManager(GameStateManager* state_manager) {
  game_state_manager_ = state_manager;
}


InputManager* InputManager::input_manager_instance_ = nullptr;

GameStateManager* InputManager::game_state_manager_ = nullptr;

double InputManager::cursor_x_ = 0;
double InputManager::cursor_y_ = 0;
bool InputManager::mouse_button_[3] = {false, false, false};

double InputManager::mouse_input_scale_ = 1.0;
double InputManager::mouse_offset_x_ = 0.0;
double InputManager::mouse_offset_y_ = 0.0;

double InputManager::time_mouse_down_[3] = {0.0, 0.0, 0.0};
bool InputManager::cursor_in_window_=true;
const double InputManager::k_mouse_click_sensitivity = 0.5;

/*******************************
* Accessor                    */
//Returns the instance of the InputManager
//   returns nullptr if GameStateManager has not been set
InputManager* InputManager::getInstance(GameStateManager* state_manager) {
  if(input_manager_instance_ == nullptr)
    input_manager_instance_ = new InputManager(state_manager);
  if(state_manager == nullptr) {
    if(game_state_manager_ == nullptr)
      return nullptr;
  } else {
    if(game_state_manager_ != nullptr)
      game_state_manager_  = state_manager;
    else
      return nullptr;
  }
  return input_manager_instance_;
}

/*******************************
* Mutators                    */
void InputManager::LinkManager(GameStateManager* state_manager) {
      game_state_manager_  = state_manager;
}

/*******************************
* Methods                    */
void InputManager::RegisterEvents(MyWindowWrapper* window) {
  window->RegisterKeyboard(KeyboardFunction);
  window->RegisterMouse(CursorEnterFunction,
                        CursorPositionFunction,
                        MouseButtonFunction,
                        ScrollWheelFunction);
  window->RegisterMouseOffsets(SetMouseOffsets);
}

void InputManager::SetMouseOffsets(double mouse_offset_x,
                                   double mouse_offset_y,
                                   double mouse_input_scale) {
  mouse_offset_x_ = mouse_offset_x;
  mouse_offset_y_ = mouse_offset_y;
  mouse_input_scale_ = mouse_input_scale;
}

/*******************************
* Callbacks                   */
void InputManager::CursorEnterFunction(GLFWwindow * window,
                                          int cursor_in_window) { //bool
  cursor_in_window_=(cursor_in_window!=0);
} 

void InputManager::CursorPositionFunction(GLFWwindow * window,
                                          double x_position,  //relative to left 
                                          double y_position) {//relative to top
  if(cursor_in_window_) {
    //DEBUG
    //std::cout<<"("<<x_position<<", "<<y_position<<")"<<std::endl;
    cursor_x_=(x_position/mouse_input_scale_) - mouse_offset_x_;
    cursor_y_=(y_position/mouse_input_scale_) - mouse_offset_y_;
    //DEBUG
    //std::cout<<"("<<cursor_x_<<", "<<cursor_y_<<")"<<std::endl;
    game_state_manager_->CursorMove(mouse_button_[0], cursor_x_, cursor_y_);
  }
} 


void InputManager::MouseButtonFunction(GLFWwindow* window,
                                       int button, // GLFW_MOUSE_BUTTON_#
                                       int action, //GLFW_PRESS-or-GLFW_RELEASE.
                                       int modifers) {
  if(cursor_in_window_) {
    if (action == GLFW_PRESS) {
      if (button == GLFW_MOUSE_BUTTON_1)
        mouse_button_[0] = true;
        time_mouse_down_[0] = glfwGetTime();
      if (button == GLFW_MOUSE_BUTTON_2)
        mouse_button_[1] = true;
        time_mouse_down_[1] = glfwGetTime();
      if (button == GLFW_MOUSE_BUTTON_3)
        mouse_button_[2] = true;
      game_state_manager_->MouseButtonPressed(button, cursor_x_, cursor_y_);
    } else { //action == GLFW_RELEASE
      if (button == GLFW_MOUSE_BUTTON_1)
        mouse_button_[0] = false;
        if ( (glfwGetTime()-time_mouse_down_[0])  < k_mouse_click_sensitivity )
          game_state_manager_->MouseButtonClicked(0, cursor_x_, cursor_y_);
      if (button == GLFW_MOUSE_BUTTON_2)
        mouse_button_[1] = false;
      if (button == GLFW_MOUSE_BUTTON_3)
        mouse_button_[2] = false;
      game_state_manager_->MouseButtonReleased(button, cursor_x_, cursor_y_);
    }
  }
}

void InputManager::ScrollWheelFunction(GLFWwindow * window,
                                       double x_offset,
                                       double y_offset) {
}

void InputManager::KeyboardFunction(GLFWwindow * window,
                                    int key,
                                    int scancode,
                                    int action,//GLFW_PRESS, GLFW_RELEASE
                                               //-or- GLFW_REPEAT
                                    int modifiers) {
  switch (key) {
    case KEYBIND_EXIT:
      game_state_manager_->Exit();
      break;
    default:
      ;
  }
}