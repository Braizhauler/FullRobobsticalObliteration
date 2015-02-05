/*******************************************************************************
* File: inputmanager.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 JAN 24
* Version: 0
* Revised: 2015 JAN 24
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "inputmanager.h"

/*******************************
* Constructors and Destructor */
InputManager::InputManager(void) {}
InputManager::~InputManager(void) {}




void InputManager::RegisterEvents(MyWindowWrapper* window) {
  window->RegisterKeyboard(KeyboardFunction);
  window->RegisterMouse(CursorPositionFunction,
                        MouseButtonFunction,
                        ScrollWheelFunction);
}

/*******************************
* Methods                    */

void InputManager::CursorPositionFunction(GLFWwindow * window,
                            double x_position,  //relative to left 
                            double y_position) {//relative to top
} 


void InputManager::MouseButtonFunction(GLFWwindow* window,
                         int button,// GLFW_MOUSE_BUTTON_#
                         int action, //GLFW_PRESS -or- GLFW_RELEASE.
                         int modifers) {
}

void InputManager::ScrollWheelFunction(GLFWwindow * window,
                         double x_offset,
                         double y_offset) {
}

void InputManager::KeyboardFunction(GLFWwindow * window,
                              int key,
                              int scancode,
                              int action,//GLFW_PRESS, GLFW_RELEASE -or- GLFW_REPEAT
                              int modifiers) {
}

/*******************************
* Accessors and Mutators      */