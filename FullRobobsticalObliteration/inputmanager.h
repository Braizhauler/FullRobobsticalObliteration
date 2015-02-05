/*******************************************************************************
* File: inputmanager.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 JAN 24
* Version: 0
* Revised: 2015 JAN 24
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

struct GLFWwindow;
class MyWindowWrapper;
class GameStateManager;

class InputManager {
public:
  //Constructors and Destructor
  InputManager();
  ~InputManager(void);
  //Methods
  void RegisterEvents(MyWindowWrapper* window);
  //Input callback events
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
                        int action,//GLFW_PRESS, GLFW_RELEASE -or- GLFW_REPEAT
                        int modifiers);
  //Accessors and Mutators
private:
  //Member Variables
};


#endif //INPUT_MANAGER_H