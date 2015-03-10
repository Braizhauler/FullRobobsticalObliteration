/*******************************************************************************
* File: mywindowwrapper.h
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 JAN 19
* Version: 0
* Revised: 2015 FEB 02
*
*
* MyWindowWrapper:
* A wrapper for GLFW Window
*
* � [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#ifndef MY_WINDOW_WRAPPER_H_
#define MY_WINDOW_WRAPPER_H_

#include <glfw3.h>
#include <string>
#include <map>

class MyWindowWrapper;

namespace MyWindowControl{
extern std::map<GLFWwindow*, MyWindowWrapper*> glfw_to_mywindowwrapper;

void ResizeWindow(GLFWwindow* window, int width, int height);
}

class MyWindowWrapper {
public:
  //Constructors, and Destructor
	MyWindowWrapper();
	~MyWindowWrapper(void);
  const bool Init(const int width, const int height, const char * title);


  void Exit(void);
  //cleanup
  void Terminate (void);

  //Methods
  void ProccessOSEvents();
  void SwapBuffers(void);
  
  void Resize(const int width,const int height);

  void RegisterResize(const GLFWwindowsizefun);


  void RegisterKeyboard(const GLFWkeyfun keyboardFunc);
  
  void RegisterMouse(const GLFWcursorenterfun cursorenterFunc,
                     const GLFWcursorposfun positionFunc,
                     const GLFWmousebuttonfun buttonFunc,
                     const GLFWscrollfun scrollwheelFunc);

  //Accessors and Mutators
	const bool initialized();
	const bool done();

  char const* title();
  void set_title(const char * title);

  GLFWwindow * context(void);

  friend void MyWindowControl::ResizeWindow(GLFWwindow* window, int width, int height);
private:
  // Member Variables
	GLFWwindow* window_;
	bool initialized_;
	bool finished_;
  int width_;
  int height_;
  char * title_;
};



#endif //MY_WINDOW_WRAPPER_H_