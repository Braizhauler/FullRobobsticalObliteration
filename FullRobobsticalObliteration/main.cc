/*******************************************************************************
* filename: main.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 JAN 06
* Version: 0
* Revised: 2015 JAN 11
*
* © [2015] Dwarfholm.com
* All Rights Reserved.  
*******************************************************************************/
#ifndef MAIN_CC
#define MAIN_CC

//hides console window in Windows
//#pragma comment (linker, "/subsystem:windows /entry:mainCRTStartup") 

#include <stdio.h>
#include <stdlib.h>
#include <map>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

//#include "font.h"

#include "spriteatlas.h"
#include "mywindowwrapper.h"
#include "gamestatemanager.h"
#include "inputmanager.h"
#include "gamestatemainmenu.h"
#include "gamestateprogram.h"

namespace MyWindowControl{
std::map<GLFWwindow*, MyWindowWrapper*> glfw_to_mywindowwrapper;
}

int main (int num_of_arugments, char * argument_list[])  {
  // Initialise GLFW
  if( !glfwInit() )
  {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    return -1;
  }
  
  //Use OpenGL version 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  //error if we use depricated OpenGL
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

  //Anti Aliasing x4
  glfwWindowHint(GLFW_SAMPLES, 4); 

  
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);

  MyWindowWrapper window;
  
  //DEBUG
  //window.Init( mode->width, mode->height, "Full Robobstical Obliteration\0");
  window.Init( 800, 600, "Full Robobstical Obliteration\0");


  // Initialize GLEW
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "GLEW not sticky enough, arena fell apart\n");
    return -1;
  }
  
  // Set Background to BLACK
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  
  GameStateManager state_manager(&window);
  InputManager* input_manager;
  
  input_manager = InputManager::getInstance(&state_manager);
  input_manager->RegisterEvents(&window);

  GameStateMainMenu state_menu(&state_manager);
  GameStateProgram state_program(&state_manager);
  state_manager.Push(&state_menu);
  
  state_menu.LinkProgramState(&state_program);
  do {  
    window.ProccessOSEvents();

    state_manager.Draw();

    // Swap buffers
    window.SwapBuffers();
  } while(!window.done() && window.initialized());
    //glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS
  window.Terminate();

  return 0;

}

#endif // MAIN_CC