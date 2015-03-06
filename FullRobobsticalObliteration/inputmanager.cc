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
  window->RegisterMouse(CursorPositionFunction,
                        MouseButtonFunction,
                        ScrollWheelFunction);
}

/*******************************
* Callbacks                   */
void InputManager::CursorPositionFunction(GLFWwindow * window,
                                          double x_position,  //relative to left 
                                          double y_position) {//relative to top
} 


void InputManager::MouseButtonFunction(GLFWwindow* window,
                                       int button, // GLFW_MOUSE_BUTTON_#
                                       int action, //GLFW_PRESS-or-GLFW_RELEASE.
                                       int modifers) {
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