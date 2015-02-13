/*******************************************************************************
* File: spriteatlas.cc
* Author: Greg Howlett (GregTHowlett@Gmail.com)
* Created: 2015 JAN 19
* Version: 0
* Revised: 2015 JAN 22
*
* © [2015] Dwarfholm.com
* All Rights Reserved.
*******************************************************************************/

#include "MyWindowWrapper.h"


/*******************************
* Constructors and Destructor */

//Constructor DOES NOT CREATE A WINDOW, call Init() after the object is created.
MyWindowWrapper::MyWindowWrapper() {
  window_ = nullptr;
	initialized_ = false;
  finished_ = false;
  width_ = 0;
  height_ = 0;
  title_ = nullptr;
}
 
MyWindowWrapper::~MyWindowWrapper(void) {
  delete [] title_;
  title_ = nullptr;
  initialized_ = false;
}

const bool MyWindowWrapper::Init(int width, int height, const char * title)  {
  width_ = width;
  height_ = height;
  size_t title_length = strlen(title);
  title_ = new char[title_length];
  for (size_t i = 0;i<=title_length;++i) {
    title_[i] = title[i];
  }
  //The last two parameters of glfwCreateWindow are:
  //  GLFWmonitor * monitorUsedByFullScreen
  //  GLFWwindow * share
  window_ = glfwCreateWindow( width_, height_, title_, nullptr, nullptr);
	if( window_ == NULL ){
		glfwTerminate();
	} else {
    initialized_ = true;
  }
  //make that OpenGL context the active context
  glfwMakeContextCurrent(window_);

  return initialized_;
}

// Terminate tells GLFW to close it's window and clean up
void MyWindowWrapper::Terminate(void) {
  glfwTerminate();
}


/*******************************
* Methods                     */

// ProccessOSEvents() makes sure the operating system isn't blocking our window,
// and invokes our input_handler_
void MyWindowWrapper::ProccessOSEvents()  {
  glfwPollEvents();
}

void MyWindowWrapper::SwapBuffers() {
  glfwSwapBuffers(window_);
}
void MyWindowWrapper::RegisterKeyboard(GLFWkeyfun keyboard) {
  glfwSetKeyCallback(window_,keyboard);
}

void MyWindowWrapper::RegisterMouse(GLFWcursorposfun positionFunc,
                                    GLFWmousebuttonfun buttonFunc,
                                    GLFWscrollfun scrollwheelFunc) {

}

/*******************************
* Accessors and Mutators      */
const bool MyWindowWrapper::initialized() {
  return initialized_;
}

const bool MyWindowWrapper::done() {
  return finished_;
}

GLFWwindow * MyWindowWrapper::context(void) {
  return window_;
}

char const* MyWindowWrapper::title() {
  return title_;
}
  
void MyWindowWrapper::set_title(char * title) {
  size_t title_length = strlen(title);
  for (size_t i = 0;i<title_length;++i) {
    title_[i] = title[i];
  }
  glfwSetWindowTitle(window_, title_);
}
