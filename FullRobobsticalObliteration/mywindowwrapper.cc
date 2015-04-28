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

#include "mywindowwrapper.h"

/*******************************
* Constructors and Destructor */

//Constructor DOES NOT CREATE A WINDOW, call Init() after the object is created.
MyWindowWrapper::MyWindowWrapper() {
  window_ = nullptr;
	initialized_ = false;
  finished_ = false;
  window_width_ = 0;
  window_height_ = 0;
  title_ = nullptr;
  mouse_offset_function_ = nullptr;
}
 
MyWindowWrapper::~MyWindowWrapper(void) {
  delete [] title_;
  title_ = nullptr;
  initialized_ = false;
}

const bool MyWindowWrapper::Init(int width, int height, const char * title)  {
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  glfwWindowHint(GLFW_RED_BITS, mode->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
  glfwWindowHint(GLFW_DECORATED, GL_FALSE);//Remove title bar, acting wierd

  window_width_ = width;
  window_height_ = height;
  size_t title_length = strlen(title);
  title_ = new char[title_length+1];
  for (size_t i = 0;i<=title_length;++i) {
    title_[i] = title[i];
  }
  //The last two parameters of glfwCreateWindow are:
  //  GLFWmonitor * monitorUsedByFullScreen
  //  GLFWwindow * share
  window_ = glfwCreateWindow( window_width_, window_height_, title_, nullptr, nullptr);
	if( window_ == NULL ){
		glfwTerminate();
	} else {
    initialized_ = true;
  }
  //make that OpenGL context the active context
  glfwMakeContextCurrent(window_);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  RegisterResize(MyWindowControl::ResizeWindow);
  Resize(window_width_,window_height_);

  return initialized_;
}

//sets the finished to true
void MyWindowWrapper::Exit(void) {
  finished_=true;
}

// Terminate tells GLFW to close it's window and clean up
void MyWindowWrapper::Terminate(void) {
  finished_=true;
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



void MyWindowWrapper::Resize(const int width,const int height)  {
  int window_width_ = width;
  int window_height_ = height;
  glViewport(0,0,window_width_, window_height_);

  display_width_ =
    window_width_ < 14.0 * window_height_ / 9.0 ?
    window_width_ : 14.0 * window_height_ / 9.0 ;
  display_height_ = 
    9.0 * window_width_ / 14.0 < window_height_ ?
    9.0 * window_width_ / 14.0 : window_height_ ;

  display_offset_x_ = (window_width_ - display_width_) /2;
  display_offset_y_ = (window_height_ - display_height_) /2;
  
  display_scale_ = display_height_ / 54.0;

  display_width_ = display_width_ / display_scale_;
  display_height_ = display_height_ / display_scale_;
  display_offset_x_ = display_offset_x_ / display_scale_;
  display_offset_y_ = display_offset_y_ / display_scale_;

  glMatrixMode(GL_PROJECTION);//changing perspective rather then drawing
	
  glLoadIdentity();
  
  glOrtho(-display_offset_x_, //left
          display_width_ + display_offset_x_, //right
          display_height_ + display_offset_y_, //bottom
          -display_offset_y_, //top
          -20, //near
          20); //far

  if(mouse_offset_function_ != nullptr)
    mouse_offset_function_(display_offset_x_,display_offset_y_,display_scale_);
}

void MyWindowWrapper::RegisterResize(GLFWwindowsizefun)  {
  MyWindowControl::glfw_to_mywindowwrapper.emplace(window_, this);
  glfwSetWindowSizeCallback(window_,MyWindowControl::ResizeWindow);
}

void MyWindowWrapper::RegisterKeyboard(GLFWkeyfun keyboard) {
  glfwSetKeyCallback(window_,keyboard);
}

void MyWindowWrapper::RegisterMouse(GLFWcursorenterfun cursorenterFunc,
                                    GLFWcursorposfun positionFunc,
                                    GLFWmousebuttonfun buttonFunc,
                                    GLFWscrollfun scrollwheelFunc) {
  glfwSetCursorPosCallback(window_, positionFunc);
  glfwSetMouseButtonCallback(window_, buttonFunc);
  glfwSetScrollCallback(window_, scrollwheelFunc);
  glfwSetCursorEnterCallback(window_, cursorenterFunc);
}

void MyWindowWrapper::RegisterMouseOffsets(const MouseOffsetFunc offsetfunc) {
  mouse_offset_function_ = offsetfunc;
  mouse_offset_function_(display_offset_x_,display_offset_y_,display_scale_);
}

double MyWindowWrapper::scale() {
  return display_scale_;
}
double MyWindowWrapper::offset_x() {
  return display_offset_x_;
}
double MyWindowWrapper::offset_y() {
  return display_offset_y_;
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
  
void MyWindowWrapper::set_title(const char * title) {
  size_t title_length = strlen(title);
  for (size_t i = 0;i<title_length;++i) {
    title_[i] = title[i];
  }
  glfwSetWindowTitle(window_, title_);
}

namespace MyWindowControl {

void ResizeWindow(GLFWwindow* window, int width, int height) {
  glfw_to_mywindowwrapper.at(window)->Resize(width, height);
}

}