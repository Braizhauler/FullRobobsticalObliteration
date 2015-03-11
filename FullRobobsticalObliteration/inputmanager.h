/*******************************************************************************
* File: inputmanager.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 MAR 05
* Version: 0
* Revised: 2015 MAR 05
*
* InputManager:
*   Handles keyboard, mouse, and controller input and translates to game events
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <string>

//DEBUG
#include <iostream>


#include "mywindowwrapper.h"
#include "gamestatemanager.h"

class InputManager {
public:
  static InputManager* getInstance(GameStateManager* state_manager = nullptr);

  //Links 
  static void LinkManager(GameStateManager* state_manager);
  //Register
  static void RegisterEvents(MyWindowWrapper* window);
  //Input callback events
  static void CursorEnterFunction(GLFWwindow * window,
                                  int cursor_in_window);

  static void CursorPositionFunction(GLFWwindow * window,
                                     double x_position,  //relative to left 
                                     double y_position); //relative to top
  static void MouseButtonFunction(GLFWwindow* window,
                                  int button,// GLFW_MOUSE_BUTTON_#
                                  int action, //GLFW_PRESS -or- GLFW_RELEASE.
                                  int modifers);
  static void ScrollWheelFunction(GLFWwindow * window,
                                  double x_offset,
                                  double y_offset);
  static void KeyboardFunction(GLFWwindow * window,
                               int key,
                               int scancode,
                               int action,//GLFW_PRESS, GLFW_RELEASE 
                                          //-or- GLFW_REPEAT
                               int modifiers);
  
  static void SetMouseOffsets(double mouse_offset_x,
                              double mouse_offset_y,
                              double mouse_input_scale);
private:
  //Member Variables
  InputManager();
  InputManager(GameStateManager* state_manager);
  InputManager(InputManager const&);
  void operator=(InputManager const&);
  static InputManager* input_manager_instance_;
  static GameStateManager* game_state_manager_;

  static double cursor_x_;
  static double cursor_y_;

  static double mouse_input_scale_;
  static double mouse_offset_x_;
  static double mouse_offset_y_;

  static bool mouse_button_[3];
  static double time_mouse_down_[3];
  static bool cursor_in_window_;
  static const double k_mouse_click_sensitivity;//sec between mouse down and up
};

#endif //INPUT_MANAGER_H